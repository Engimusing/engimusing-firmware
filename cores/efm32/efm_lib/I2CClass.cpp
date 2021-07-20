/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/



#include "Arduino.h"

#include <em_i2c.h>

// Includes Atmel CMSIS
#include <em_device.h>
#include <em_cmu.h>

#if WIRE_INTERFACES_COUNT > 0
#include "I2CClass.h"

static I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;


I2CClass::I2CClass(I2C_TypeDef &_i2c, uint8_t loc, CMU_Clock_TypeDef _i2cClock, uint32_t pinSda, uint32_t pinScl)
    : myI2c(_i2c)
    , myLocation(loc)
    , myI2cClock(_i2cClock)
    , myPinSda(pinSda)
    , myPinScl(pinScl)
{
    
}

void I2CClass::begin(void) 
{  
  /* Enable High Frequency Peripherals */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(myI2cClock, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  pinMode(
		  myPinSda,
		  WIRED_AND_PU_FILTER);
  digitalWrite(myPinSda, 1);
  pinMode(
		  myPinScl,
		  WIRED_AND_PU_FILTER);
  digitalWrite(myPinScl, 1);
  
  //reset the state of the slave by sending 9 clk signals while SDA is high
  for (int i = 0; i < 9; i++)
  {
	  digitalWrite(myPinScl, 0);
	  digitalWrite(myPinScl, 1);
  }

#ifndef EFM32GG12B110F1024GQ64
  myI2c.ROUTE = I2C_ROUTE_SDAPEN |
    I2C_ROUTE_SCLPEN |
    (myLocation << _I2C_ROUTE_LOCATION_SHIFT);
#else
  myI2c.ROUTEPEN = I2C_ROUTEPEN_SDAPEN |
    I2C_ROUTEPEN_SCLPEN;
  myI2c.ROUTELOC0 = 
    (myLocation << _I2C_ROUTELOC0_SDALOC_SHIFT) | 
	(myLocation << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	
#endif				
  I2C_Init(&myI2c, &i2cInit);
  I2C_Enable(&myI2c, true);
}

uint8_t I2CClass::transfer(uint8_t address, uint8_t txLength, uint8_t *txBuffer, uint8_t rxLength, uint8_t *rxBuffer)
{
    myCurTransmission.addr = (address << 1); //convert to 8-bit address for energy micro
	
    if(txLength > 0)
    {
        myCurTransmission.buf[0].data = &txBuffer[0];
        myCurTransmission.buf[0].len = 1;
        myCurTransmission.flags = I2C_FLAG_WRITE;

        if(rxLength > 0)//assume it is a read transmission
        {	
            myCurTransmission.buf[1].data = &rxBuffer[0];
            myCurTransmission.buf[1].len = rxLength;
            myCurTransmission.flags = I2C_FLAG_WRITE_READ;
        }else if(txLength > 1)
        {
            myCurTransmission.buf[1].data = &txBuffer[1];
            myCurTransmission.buf[1].len = txLength - 1;
            myCurTransmission.flags = I2C_FLAG_WRITE_WRITE;
        }
    }else if(rxLength > 0)
    {
      myCurTransmission.buf[0].data = &rxBuffer[0];
      myCurTransmission.buf[0].len = rxLength;
      myCurTransmission.flags = I2C_FLAG_READ;
    }else
    {
        return 0;
    }
	
    // transmit buffer (blocking)
    I2C_TransferReturn_TypeDef ret = I2C_TransferInit(&myI2c,&myCurTransmission);
    while (ret == i2cTransferInProgress)
    {
        ret = I2C_Transfer(&myI2c);
    }


    if(ret == i2cTransferDone)
    {
        //return the number of bytes sent and recieved
        return myCurTransmission.buf[0].len + myCurTransmission.buf[1].len;
    }else
    {
        return 0;
    }
    
}

void I2CClass::onService(void) {
	
  //not supported yet
  return;
  /*
  // Retrieve interrupt status
  uint32_t sr = TWI_GetStatus(twi);

  if (status == SLAVE_IDLE && TWI_STATUS_SVACC(sr)) {
  TWI_DisableIt(twi, TWI_IDR_SVACC);
  TWI_EnableIt(twi, TWI_IER_RXRDY | TWI_IER_GACC | TWI_IER_NACK
  | TWI_IER_EOSACC | TWI_IER_SCL_WS | TWI_IER_TXCOMP);

  srvBufferLength = 0;
  srvBufferIndex = 0;

  // Detect if we should go into RECV or SEND status
  // SVREAD==1 means *master* reading -> SLAVE_SEND
  if (!TWI_STATUS_SVREAD(sr)) {
  status = SLAVE_RECV;
  } else {
  status = SLAVE_SEND;

  // Alert calling program to generate a response ASAP
  if (onRequestCallback)
  onRequestCallback();
  else
  // create a default 1-byte response
  write((uint8_t) 0);
  }
  }

  if (status != SLAVE_IDLE) {
  if (TWI_STATUS_TXCOMP(sr) && TWI_STATUS_EOSACC(sr)) {
  if (status == SLAVE_RECV && onReceiveCallback) {
  // Copy data into rxBuffer
  // (allows to receive another packet while the
  // user program reads actual data)
  for (uint8_t i = 0; i < srvBufferLength; ++i)
  rxBuffer[i] = srvBuffer[i];
  rxBufferIndex = 0;
  rxBufferLength = srvBufferLength;

  // Alert calling program
  onReceiveCallback( rxBufferLength);
  }

  // Transfer completed
  TWI_EnableIt(twi, TWI_SR_SVACC);
  TWI_DisableIt(twi, TWI_IDR_RXRDY | TWI_IDR_GACC | TWI_IDR_NACK
  | TWI_IDR_EOSACC | TWI_IDR_SCL_WS | TWI_IER_TXCOMP);
  status = SLAVE_IDLE;
  }
  }

  if (status == SLAVE_RECV) {
  if (TWI_STATUS_RXRDY(sr)) {
  if (srvBufferLength < BUFFER_LENGTH)
  srvBuffer[srvBufferLength++] = TWI_ReadByte(twi);
  }
  }

  if (status == SLAVE_SEND) {
  if (TWI_STATUS_TXRDY(sr) && !TWI_STATUS_NACK(sr)) {
  uint8_t c = 'x';
  if (srvBufferIndex < srvBufferLength)
  c = srvBuffer[srvBufferIndex++];
  TWI_WriteByte(twi, c);
  }
  }
  */
}
#endif 
//setup the static globals
// these are used by the TwoWire class to initialize the Wire static globals

#if WIRE_INTERFACES_COUNT > 0
I2CClass I2C_0 = I2CClass(*WIRE0_INTERFACE, WIRE0_LOC, WIRE0_CLOCK, PIN_WIRE0_SDA, PIN_WIRE0_SCL);

#if WIRE_INTERFACES_COUNT > 1
I2CClass I2C_1 = I2CClass(*WIRE1_INTERFACE, WIRE1_LOC, WIRE1_CLOCK, PIN_WIRE1_SDA, PIN_WIRE1_SCL);

#if WIRE_INTERFACES_COUNT > 2
I2CClass I2C_2 = I2CClass(*WIRE2_INTERFACE, WIRE2_LOC, WIRE2_CLOCK, PIN_WIRE2_SDA, PIN_WIRE2_SCL);

#if WIRE_INTERFACES_COUNT > 3
I2CClass I2C_3 = I2CClass(*WIRE3_INTERFACE, WIRE3_LOC, WIRE3_CLOCK, PIN_WIRE3_SDA, PIN_WIRE3_SCL);

#endif
#endif
#endif
#endif

#if WIRE_INTERFACES_COUNT > 0

void WIRE0_ISR_HANDLER(void) {
  I2C_0.onService();
#if WIRE_INTERFACES_COUNT > 1
#if WIRE0_ISR_HANDLER == WIRE1_ISR_HANDLER
  I2C_1.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 2
#if WIRE0_ISR_HANDLER == WIRE2_ISR_HANDLER
  I2C_2.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 3
#if WIRE0_ISR_HANDLER == WIRE3_ISR_HANDLER
  I2C_3.onService();
#endif
#endif
}
#endif

#if WIRE_INTERFACES_COUNT > 1

#if WIRE0_ISR_HANDLER != WIRE1_ISR_HANDLER
void WIRE1_ISR_HANDLER(void) {
  I2C_1.onService();
#if WIRE_INTERFACES_COUNT > 2
#if WIRE1_ISR_HANDLER == WIRE2_ISR_HANDLER
  I2C_2.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 3
#if WIRE1_ISR_HANDLER == WIRE3_ISR_HANDLER
  I2C_3.onService();
#endif
#endif
}
#endif

#endif

#if WIRE_INTERFACES_COUNT > 2

#if WIRE0_ISR_HANDLER != WIRE2_ISR_HANDLER && \
	 WIRE1_ISR_HANDLER != WIRE2_ISR_HANDLER 
void WIRE2_ISR_HANDLER(void) {
  I2C_2.onService();
#if WIRE_INTERFACES_COUNT > 3
#if WIRE2_ISR_HANDLER == WIRE3_ISR_HANDLER
  I2C_3.onService();
#endif
#endif
}
#endif

#endif

#if WIRE_INTERFACES_COUNT > 3

#if WIRE0_ISR_HANDLER != WIRE3_ISR_HANDLER && \
	 WIRE1_ISR_HANDLER != WIRE3_ISR_HANDLER && \
	 WIRE2_ISR_HANDLER != WIRE3_ISR_HANDLER
void WIRE3_ISR_HANDLER(void) {
  I2C_3.onService();
}
#endif

#endif



