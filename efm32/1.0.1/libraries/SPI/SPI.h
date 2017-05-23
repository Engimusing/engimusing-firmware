/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

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
	SPIClass(USART_TypeDef *_spi, uint32_t _id, CMU_Clock_TypeDef UartClk, const SPIPinSettings *_pinSettings );

	byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST) { return transfer(0, _data, _mode); }
	byte transfer(byte _pin, uint8_t _data, SPITransferMode _mode = SPI_LAST);

	// SPI Configuration methods

	void attachInterrupt(void);
	void detachInterrupt(void);

	void begin(void);
	void end(void);

	// Attach/Detach pin to/from SPI controller
	void begin(uint8_t _pin);
	void end(uint8_t _pin);

	// These methods sets a parameter on a single pin
	void setBitOrder(uint8_t _pin, bool);
	void setDataMode(uint8_t _pin, USART_ClockMode_TypeDef);
	void setClockDivider(uint8_t _pin, uint8_t);

	// These methods sets the same parameters but on default pin BOARD_SPI_DEFAULT_SS
	void setBitOrder(bool _order) { setBitOrder(0, _order); };
	void setDataMode(USART_ClockMode_TypeDef _mode) { setDataMode(0, _mode); };
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