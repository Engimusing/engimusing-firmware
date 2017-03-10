/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"

#define DEBUGPRINTLN(x)
//#define DEBUGPRINTLN(x) Serial.println(x)


USART_InitSync_TypeDef usartInit = USART_INITSYNC_DEFAULT;

SPIClass::SPIClass(USART_TypeDef *_spi, uint32_t _id, CMU_Clock_TypeDef UartClk, const SPIPinSettings *_pinSettings) :
	spi(_spi), id(_id), pinSettings(_pinSettings), spi_clk(UartClk)
{
	
	setBitOrder(true);
	setDataMode(usartClockMode0);
	//setClockDivider(84);
	/*SPI_Configure(spi, id, SPI_MR_MSTR | SPI_MR_PS | SPI_MR_MODFDIS);
	SPI_Enable(spi);*/
}

void SPIClass::begin() {
	DEBUGPRINTLN("ASDFASDF");
	
	
	GPIO_PinModeSet(
    (GPIO_Port_TypeDef)dPorts[ pinSettings->mosiPin],
    dPins[ pinSettings->mosiPin],
    gpioModeWiredAndPullUpFilter,
   1);
   
   GPIO_PinModeSet(
    (GPIO_Port_TypeDef)dPorts[ pinSettings->misoPin],
    dPins[ pinSettings->misoPin],
    gpioModeInput,
   0);
   
   //This needs to be push pull or the CC3000 doesn't work!!!!!
	GPIO_PinModeSet(
    (GPIO_Port_TypeDef)dPorts[ pinSettings->clkPin],
    dPins[ pinSettings->clkPin],
    gpioModePushPull,
   1);

	/*//setup SPI Pins
	pinMode(
		  pinSettings->mosiPin,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(pinSettings->mosiPin, 1);
  pinMode(
		  pinSettings->misoPin,
		  gpioModeInput);
  //digitalWrite(pinSettings->misoPin, 0);
  
  pinMode(
		  35,
		  gpioModeInput);
  //digitalWrite(35, 0);

  pinMode(
		  34,
		  gpioModeInput);
  //digitalWrite(34, 0);
			
  
  
  pinMode(
		  pinSettings->clkPin,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(pinSettings->clkPin, 1);*/
		

	// NPCS control is left to the user
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(spi_clk, true);
	//CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
 
	DEBUGPRINTLN("CONFIG");
	DEBUGPRINTLN(id);
	DEBUGPRINTLN(spi_clk);
	DEBUGPRINTLN(mode[0]);
	DEBUGPRINTLN(bitOrder[0] ? 1 : 0);
	DEBUGPRINTLN("ENDCONFIG");
	
	// Default speed set to 4Mhz
	//usartInit.msbf = true;//bitOrder[0];
	//usartInit.clockMode = usartClockMode0;
	//usartInit.baudrate = 1000000;//84000000 / divider[0];
	usartInit.refFreq = 14000000;
	
	  usartInit.baudrate     = 100000;
	  //usartInit.baudrate     = 1000000;
	  usartInit.databits     = usartDatabits8;
	  usartInit.msbf         = bitOrder[0] ? 1 : 0;
	  usartInit.master       = 1;
	  usartInit.clockMode    = mode[0];
	  usartInit.prsRxEnable  = 0;
	  usartInit.autoTx       = 0;
	
	
	USART_InitSync(spi, &usartInit);
	//USART_Enable(spi, usartEnable);
	
	  // Enable receiver and transmitter
	   /* Module USART2 is configured to location 1 */
	  spi->ROUTE = id;
	  /* Enable signals TX, RX, CLK */
	  spi->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_CLKPEN | USART_ROUTE_RXPEN;
	  //
	
	//spi->CLKDIV = 0x200;
			 
		
}


void SPIClass::begin(uint8_t _pin) {

	
	pinMode(
		  _pin,
		  WIRED_AND_PU_FILTER);
  digitalWrite(_pin, 1);
	

	uint32_t ch =  0;//BOARD_PIN_TO_SPI_CHANNEL(_pin);
	
	usartInit.msbf = bitOrder[0];
	usartInit.baudrate = 84000000 / divider[0];

}

void SPIClass::end(uint8_t _pin) {
	// Setting the pin as INPUT will disconnect it from SPI peripheral
	pinMode(_pin, INPUT);
	
	CMU_ClockEnable(spi_clk, false);
}

