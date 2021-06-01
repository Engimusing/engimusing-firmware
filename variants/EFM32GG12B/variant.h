/*
  Copyright (c) 2014-2015 Engimusing LLC.  All right reserved.
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"

#define LED_BUILTIN 35

#define EFMZG_LEUART_CLKDIV 0x59D0
#define EFMTG_LEUART_CLKDIV 0x77C0
#define EFMWG_LEUART_CLKDIV 0x77C0
#define EFMGG_LEUART_CLKDIV 0x5177
#define LEUART_CLKDIV EFMGG_LEUART_CLKDIV

#define ADC_RESOLUTION		0



static const uint8_t A0  = 1; //A0
static const uint8_t A1  = 2; //A1
static const uint8_t A2  = 3; //A2
static const uint8_t A3  = 4; //A3
static const uint8_t A4  = 5; //A4
static const uint8_t A5  = 6; //A5 //Pins C0-C5 did not work on the first try so skipping for now
static const uint8_t A6  = 17; //A8
static const uint8_t A7  = 18; //A9
static const uint8_t A8  = 19; //A10
static const uint8_t A9  = 21; //B11
static const uint8_t A10  = 24; //B13
static const uint8_t A11  = 25; //B14
static const uint8_t A12  = 49; //F0 //DBG connection pin
static const uint8_t A13  = 50; //F1 //DBG connection pin
static const uint8_t A14  = 51; //F2 //DBG connection pin
static const uint8_t A15  = 52; //F3
static const uint8_t A16  = 53; //F4
static const uint8_t A17  = 54; //F5
static const uint8_t A18  = 57; //E8
static const uint8_t A19  = 58; //E9
static const uint8_t A20  = 59; //E10
static const uint8_t A21  = 60; //E11
static const uint8_t A22  = 61; //E12
static const uint8_t A23  = 62; //E13
static const uint8_t A24  = 63; //E14
static const uint8_t A25  = 64; //E15

#define ADC_RESOLUTION		12
/*
// DACC

#define DACC_INTERFACE		DACC
#define DACC_INTERFACE_ID	ID_DACC
#define DACC_RESOLUTION		12
#define DACC_ISR_HANDLER    DACC_Handler
#define DACC_ISR_ID         DACC_IRQn


// PWM Resolution

#define PWM_INTERFACE        PWM
#define PWM_INTERFACE_ID     ID_PWM
#define PWM_FREQUENCY	     1000
#define PWM_MAX_DUTY_CYCLE   255
#define PWM_MIN_DUTY_CYCLE   0
#define PWM_RESOLUTION	     16
*/

// Wire Interfaces (I2C)

#define WIRE_INTERFACES_COUNT 0

#define PIN_WIRE0_SDA         (13u) //PD6
#define PIN_WIRE0_SCL         (14u) //PD7
#define WIRE0_INTERFACE       I2C1
#define WIRE0_LOC    0
#define WIRE0_ISR_HANDLER     I2C1_Handler
#define WIRE0_CLOCK				cmuClock_I2C1

#define PIN_WIRE1_SDA         (1u) //PD6
#define PIN_WIRE1_SCL         (2u) //PD7
#define WIRE1_INTERFACE       I2C0
#define WIRE1_LOC    0
#define WIRE1_ISR_HANDLER     I2C0_Handler
#define WIRE1_CLOCK				cmuClock_I2C0

#define PIN_WIRE2_SDA         (21u) //PD6
#define PIN_WIRE2_SCL         (22u) //PD7
#define WIRE2_INTERFACE       I2C1
#define WIRE2_LOC    1
#define WIRE2_ISR_HANDLER     I2C1_Handler
#define WIRE2_CLOCK				cmuClock_I2C1

#define PIN_WIRE3_SDA         (34u) //PD6
#define PIN_WIRE3_SCL         (35u) //PD7
#define WIRE3_INTERFACE       I2C0
#define WIRE3_LOC    1
#define WIRE3_ISR_HANDLER     I2C0_Handler
#define WIRE3_CLOCK				cmuClock_I2C0


