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


//#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif


#define EFMZG_LEUART_CLKDIV 0x59D0
#define EFMTG_LEUART_CLKDIV 0x77C0
#define EFMWG_LEUART_CLKDIV 0x77C0

#define LEUART_CLKDIV EFMZG_LEUART_CLKDIV

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int  digitalRead(uint8_t pin);

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

#define RISING     (0x2)
#define CHANGE     (0x3)
#define FALLING    (0x4)

void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t pin);

#ifdef __cplusplus
}
#endif


#endif // _VARIANT_EFM32ZGUSB_

