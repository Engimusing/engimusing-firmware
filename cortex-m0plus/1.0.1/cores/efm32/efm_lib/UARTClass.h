/*
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

#ifndef _UART_CLASS_
#define _UART_CLASS_

#include "HardwareSerial.h"
#include "RingBuffer.h"

// Includes Atmel CMSIS
#include <em_device.h>
#include "efm_cmu_config.h"

typedef USART_TypeDef Uart;
typedef LEUART_TypeDef Leuart;



class UARTClass : public HardwareSerial
{
 protected:
    RingBuffer *_rx_buffer ;

	enum BreakCommandState
	{
			Idle,
			BreakReceived,
			ResetReceived
	};
	
 protected:
    Uart* _pUart ;
    Leuart* _pLeuart ;
    IRQn_Type _dwIrq ;
    uint32_t _UartLoc;
    CMU_Clock_TypeDef _UartClk;
    bool _loopback;
	int _breakCommandState;
	//const char *_id;
 public:
    UARTClass( Uart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk, bool loopback );
    UARTClass( Uart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk );
    UARTClass( Leuart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk );
	
    void begin( const uint32_t dwBaudRate ) ;
    void end( void ) ;
    int available( void ) ;
    int peek( void ) ;
    int read( void ) ;
    void flush( void ) ;
    size_t write( const uint8_t c ) ;

    void IrqHandler( void ) ;
	bool isResetReceived( void );
#if defined __GNUC__ /* GCC CS3 */
    using Print::write ; // pull in write(str) and write(buf, size) from Print
#elif defined __ICCARM__ /* IAR Ewarm 5.41+ */
    //    virtual void write( const char *str ) ;
    //    virtual void write( const uint8_t *buffer, size_t size ) ;
#endif

    operator bool() { return true; }; // UART always active
};

extern UARTClass Serial;
extern UARTClass Serial1;

extern void serialEventRun(void) __attribute__((weak));
extern void serialEvent() __attribute__((weak));
/*void serialEventRun(void)
  {
  if (Serial.available() && serialEvent) serialEvent();

  }
*/
#endif // _UART_CLASS_
