/*
  Copyright (c) 2015 Engimusing.  All right reserved.
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LEUARTClass.h"
#include "Arduino.h"

#include "RingBuffer.h"


#include "HardwareSerial.h"


// Constructors ////////////////////////////////////////////////////////////////

LEUARTClass::LEUARTClass(Leuart *pUart, IRQn_Type dwIrq, uint32_t dwId, RingBuffer *pRx_buffer, RingBuffer *pTx_buffer, uint8_t port, uint8_t txpin, uint8_t rxpin, uint32_t location, uint32_t cmu_clken)
{
  _rx_buffer = pRx_buffer;
  _tx_buffer = pTx_buffer;

  _pUart     = pUart;
  _dwIrq     = dwIrq;
  _dwId      = dwId;
  _port      = port;
  _txpin     = txpin;
  _rxpin     = rxpin;
  _location  = location;
  _cmu_clken = cmu_clken;
}

// Public Methods //////////////////////////////////////////////////////////////

void LEUARTClass::begin(const uint32_t dwBaudRate)
{
  begin(dwBaudRate, SERIAL_8N1);
}

void LEUARTClass::begin(const uint32_t dwBaudRate, uint8_t config)
{
  init(dwBaudRate, config);
}

void LEUARTClass::init(const uint32_t dwBaudRate, uint8_t config)
{
  // LEUART configure
  GPIO->P[_port].DOUTSET = (1 << _txpin);  // LEUART_TX high to avoid false start
  GPIO_config(_port, _txpin, OUTPUT);      // LEUART_TX output
  GPIO_config(_port, _rxpin, INPUT);       // LEUART_RX input
  CMU->LFBCLKEN0 |= _cmu_clken;
  _pUart->IFC = _LEUART_IFC_MASK;  // clear ints
  _pUart->IEN |= LEUART_IEN_RXDATAV;    // enable ints
  NVIC_EnableIRQ(_dwIrq);
  NVIC_ClearPendingIRQ(_dwIrq);
  _pUart->CLKDIV = LEUART_CLKDIV;
  _pUart->ROUTE  = _location | LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN;
  _pUart->CMD    = LEUART_CMD_RXEN | LEUART_CMD_TXEN;

  // Make sure both ring buffers are initialized back to empty.
  _rx_buffer->_iHead = _rx_buffer->_iTail = 0;
  _tx_buffer->_iHead = _tx_buffer->_iTail = 0;
}

void LEUARTClass::end( void )
{
  // Clear any received data
  _rx_buffer->_iHead = _rx_buffer->_iTail;

  // Wait for any outstanding data to be sent
  flush();

  // Disable UART interrupt in NVIC
  NVIC_DisableIRQ( _dwIrq );

  CMU->LFBCLKEN0 &= ~_cmu_clken;
}

void LEUARTClass::setInterruptPriority(uint32_t priority)
{
  NVIC_SetPriority(_dwIrq, priority & 0x0F);
}

uint32_t LEUARTClass::getInterruptPriority()
{
  return NVIC_GetPriority(_dwIrq);
}

int LEUARTClass::available( void )
{
  return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) & SERIAL_BUFFER_MASK;
}

int LEUARTClass::availableForWrite(void)
{
  int head = _tx_buffer->_iHead;
  int tail = _tx_buffer->_iTail;
  if (head >= tail) return SERIAL_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

int LEUARTClass::peek( void )
{
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1;

  return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int LEUARTClass::read( void )
{
  // if the head isn't ahead of the tail, we don't have any characters
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1;

  uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
  _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
  return uc;
}

void LEUARTClass::flush( void )
{
  while (_tx_buffer->_iHead != _tx_buffer->_iTail); //wait for transmit data to be sent
  // Wait for transmission to complete
  while((_pUart->STATUS & LEUART_STATUS_TXBL) != LEUART_STATUS_TXBL)
    ;
}


size_t LEUARTClass::write( const uint8_t uc_data )
{
  // Is the hardware currently busy?
  if (((_pUart->STATUS & LEUART_STATUS_TXBL) != LEUART_STATUS_TXBL) |
      (_tx_buffer->_iTail != _tx_buffer->_iHead))
    {
      // If busy we buffer
      unsigned int l = (_tx_buffer->_iHead + 1) & SERIAL_BUFFER_MASK;
      while (_tx_buffer->_iTail == l)
	; // Spin locks if we're about to overwrite the buffer. This continues once the data is sent

      _tx_buffer->_aucBuffer[_tx_buffer->_iHead] = uc_data;
      _tx_buffer->_iHead = l;
      // Make sure TX interrupt is enabled
      _pUart->IEN |= LEUART_IEN_TXBL;  // Enable interrupt on SERIAL TX Buffer
    }
  else 
    {
      // Bypass buffering and send character directly
      _pUart->TXDATA = uc_data;
    }
  return 1;
}


void LEUARTClass::IrqHandler( void )
{
  uint32_t status = _pUart->STATUS;

  // Did we receive data?
  if ((status & LEUART_STATUS_RXDATAV) == LEUART_STATUS_RXDATAV) {
    int i = (uint32_t)(_rx_buffer->_iHead + 1) & SERIAL_BUFFER_MASK;
    if ( i != _rx_buffer->_iTail ) {
      _rx_buffer->_aucBuffer[_rx_buffer->_iHead] = _pUart->RXDATA ;
      _rx_buffer->_iHead = i ;
    }
  }
  // Do we need to keep sending data?
  if ((status & LEUART_STATUS_TXBL) == LEUART_STATUS_TXBL) 
    {
      if (_tx_buffer->_iTail != _tx_buffer->_iHead) {
	_pUart->TXDATA = _tx_buffer->_aucBuffer[_tx_buffer->_iTail];
	_tx_buffer->_iTail = (unsigned int)(_tx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
      }
      else
	{
	  // Mask off transmit interrupt so we don't get it anymore
	  _pUart->IEN &= ~LEUART_IEN_TXBL;
	}
    }

  // Acknowledge errors
  if(_pUart->RXDATAXP & LEUART_RXDATAXP_FERRP)
    SCB->AIRCR = 0x05FA0004;  // Write to the Application Interrupt/Reset Command Register to reset
}

