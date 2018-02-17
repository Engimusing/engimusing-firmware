/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
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
#include "UARTClass.h"
#include "Arduino.h"
#include "efm_usart.h"
#include "efm_leuart.h"

//#define USART_IntEnable //
//#define NVIC_ClearPendingIRQ //
//#define NVIC_EnableIRQ //
//#define LEUART_Init //
//#define USART_InitAsync //

extern void check_for_reset ( void ) __attribute__((weak));

// Constructors ////////////////////////////////////////////////////////////////

UARTClass::UARTClass( Uart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk, unsigned int txPin, unsigned int rxPin)
{
  _rx_buffer = pRx_buffer ;

  _pUart=pUart ;
  _dwIrq=dwIrq ;
  _UartLoc = UartLoc;
  _UartClk = UartClk;
  _loopback = false;
  _breakCommandState = Idle;
  _txPin = txPin;
  _rxPin = rxPin;
  _begun = false;
  //_id =  (char*)"{EMUS;ADXL_0;ADXL_1;ADXL_2;TMP_0;ASDF_0}";
}

UARTClass::UARTClass( Leuart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk, unsigned int txPin, unsigned int rxPin)
{
  _rx_buffer = pRx_buffer ;

  _pUart=0;
  _pLeuart=pUart ;
  _dwIrq=dwIrq ;
  _UartLoc = UartLoc;
  _UartClk = UartClk;
  _breakCommandState = Idle;
  _txPin = txPin;
  _rxPin = rxPin;
  _begun = false;
  //_id = (char*)"{EMUS;ADXL_0;ADXL_1;ADXL_2;TMP_0;ASDF_0}";
}

// Public Methods //////////////////////////////////////////////////////////////

void UARTClass::begin( const uint32_t dwBaudRate )
{
	
	//for now lets not allow any other baudrates!!!!! 
	// Remove before distributing to customers!!!!!
	//if(dwBaudRate != 115200)
	//	return;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
  // Configure PMC
	if(_txPin > 0)
    {
        GPIO_PinModeSet(
        (GPIO_Port_TypeDef)dPorts[ _txPin],
        dPins[ _txPin],
        gpioModePushPull,
       1);
    }
    if(_rxPin > 0)
    {
        GPIO_PinModeSet(
        (GPIO_Port_TypeDef)dPorts[ _rxPin],
        dPins[ _rxPin],
        gpioModeInput,
       0);
    }
    
  if(_pUart)
    {
	//NOTE TO SELF Make sure there are rs232 recievers on both ends or niether end when attempting to use UART/LEUART
      CMU_ClockEnable(cmuClock_HFPER, true);
      CMU_ClockEnable(_UartClk, true);
      USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

      uartInit.baudrate = dwBaudRate;
      USART_InitAsync(_pUart, &uartInit);
  
      // Enable receiver and transmitter
      _pUart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | 
	_UartLoc;
      if(_loopback)
	{
	  _pUart->CTRL |=  USART_CTRL_LOOPBK;
	}
      USART_IntEnable(_pUart,USART_IF_RXDATAV);
      USART_IntClear(_pUart,USART_IF_RXDATAV);

      // Enable UART interrupt in NVIC
      NVIC_ClearPendingIRQ(_dwIrq);
      NVIC_EnableIRQ(_dwIrq);
    }
  else
    {
		//NOTE TO SELF Make sure there are rs232 recievers on both ends or niether end when attempting to use UART/LEUART

		/* Enable High Frequency Peripherals */
		CMU_ClockEnable(cmuClock_HFPER, true);

		/* Enable clocks to GPIO */
		CMU_ClockEnable(cmuClock_GPIO, true);


		CMU_ClockEnable(_UartClk, true);

		/* Enable CORE LE clock in order to access LE modules */
		CMU_ClockEnable(cmuClock_CORELE, true);

		if(dwBaudRate > 9600) //baudrate will = 115200 if it is greater than 9600
		{
			CMU_ClockSelectSet( cmuClock_LFB, cmuSelect_CORELEDIV2 );
		}  else //Baudrates between 300 and 9600 should work with the low frequency clock
		{
			/* Enable LFRCO oscillator */
			CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

			/* Select LFRCO as clock source for LFBCLK */
			CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO);
		}
#if defined(EFM32TG)  || defined(EFM32ZG)
		if(_UartLoc == LEUART_ROUTE_LOCATION_LOC3)
		{
			//if it is LOC3 than it is shared with the debug IO pins on the TG222 and ZG222 so disable them after a 3 second delay 
			delay(3000);
			GPIO->ROUTE &= ~(GPIO_ROUTE_SWDIOPEN | GPIO_ROUTE_SWCLKPEN);
		}
#endif

		LEUART_Init_TypeDef leuartInit = LEUART_INIT_DEFAULT;
		leuartInit.baudrate = dwBaudRate;
		leuartInit.enable = leuartDisable;
		LEUART_Init(_pLeuart, &leuartInit);

		// Enable receiver and transmitter

		_pLeuart->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN | _UartLoc;

		LEUART_IntEnable(_pLeuart,LEUART_IF_RXDATAV);
		LEUART_IntClear(_pLeuart,LEUART_IF_RXDATAV);
		NVIC_ClearPendingIRQ(_dwIrq);
		NVIC_EnableIRQ(_dwIrq);

		LEUART_Enable(_pLeuart, leuartEnable);

    }
    
    _begun = true;
}



