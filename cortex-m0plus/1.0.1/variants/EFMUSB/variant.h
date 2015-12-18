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

#ifndef _VARIANT_EFM32ZGUSB_
#define _VARIANT_EFM32ZGUSB_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"

#define VARIANT_MCK 21000000

#define EFMZG_LEUART_CLKDIV 0x59D0
#define EFMTG_LEUART_CLKDIV 0x77C0
#define EFMWG_LEUART_CLKDIV 0x77C0
#define LEUART_CLKDIV EFMZG_LEUART_CLKDIV

extern const uint8_t dPins[];
extern const uint8_t dPorts[];
extern const uint8_t iPorts[];
extern const uint8_t iPins[];
extern const uint8_t adcPorts[];
extern const uint8_t adcPins[];
extern const uint8_t acmpPorts[];
extern const uint8_t acmpPins[];
extern const uint8_t dacPorts[];
extern const uint8_t dacPins[];

typedef void (*voidFuncPtr)(void);
extern volatile voidFuncPtr intFunc[];

#ifdef __cplusplus
extern "C" {
#endif

void ledRedOff(void);
void ledRedOn(void);
void ledGreenOff(void);
void ledGreenOn(void);
void ledBlueOff(void);
void ledBlueOn(void);
void ledAllOff(void);
void ledAllOn(void);

uint32_t readGPIOregs(uint8_t port);
void print_gpio_regs(void);

void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t pin);

#ifdef __cplusplus
}
#endif


#endif // _VARIANT_EFM32ZGUSB_

