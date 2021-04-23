/*
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

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

#include "Arduino.h"
#include "em_adc.h"

typedef void (*voidFuncPtr)(void);

void init_efm32(void);

// timer variant defines
#define TIMER_ROUTE_CC0PEN                 (0x1UL << 0)          // CC Channel 0 Pin Enable
#define TIMER_ROUTE_CC1PEN                 (0x1UL << 1)          // CC Channel 1 Pin Enable
#define TIMER_ROUTE_CC2PEN                 (0x1UL << 2)          // CC Channel 2 Pin Enable
#define _TIMER_ROUTE_LOCATION_MASK            0x70000UL          // Bit mask for TIMER_LOCATION
#define TIMER_ROUTE_LOCATION_LOC0           (0x0 << 16)          // Shifted mode LOC0 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC1           (0x1 << 16)          // Shifted mode LOC1 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC2           (0x2 << 16)          // Shifted mode LOC2 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC3           (0x3 << 16)          // Shifted mode LOC3 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC4           (0x4 << 16)          // Shifted mode LOC4 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC5           (0x5 << 16)          // Shifted mode LOC5 for TIMER_ROUTE

#define PINS_COUNT 65

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

extern const uint8_t timerPorts[];
extern const uint8_t timerPins[];
extern const uint8_t timerPinMap[];
extern const uint8_t timerCCindex[];
extern const uint32_t timerRoutes[];

extern const uint32_t pwmChannel[];

#define LED_COUNT 16

extern const uint8_t ledPorts[];
extern const uint8_t ledPins[];
extern const uint8_t ledId[];
extern const uint8_t debugPinId[];
extern const uint32_t adcChannel[];
//extern const ADC_SingleInput_TypeDef adcChannelNum[];

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  uint8_t valid_pin(uint8_t pin);

#ifdef __cplusplus
} // extern "C"
#endif




