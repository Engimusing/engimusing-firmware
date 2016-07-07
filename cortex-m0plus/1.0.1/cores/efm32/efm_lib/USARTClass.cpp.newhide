/*
  Copyright (c) 2016 Engimusing.  All right reserved.
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

#include "USARTClass.h"
#include "variant.h"


// Constructors ////////////////////////////////////////////////////////////////

USARTClass::USARTClass(Usart *pUart, IRQn_Type dwTxIrq, IRQn_Type dwRxIrq, uint32_t dwId, RingBuffer *pRx_buffer, 
		       RingBuffer *pTx_buffer, uint8_t port, uint8_t txpin, uint8_t rxpin, uint32_t location,
		       uint32_t cmu_clken, uint32_t usart_clkdiv) 
{
  _rx_buffer = pRx_buffer;
  _tx_buffer = pTx_buffer;

  _pUart     = pUart;
  _dwTxIrq   = dwTxIrq;
  _dwRxIrq   = dwRxIrq;
  _dwId      = dwId;
  _port      = port;
  _txpin     = txpin;
  _rxpin     = rxpin;
  _location  = location;
  _cmu_clken = cmu_clken;
  _clkdiv    = usart_clkdiv;
}

// Public Methods //////////////////////////////////////////////////////////////

void USARTClass::begin(const uint32_t dwBaudRate)
{
  begin(dwBaudRate, SERIAL_8N1);
}

void USARTClass::begin(const uint32_t dwBaudRate, uint32_t config)
{
  init(dwBaudRate, config);
}

void USARTClass::init(const uint32_t dwBaudRate, uint32_t config)
{
  // USART configure
  if((dwBaudRate == 115200) && (config == SERIAL_8N1)) {
    GPIO->P[_port].DOUTSET = (1 << _txpin);  // USART_TX high to avoid false start
    GPIO_config(_port, _txpin, OUTPUT);      // USART_TX output
    GPIO_config(_port, _rxpin, INPUT);       // USART_RX input
    CMU->HFPERCLKEN0 |= _cmu_clken;
    _pUart->IFC = _USART_IFC_MASK;  // clear ints
    _pUart->IEN |= USART_IEN_RXDATAV;    // enable ints
    NVIC_EnableIRQ(_dwTxIrq);
    NVIC_ClearPendingIRQ(_dwTxIrq);
    NVIC_EnableIRQ(_dwRxIrq);
    NVIC_ClearPendingIRQ(_dwRxIrq);
    _pUart->CLKDIV = _clkdiv;
    _pUart->ROUTE  = _location | USART_ROUTE_RXPEN | USART_ROUTE_TXPEN;
    _pUart->CMD    = USART_CMD_RXEN | USART_CMD_TXEN;

    // Make sure both ring buffers are initialized back to empty.
    _rx_buffer->_iHead = _rx_buffer->_iTail = 0;
    _tx_buffer->_iHead = _tx_buffer->_iTail = 0;
  }
}

void USARTClass::end( void )
{
  // Clear any received data
  _rx_buffer->_iHead = _rx_buffer->_iTail;

  // Wait for any outstanding data to be sent
  flush();

  // Disable UART interrupt in NVIC
  NVIC_DisableIRQ( _dwTxIrq );
  NVIC_DisableIRQ( _dwRxIrq );

  CMU->HFPERCLKEN0 &= ~_cmu_clken;
}

int USARTClass::available( void )
{
  return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) & SERIAL_BUFFER_MASK;
}

int USARTClass::availableForWrite(void)
{
  int head = _tx_buffer->_iHead;
  int tail = _tx_buffer->_iTail;
  if (head >= tail) return SERIAL_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

int USARTClass::peek( void )
{
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1;

  return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int USARTClass::read( void )
{
  // if the head isn't ahead of the tail, we don't have any characters
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1;

  uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
  _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
  return uc;
}

void USARTClass::flush( void )
{
  while (_tx_buffer->_iHead != _tx_buffer->_iTail); //wait for transmit data to be sent
  // Wait for transmission to complete
  while((_pUart->STATUS & USART_STATUS_TXBL) != USART_STATUS_TXBL)
    ;
}


size_t USARTClass::write( const uint8_t uc_data )
{
  // Is the hardware currently busy?
  if (((_pUart->STATUS & USART_STATUS_TXBL) != USART_STATUS_TXBL) |
      (_tx_buffer->_iTail != _tx_buffer->_iHead))
    {
      // If busy we buffer
      unsigned int l = (_tx_buffer->_iHead + 1) & SERIAL_BUFFER_MASK;
      while (_tx_buffer->_iTail == l)
	; // Spin locks if we're about to overwrite the buffer. This continues once the data is sent

      _tx_buffer->_aucBuffer[_tx_buffer->_iHead] = uc_data;
      _tx_buffer->_iHead = l;
      // Make sure TX interrupt is enabled
      _pUart->IEN |= USART_IEN_TXBL;  // Enable interrupt on SERIAL TX Buffer
    }
  else 
    {
      // Bypass buffering and send character directly
      _pUart->TXDATA = uc_data;
    }
  return 1;
}

void USARTClass::IrqTxHandler( void )
{
  uint32_t status = _pUart->STATUS;

  // Do we need to keep sending data?
  if ((status & USART_STATUS_TXBL) == USART_STATUS_TXBL) 
    {
      if (_tx_buffer->_iTail != _tx_buffer->_iHead) {
	_pUart->TXDATA = _tx_buffer->_aucBuffer[_tx_buffer->_iTail];
	_tx_buffer->_iTail = (unsigned int)(_tx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
      }
      else
	{
	  // Mask off transmit interrupt so we don't get it anymore
	  _pUart->IEN &= ~USART_IEN_TXBL;
	}
    }

  // Acknowledge errors
  if(_pUart->RXDATAXP & USART_RXDATAXP_FERRP)
    SCB->AIRCR = 0x05FA0004;  // Write to the Application Interrupt/Reset Command Register to reset
}


void USARTClass::IrqRxHandler( void )
{
  uint32_t status = _pUart->STATUS;

  // Do we need to keep sending data?
  if ((status & USART_STATUS_TXBL) == USART_STATUS_TXBL) 
    {
      if (_tx_buffer->_iTail != _tx_buffer->_iHead) {
	_pUart->TXDATA = _tx_buffer->_aucBuffer[_tx_buffer->_iTail];
	_tx_buffer->_iTail = (unsigned int)(_tx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
      }
      else
	{
	  // Mask off transmit interrupt so we don't get it anymore
	  _pUart->IEN &= ~USART_IEN_TXBL;
	}
    }
}


