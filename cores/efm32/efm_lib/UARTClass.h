///
///@file UARTClass.h
///@brief Contains UARTClass which is used for Serial port communication
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2011 Arduino.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///

#ifndef _UART_CLASS_
#define _UART_CLASS_

#include "HardwareSerial.h"
#include "RingBuffer.h"

// Includes Atmel CMSIS
#include <em_device.h>
#include "efm_cmu_config.h"

typedef USART_TypeDef Uart;
typedef LEUART_TypeDef Leuart;


///@brief Class for accessing the UART peripherals on the Energy Micro
/// derived from HardwareSerial
class UARTClass : public HardwareSerial
{
 
 protected:
    
	///@brief Brief description
	enum BreakCommandState
	{
			Idle,
			BreakReceived,
			ResetReceived
	};	

 public:
 
    ///@brief Constructor for creating and configuring the USARTClass object which use a UART. There are many pre-initialized objects like Serial. 
    ///@param [in] pUart Specify the UART peripheral to use. Only parameter that is different between the two contructors.
    ///@param [in] dwIrq IRQ to use. Pass in one of the USARTn_RX_IRQn defines.
    ///@param [in] pRx_buffer RingBuffer object to use for this USARTClass object. It should only be used for a single USARTClass object
    ///@param [in] UartLoc Location id to use. Pass in one of the USART_ROUTE_LOCATION defines. 
    ///@param [in] UartClk Clock to use. Pass in one of the cmuClock_USART defines.
    ///@param [in] txPin transmit pin that matches the location specified by UartLoc. Uses a pin index from the pins_ardunio files. Default = 0
    ///@param [in] rxPin receive pin that matches the location specified by UartLoc. Uses a pin index from the pins_ardunio files. Default = 0
    ///@return UARTClass object
    UARTClass( Uart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk, unsigned int txPin = 0, unsigned int rxPin = 0 );
    
    ///@brief Constructor for creating and configuring the USARTClass object which use a LEUART. There are many pre-initialized objects like Serial. 
    ///@param [in] pUart Specify the LEUART peripheral to use. Only parameter that is different between the two contructors.
    ///@param [in] dwIrq IRQ to use. Pass in one of the LEUARTn_IRQn defines.
    ///@param [in] pRx_buffer RingBuffer object to use for this USARTClass object. It should only be used for a single USARTClass object
    ///@param [in] UartLoc Location id to use. Pass in one of the LEUART_ROUTE_LOCATION defines. 
    ///@param [in] UartClk Clock to use. Pass in one of the cmuClock_LEUART0 defines.
    ///@param [in] txPin transmit pin that matches the location specified by UartLoc. Uses a pin index from the pins_ardunio files. Default = 0
    ///@param [in] rxPin receive pin that matches the location specified by UartLoc. Uses a pin index from the pins_ardunio files. Default = 0
    ///@return UARTClass object
    UARTClass( Leuart* pUart, IRQn_Type dwIrq, RingBuffer* pRx_buffer, uint32_t UartLoc, CMU_Clock_TypeDef UartClk, unsigned int txPin = 0, unsigned int rxPin = 0 );
	
    ///@brief Initializes the UARTClass object and starts it receiving data
    ///@param [in] dwBaudRate Baud rate to use for the Serial port. 115200 is the default and used by the IDE for programming
    ///@details Important!!!! Setting the baud rate for the Serial or Serial1 objects to anything but 115200 will prevent them
    /// from being able to be programmed using the Arduino IDE unless they are reset manually.
    void begin( const uint32_t dwBaudRate ) ;
    
    ///@brief Clear the internal buffer and stop the Serial port from recieving any data.
    void end( void ) ;
   
    ///@brief Check for any received data available in the buffer
    ///@return Number of bytes available
    int available( void ) ;
    
    ///@brief Read the next byte without removing it from the buffer
    ///@return Next available received byte, -1 if there is no data available
    int peek( void ) ;
    
    ///@brief Read the next byte and remove it from the buffer
    ///@return Next available received byte, -1 if there is no data available
    int read( void ) ;
    
    ///@brief Stall until all data has been transmitted
    void flush( void ) ;
    
    ///@brief Write a byte to the serial port. Stalls until the peripheral is ready to accept the byte.
    ///@param [in] uc_data byte to write to the serial port.
    ///@return 1, currently always returns 1. Part of the HardwareSerial interface
    size_t write( const uint8_t uc_data ) ;

	///@brief Called by the interrupt handler to process the reason for the interrupt
	///@details Handles the reset logic as well. If a check_for_reset function is setup then it will call it if a reset command is received (Break+r)
	/// Also does nothing (received bytes are discarded) if the SerialPort has not been fully setup yet. 
	void IrqHandler( void ) ;
	
    ///@brief Did the IrqHandler detect a reset command
    ///@return true if the IrqHandler has detected a reset command, false otherwise
    bool isResetReceived( void );
    
    ///@brief Is the UARTClass started
    ///@return True if between a begin() and an end() call for this UARTClass, false otherwise
    bool hasBegun();
    
#if defined __GNUC__ /* GCC CS3 */
    using Print::write ; // pull in write(str) and write(buf, size) from Print
#elif defined __ICCARM__ /* IAR Ewarm 5.41+ */
    //    virtual void write( const char *str ) ;
    //    virtual void write( const uint8_t *buffer, size_t size ) ;
#endif

    ///@brief UART always active
    ///@return true
    operator bool() { return true; };
    
 protected:
 
    RingBuffer *_rx_buffer ;
    Uart* _pUart ;
    Leuart* _pLeuart ;
    IRQn_Type _dwIrq ;
    uint32_t _UartLoc;
    CMU_Clock_TypeDef _UartClk;
    bool _loopback;
	BreakCommandState _breakCommandState;
    unsigned int _txPin;
    unsigned int _rxPin;
    bool _begun;
    
};

extern UARTClass Serial;
extern UARTClass Serial1;
extern UARTClass Serial2;
extern UARTClass Serial3;
extern UARTClass Serial4;
extern UARTClass SerialDF11_0;
extern UARTClass SerialDF11_1;
extern UARTClass SerialDF11_2;
extern UARTClass SerialDF11_3;

///@brief Function defined in the variant.cpp for the device
extern void serialEventRun(void) __attribute__((weak));
///@brief Can be defined in a sketch to run whenever data arrives on any Serial port
extern void serialEvent() __attribute__((weak));

#endif // _UART_CLASS_