void SPIClass::end() {
	CMU_ClockEnable(spi_clk, false);
}

void SPIClass::setBitOrder(uint8_t _pin, bool _bitOrder) {
	uint32_t ch = 0;//BOARD_PIN_TO_SPI_CHANNEL(_pin);
	bitOrder[ch] = _bitOrder;
}

void SPIClass::setDataMode(uint8_t _pin, USART_ClockMode_TypeDef _mode) {
	uint32_t ch = 0;//BOARD_PIN_TO_SPI_CHANNEL(_pin);
	mode[ch] = _mode;
	// SPI_CSR_DLYBCT(1) keeps CS enabled for 32 MCLK after a completed
	// transfer. Some device needs that for working properly.
	//SPI_ConfigureNPCS(spi, ch, mode[ch] | SPI_CSR_SCBR(divider[ch]) | SPI_CSR_DLYBCT(1));
}

void SPIClass::setClockDivider(uint8_t _pin, uint8_t _divider) {
	uint32_t ch = 0;//BOARD_PIN_TO_SPI_CHANNEL(_pin);
	divider[ch] = _divider;
	// SPI_CSR_DLYBCT(1) keeps CS enabled for 32 MCLK after a completed
	// transfer. Some device needs that for working properly.
	//SPI_ConfigureNPCS(spi, ch, mode[ch] | SPI_CSR_SCBR(divider[ch]) | SPI_CSR_DLYBCT(1));
}

byte SPIClass::transfer(byte _pin, uint8_t _data, SPITransferMode _mode) {

	//SERIAL.print(":w:");
	//DEBUGPRINTLN(_data);
	/*while (!(spi->STATUS & USART_STATUS_TXBL));
	
	spi->TXDATA = (uint32_t)_data;


	
	while (!((spi->STATUS & USART_STATUS_RXDATAV) == USART_STATUS_RXDATAV)); 
	
	uint32_t d = spi->RXDATA; */
	uint8_t out =0;

	out = USART_SpiTransfer(spi, _data);

	/*SERIAL.print("data:");
	DEBUGPRINTLN(_data);*/
	/*uint8_t out = 0;
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(PIN_SPI_MOSI, ((_data >> (7-i)) & 0x01));
		//delayMicroseconds(1);
		digitalWrite(PIN_SPI_SCK, HIGH);
		//delayMicroseconds(1);
		digitalWrite(PIN_SPI_SCK, LOW);
		out = (digitalRead(PIN_SPI_MISO) << (7-i)) | out;
	}*/
	
	
	/*SERIAL.print("read:");
	DEBUGPRINTLN(out);*/
	
    return out & 0xFF;
}

void SPIClass::attachInterrupt(void) {
	// Should be enableInterrupt()
}

void SPIClass::detachInterrupt(void) {
	// Should be disableInterrupt()
}

#if SPI_INTERFACES_COUNT > 0

const SPIPinSettings SPI0Pins = {
	PIN_SPI0_MOSI,
	PIN_SPI0_MISO,
	PIN_SPI0_SCK
};

SPIClass SPI(SPI_INTERFACE, SPI_INTERFACE_ID, SPI_CLK, &SPI0Pins
	);
#endif

#if SPI_INTERFACES_COUNT > 1

const SPIPinSettings SPI1Pins = {
	PIN_SPI1_MOSI,
	PIN_SPI1_MISO,
	PIN_SPI1_SCK
};

SPIClass SPI1(SPI1_INTERFACE, SPI1_INTERFACE_ID, SPI1_CLK,&SPI1Pins);
#endif

#if SPI_INTERFACES_COUNT > 2

const SPIPinSettings SPI2Pins = {
	PIN_SPI2_MOSI,
	PIN_SPI2_MISO,
	PIN_SPI2_SCK
};

SPIClass SPI2(SPI2_INTERFACE, SPI2_INTERFACE_ID, SPI2_CLK,&SPI2Pins);
#endif

#if SPI_INTERFACES_COUNT > 3

const SPIPinSettings SPI3Pins = {
	PIN_SPI3_MOSI,
	PIN_SPI3_MISO,
	PIN_SPI3_SCK
};

SPIClass SPI3(SPI3_INTERFACE, SPI3_INTERFACE_ID, SPI3_CLK,&SPI3Pins);
#endif