void UARTClass::end( void )
{
  // clear any received data
  _rx_buffer->_iHead = _rx_buffer->_iTail ;

  // Disable UART interrupt in NVIC
  NVIC_DisableIRQ( _dwIrq ) ;

  // Wait for any outstanding data to be sent
  flush();

  CMU_ClockEnable(_UartClk, false);
  
  _begun = false;
}

int UARTClass::available( void )
{
  return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) & SERIAL_BUFFER_MASK ;
}

int UARTClass::peek( void )
{
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1 ;

  return _rx_buffer->_aucBuffer[_rx_buffer->_iTail] ;
}

int UARTClass::read( void )
{
  // if the head isn't ahead of the tail, we don't have any characters
  if ( _rx_buffer->_iHead == _rx_buffer->_iTail )
    return -1 ;
	 
  uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail] ;
  _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) & SERIAL_BUFFER_MASK;
  return uc ;
}

void UARTClass::flush( void )
{
  // Wait for transmission to complete
  if(_pUart)
    {
      while (!(_pUart->STATUS & USART_STATUS_TXBL));
    }else
    {
      while (!(_pLeuart->STATUS & LEUART_STATUS_TXBL));
    }
}

size_t UARTClass::write( const uint8_t uc_data )
{
  
  // Check if the transmitter is ready
  if(_pUart)
    {
      while (!(_pUart->STATUS & USART_STATUS_TXBL));
      _pUart->TXDATA = (uint32_t)uc_data;
    }else
    {

      while (!(_pLeuart->STATUS & LEUART_STATUS_TXBL));
      _pLeuart->TXDATA = (uint32_t)uc_data;
	
    }
  return 1;
}

void UARTClass::IrqHandler( void )
{
  int readData = 0;
  bool breakReceived = false;
  // Did we receive data ?
  if(_pUart)
    {
      USART_IntClear(_pUart,USART_IF_RXDATAV);
	  
      if ((_pUart->STATUS & USART_STATUS_RXDATAV) == USART_STATUS_RXDATAV)	  
      {
          readData = _pUart->RXDATAX;
      }
	  
	  breakReceived = ((USART_RXDATAX_FERR & readData) != 0) && _begun;
	  
    }else
    {
      LEUART_IntClear(_pLeuart,LEUART_IF_RXDATAV);

      if ((_pLeuart->STATUS & LEUART_STATUS_RXDATAV) == LEUART_STATUS_RXDATAV) 
      {
          readData = _pLeuart->RXDATAX;
      }
	  
	  breakReceived = ((LEUART_RXDATAX_FERR & readData) != 0) && _begun;	  
	  
    }

	if(breakReceived)
	{
		_breakCommandState = BreakReceived;
	}else if(_breakCommandState == BreakReceived && ((0xFF & readData) == 'r'))
	{
		_breakCommandState = ResetReceived;
		if(check_for_reset) check_for_reset();
	}/*else if(_breakCommandState == BreakReceived && ((0xFF & readData) == 'i'))
	{
		int i = 0;
		while(_id[i] != '\0' && i < 50)
		{
			write(_id[i]);
			i++;
		}
		_breakCommandState = Idle;
	}*/else if(_breakCommandState == BreakReceived)
	{
		_breakCommandState = Idle;
	}
	
	if(_begun)
    {
        _rx_buffer->store_char(readData & 0xFF); 
    }
	
	
}

bool UARTClass::isResetReceived()
{
	return _breakCommandState == ResetReceived;
}

bool UARTClass::hasBegun()
{
    return _begun;
}