//for the 4 DF11 board each of these is one of the DF11 connections.
// SPI 0 is the top left connection when the board has the RS232 on the left and the 
// Energy Micro on top. Then the rest of the SPI go counter clockwise from there.
// On this particular board SPI 1,2, and 3 cannot be used at the same time since they us the same USART
#define SPI_INTERFACES_COUNT 0

#define SPI_INTERFACE        USART2
#define SPI_INTERFACE_ID     USART_ROUTE_LOCATION_LOC1
#define SPI_CLK	cmuClock_USART2
#define SPI_CHANNELS_NUM 1
#define PIN_SPI0_MOSI 9
#define PIN_SPI0_MISO 10
#define PIN_SPI0_SCK 11

#define SPI1_INTERFACE        USART0
#define SPI1_INTERFACE_ID     USART_ROUTE_LOCATION_LOC4
#define SPI1_CLK	cmuClock_USART0
#define SPI1_CHANNELS_NUM 1
#define PIN_SPI1_MOSI 15
#define PIN_SPI1_MISO 16
#define PIN_SPI1_SCK 24

#define SPI2_INTERFACE        USART0
#define SPI2_INTERFACE_ID     USART_ROUTE_LOCATION_LOC1
#define SPI2_CLK	cmuClock_USART0
#define SPI2_CHANNELS_NUM 1
#define PIN_SPI2_MOSI 44
#define PIN_SPI2_MISO 43
#define PIN_SPI2_SCK 42

#define SPI3_INTERFACE        USART0
#define SPI3_INTERFACE_ID     USART_ROUTE_LOCATION_LOC0
#define SPI3_CLK	cmuClock_USART0
#define SPI3_CHANNELS_NUM 1
#define PIN_SPI3_MOSI 58
#define PIN_SPI3_MISO 59
#define PIN_SPI3_SCK 60

//There line up with the 4 SPI's defined above.
#define CC3000_INTERFACES_COUNT 0
/*
#define PIN_CC3000_0_CS 12
#define PIN_CC3000_0_IRQ 33
#define PIN_CC3000_0_VBAT 46
#define CC3000_0_SPI SPI

#define PIN_CC3000_1_CS 25
#define PIN_CC3000_1_IRQ 19
#define PIN_CC3000_1_VBAT 48
#define CC3000_1_SPI SPI1

#define PIN_CC3000_2_CS 41
#define PIN_CC3000_2_IRQ 30
#define PIN_CC3000_2_VBAT 45
#define CC3000_2_SPI SPI2

#define PIN_CC3000_3_CS 61
#define PIN_CC3000_3_IRQ 6
#define PIN_CC3000_3_VBAT 47
#define CC3000_3_SPI SPI3
*/
#define ESP8266_INTERFACES_COUNT 0
/*
//clockwise starting on the top left of the board with the rs232 on the left and the efm on the top side of the board.
#define PIN_ESP8266_0_POWER 32
#define PIN_ESP8266_0_RESET 31
#define PIN_ESP8266_0_GPIO0 12
#define SERIAL_ESP8266_0 SerialDF11_0

#define PIN_ESP8266_1_POWER 18
#define PIN_ESP8266_1_RESET 17
#define PIN_ESP8266_1_GPIO0 25
#define SERIAL_ESP8266_1 SerialDF11_1

#define PIN_ESP8266_2_POWER 29
#define PIN_ESP8266_2_RESET 28
#define PIN_ESP8266_2_GPIO0 41
#define SERIAL_ESP8266_2 SerialDF11_2

#define PIN_ESP8266_3_POWER 5
#define PIN_ESP8266_3_RESET 4
#define PIN_ESP8266_3_GPIO0 61
#define SERIAL_ESP8266_3 SerialDF11_3
*/
/* LESENSE number of channels possible to use, should be 16 */
// On the WG840 only 8 channels are exposed by pins (4,5,6,7,12,13,14,15)
//#define NUM_LESENSE_CHANNELS    16
#define NUM_LESENSE_CHANNELS    0
/* GPIO Port for analog comparators */
//#define LESENSE_CH_PORT         gpioPortC


void print_gpio_regs(void);

void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t pin);
uint32_t cmu_hfper_freq_get(void);

extern void check_for_reset(void);
extern void initVariant(void);


