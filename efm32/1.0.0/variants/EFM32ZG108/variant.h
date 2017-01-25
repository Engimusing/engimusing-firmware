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

#define LED_BUILTIN 13

#define EFMZG_LEUART_CLKDIV	0x59D0
#define EFMTG_LEUART_CLKDIV	0x77C0
#define EFMWG_LEUART_CLKDIV	0x77C0

#define LEUART_CLKDIV		EFMZG_LEUART_CLKDIV
#define EFMZG_USART_CLKDIV  	0x0A65


// Wire Interfaces (I2C)

#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE0_SDA         (11u) //PD6
#define PIN_WIRE0_SCL         (12u) //PD7
#define WIRE0_INTERFACE       I2C0
#define WIRE0_LOC    1
#define WIRE0_ISR_HANDLER     I2C0_Handler
#define WIRE0_CLOCK				cmuClock_I2C0

#define PIN_WIRE1_SDA         (11u) //PD6
#define PIN_WIRE1_SCL         (12u) //PD7
#define WIRE1_INTERFACE       I2C0
#define WIRE1_LOC    1
#define WIRE1_ISR_HANDLER     I2C0_Handler
#define WIRE1_CLOCK				cmuClock_I2C0

#define PIN_WIRE2_SDA         (11u) //PD6
#define PIN_WIRE2_SCL         (12u) //PD7
#define WIRE2_INTERFACE       I2C0
#define WIRE2_LOC    1
#define WIRE2_ISR_HANDLER     I2C0_Handler
#define WIRE2_CLOCK				cmuClock_I2C0

#define PIN_WIRE3_SDA         (11u) //PD6
#define PIN_WIRE3_SCL         (12u) //PD7
#define WIRE3_INTERFACE       I2C0
#define WIRE3_LOC    1
#define WIRE3_ISR_HANDLER     I2C0_Handler
#define WIRE3_CLOCK				cmuClock_I2C0

static const uint8_t A0  = -1;//No ADC on Zero Gecko

#define ADC_RESOLUTION		0

void print_gpio_regs(void);

void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t pin);
uint32_t cmu_hfper_freq_get(void);

#define CMU_HFPERCLKEN0_USART1	(0x1UL << 3)

extern void check_for_reset(void);
extern void initVariant(void);

/*#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void check_for_reset(void);

#ifdef __cplusplus
} // extern "C"
#endif
*/

