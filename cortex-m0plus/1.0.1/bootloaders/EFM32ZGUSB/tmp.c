static I2C_Transfer_TypeDef i2cTransfer[I2C_COUNT];


I2C_TransferReturn_TypeDef I2C_Transfer(I2C_TypeDef *i2c)
{
  uint32_t                tmp;
  uint32_t                pending;
  I2C_Transfer_TypeDef    *transfer;
  I2C_TransferSeq_TypeDef *seq;

  transfer = i2cTransfer;

  seq = transfer->seq;
  for (;; )
    {
      pending = i2c->IF;

      if(pending & I2C_IF_ERRORS) {  // If some sort of fault, abort transfer
	if (pending & I2C_IF_ARBLOST) { // Arb fault
	  transfer->result = i2cTransferArbLost;
	} else if (pending & I2C_IF_BUSERR) { // bus error
	  transfer->result = i2cTransferBusErr;
	}
	transfer->state = i2cStateDone;
	goto done;
      }

      switch (transfer->state) {

      case i2cStateStartAddrSend:  // Send first start+address (first byte if 10 bit)
	if (seq->flags & I2C_FLAG_10BIT_ADDR) {
	  tmp = (((uint32_t)(seq->addr) >> 8) & 0x06) | 0xf0;  // In 10 bit address mode, the address following the first start always indicate write.
	} else {
	  tmp = (uint32_t)(seq->addr) & 0xfe;
	  if (seq->flags & I2C_FLAG_READ) {
	    tmp |= 1;  // Indicate read request
	  }
	}
	transfer->state = i2cStateAddrWFAckNack;
	i2c->TXDATA     = tmp; /* Data not transmitted until START sent */
	i2c->CMD        = I2C_CMD_START;
	goto done;

      case i2cStateAddrWFAckNack:  // Wait for ACK/NACK on address (first byte if 10 bit)
	if (pending & I2C_IF_NACK) {
	  i2c->IFC         = I2C_IFC_NACK;
	  transfer->result = i2cTransferNack;
	  transfer->state  = i2cStateWFStopSent;
	  i2c->CMD         = I2C_CMD_STOP;
	} else if (pending & I2C_IF_ACK) {
	  i2c->IFC = I2C_IFC_ACK;
	  if (seq->flags & I2C_FLAG_10BIT_ADDR) {  // If 10 bit address, send 2nd byte of address
	    transfer->state = i2cStateAddrWF2ndAckNack;
	    i2c->TXDATA     = (uint32_t)(seq->addr) & 0xff;
	  } else {
	    if (seq->flags & I2C_FLAG_READ) { // Determine whether receiving or sending data
	      transfer->state = i2cStateWFData;
	      if(seq->buf[transfer->bufIndx].len==1) {
		i2c->CMD  = I2C_CMD_NACK;
	      }
	    } else {
	      transfer->state = i2cStateDataSend;
	      continue;
	    }
	  }
	}
	goto done;

      case i2cStateAddrWF2ndAckNack:	  // Wait for ACK/NACK on second byte of 10 bit address
	if (pending & I2C_IF_NACK) {
	  i2c->IFC         = I2C_IFC_NACK;
	  transfer->result = i2cTransferNack;
	  transfer->state  = i2cStateWFStopSent;
	  i2c->CMD         = I2C_CMD_STOP;
	} else if(pending & I2C_IF_ACK) {
	  i2c->IFC = I2C_IFC_ACK;
	  // If using plain read sequence with 10 bit address, switch to send repeated start
	  if (seq->flags & I2C_FLAG_READ) {
	    transfer->state = i2cStateRStartAddrSend;
	  } else { // Otherwise expected to write 0 or more bytes
	    transfer->state = i2cStateDataSend;
	  }
	  continue;
	}
	goto done;

      case i2cStateRStartAddrSend:	  / Send repeated start+address
	  if (seq->flags & I2C_FLAG_10BIT_ADDR) {
	    tmp = ((seq->addr >> 8) & 0x06) | 0xf0;
	  } else {
	    tmp = seq->addr & 0xfe;
	  }
	// If this is a write+read combined sequence, then read is about to start
	if (seq->flags & I2C_FLAG_WRITE_READ) {      // Indicate read request
	  tmp |= 1;
	}
	transfer->state = i2cStateRAddrWFAckNack;  // We have to write START cmd first since repeated start, otherwise data would be sent first
	i2c->CMD    = I2C_CMD_START;
	i2c->TXDATA = tmp;
	goto done;

      case i2cStateRAddrWFAckNack:	  // Wait for ACK/NACK on repeated start+address (first byte if 10 bit)
	if (pending & I2C_IF_NACK) {
	  i2c->IFC         = I2C_IFC_NACK;
	  transfer->result = i2cTransferNack;
	  transfer->state  = i2cStateWFStopSent;
	  i2c->CMD         = I2C_CMD_STOP;
	} else if (pending & I2C_IF_ACK) {
	  i2c->IFC = I2C_IFC_ACK;
	  if (seq->flags & I2C_FLAG_WRITE_READ) {  // Determine whether receiving or sending data
	    transfer->state = i2cStateWFData;
	  } else {
	    transfer->state = i2cStateDataSend;
	    continue;
	  }
	}
	goto done;

      case i2cStateDataSend:	  // Send a data byte to slave
	if (transfer->offset >= seq->buf[transfer->bufIndx].len) {  // Reached end of data buffer?
	  transfer->offset = 0;     // Move to next message part
	  transfer->bufIndx++;

	  // Send repeated start when switching to read mode on 2nd buffer
	  if (seq->flags & I2C_FLAG_WRITE_READ) {
	    transfer->state = i2cStateRStartAddrSend;
	    continue;
	  }
	  // Only writing from one buffer, or finished both buffers
	  if ((seq->flags & I2C_FLAG_WRITE) || (transfer->bufIndx > 1)) {
	    transfer->state = i2cStateWFStopSent;
	    i2c->CMD        = I2C_CMD_STOP;
	    goto done;
	  }
	  // Reprocess in case next buffer is empty
	  continue;
	}
	i2c->TXDATA     = (uint32_t)(seq->buf[transfer->bufIndx].data[transfer->offset++]);  // Send byte
	transfer->state = i2cStateDataWFAckNack;
	goto done;

      case i2cStateDataWFAckNack:	  // Wait for ACK/NACK from slave after sending data to it
	if (pending & I2C_IF_NACK) {
	  i2c->IFC         = I2C_IFC_NACK;
	  transfer->result = i2cTransferNack;
	  transfer->state  = i2cStateWFStopSent;
	  i2c->CMD         = I2C_CMD_STOP;
	} else if (pending & I2C_IF_ACK) {
	  i2c->IFC        = I2C_IFC_ACK;
	  transfer->state = i2cStateDataSend;
	  continue;
	}
	goto done;

      case i2cStateWFData:	  // Wait for data from slave
	if (pending & I2C_IF_RXDATAV) {
	  uint8_t       data;
	  unsigned int  rxLen = seq->buf[transfer->bufIndx].len;

	  data = (uint8_t)(i2c->RXDATA);   // Must read out data in order to not block further progress

	  // Make sure not storing beyond end of buffer just in case
	  if (transfer->offset < rxLen) {
	    seq->buf[transfer->bufIndx].data[transfer->offset++] = data;
	  }
	  // If we have read all requested data, then the sequence should end
	  if (transfer->offset >= rxLen) {
	    // If there is only one byte to receive we need to transmit the NACK now, before the stop
	    if (1 == rxLen) {
	      i2c->CMD  = I2C_CMD_NACK;
	    }
	    transfer->state = i2cStateWFStopSent;
	    i2c->CMD        = I2C_CMD_STOP;
	  } else {
	    // Send ACK and wait for next byte
	    i2c->CMD = I2C_CMD_ACK;
	    if ( (1<rxLen) && (transfer->offset == (rxLen-1)) ) {
	      // If there is more than one byte to receive and this is the next to last byte we need to
	      // transmit the NACK now, before receiving the last byte
	      i2c->CMD  = I2C_CMD_NACK;
	    }
	  }
	}
	goto done;

      case i2cStateWFStopSent:	  // Wait for STOP to have been sent
	if (pending & I2C_IF_MSTOP) {
	  i2c->IFC        = I2C_IFC_MSTOP;
	  transfer->state = i2cStateDone;
	}
	goto done;

      default:	  // Unexpected state, SW fault
	transfer->result = i2cTransferSwFault;
	transfer->state  = i2cStateDone;
	goto done;
      }
    }

 done:
  if (transfer->state == i2cStateDone) {      // Disable interrupt sources when done
    i2c->IEN = 0;
    // Update result unless some fault already occurred
    if (transfer->result == i2cTransferInProgress) {
      transfer->result = i2cTransferDone;
    }
  } else { // Until transfer is done keep returning i2cTransferInProgress
    return(i2cTransferInProgress);
  }
  return transfer->result;
}




//----------------------------------------------------------------------

int i2c_write_byte(uint8_t address, uint8_t data)
{


}





