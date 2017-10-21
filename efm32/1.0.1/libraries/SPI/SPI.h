///
///@file SPI.h
///@brief Contains SPI class which is used to access the energy micro USART using the SPI protocol
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///Based on SPI.h with this copyright
///Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
///SPI Master library for arduino.
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
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>
#include <em_usart.h>

#define SPI_MODE0 usartClockMode0
#define SPI_MODE1 usartClockMode1
#define SPI_MODE2 usartClockMode2
#define SPI_MODE3 usartClockMode3

#if SPI_INTERFACES_COUNT > 0

enum SPITransferMode {
	SPI_CONTINUE,
	SPI_LAST
};

struct SPIPinSettings {
	uint8_t mosiPin;
	uint8_t misoPin;
	uint8_t clkPin;	
};

class SPIClass {
  public:
	///@brief Constructor which initializes the SPIclass. SPI.cpp uses this to initialize the default SPI objects
    ///@param [in] _spi USART to use
    ///@param [in] _id Interface ID to use
    ///@param [in] UartClk USART clock to use
    ///@param [in] _pinSettings Struct containing the pins to use
    ///@return SPI object
    SPIClass(USART_TypeDef *_spi, uint32_t _id, CMU_Clock_TypeDef UartClk, const SPIPinSettings *_pinSettings );

	///@brief Transfer data over the SPI connection
	///@param [in] _data byte to send
	///@param [in] _mode mode for the transfer (currently unused)
	///@return byte read from the SPI connection
	byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST) { return transfer(0, _data, _mode); }
	
    ///@brief Transfer data over the SPI connection
	///@param [in] _pin unused parameter
	///@param [in] _data byte to send
	///@param [in] _mode mode for the transfer (currently unused)
	///@return byte read from the SPI connection
	byte transfer(byte _pin, uint8_t _data, SPITransferMode _mode = SPI_LAST);

	// SPI Configuration methods

	///@brief No-op unused function
	void attachInterrupt(void);
	///@brief No-op unused function
	void detachInterrupt(void);

	///@brief Start the SPI connection
	void begin(void);
	///@brief Turn off the SPI clock which effectively turns off the SPI connection
    void end(void);

	///@brief Don't use this since _pins are not used for SPI yet
	void begin(uint8_t _pin);
	///@brief Don't use this since _pins are not used for SPI yet
	void end(uint8_t _pin);

	// These methods sets a parameter on a single pin
	///@brief Don't use this since _pins are not used for SPI yet
	void setBitOrder(uint8_t _pin, bool);
	///@brief Don't use this since _pins are not used for SPI yet
	void setDataMode(uint8_t _pin, USART_ClockMode_TypeDef);
	///@brief Don't use this since _pins are not used for SPI yet
	void setClockDivider(uint8_t _pin, uint8_t);

	///@brief Set the bit order to use with the SPI object
	///@param [in] _order order to use (true for most significant bit first)
	void setBitOrder(bool _order) { setBitOrder(0, _order); };
	
	    
    ///@brief Set data mode
	///@param [in] _mode data mode to use
	void setDataMode(USART_ClockMode_TypeDef _mode) { setDataMode(0, _mode); };
	
    ///@brief Set the clock divider to specify the clock for the SPI bus
    ///@param [in] _div Divider value to use
    void setClockDivider(uint8_t _div) { setClockDivider(0, _div); };

  private:
  
  	
  
  CMU_Clock_TypeDef spi_clk;
	USART_TypeDef *spi;
	uint32_t id;
	bool bitOrder[SPI_CHANNELS_NUM];
	uint32_t divider[SPI_CHANNELS_NUM];
	USART_ClockMode_TypeDef mode[SPI_CHANNELS_NUM];
	const SPIPinSettings *pinSettings;
	
};

#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif

#if SPI_INTERFACES_COUNT > 1
extern SPIClass SPI1;
#endif

#if SPI_INTERFACES_COUNT > 2
extern SPIClass SPI2;
#endif

#if SPI_INTERFACES_COUNT > 3
extern SPIClass SPI3;
#endif

#endif

#endif