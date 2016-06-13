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

#include <stdint.h>
#include "pins_arduino.h"
#include "../../cores/efm32/efm_lib/efm_cmu_config.h"

// Required CMSIS global variable that must be kept up-to-date.
uint32_t SystemCoreClock = VARIANT_MCK;


// ----------------- Pin and Port Arrays -----------------------------------------------------------------------

//                                      X1    X2    X3    X4    X5    X6    X7    SWO   LED   SDA   SCL
//                                       5     6    17    18    23    24     1     21    8     13    14
const uint8_t dPorts[]         = {0, 0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,PORTE,PORTD,PORTD};
const uint8_t dPins[]          = {0, 0,  7,    8,   14,   15,   12,   13,    0,    2,   13,    6,    7  };

// GPIO Interrupt Pins                  X1    X2    X3    X4    X5    X6    X7    SWO   LED   SDA   SCL
const uint8_t iPorts[13]       = {0,0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,PORTE,PORTD,PORTD};
const uint8_t iPins[13]        = {0,0,   7,    8,   14,   15,   12,   13,    0,    2,   13,    6,    7  };

// ADC Pins
const uint8_t adcPorts[13]       = {0};
const uint8_t adcPins[13]        = {0};

// ACMP Pins
const uint8_t acmpPorts[13] = {0};
const uint8_t acmpPins[13]  = {0};

// DAC Pins
const uint8_t dacPorts[11] = {0};
const uint8_t dacPins[11]  = {0};

//                                     X1    X2     X3    X4    X5    X6    X7    SWO   LED  SDA  SCL
//                                      5     6     17    18    23    24     1     21    8    13   14
const uint8_t timerPorts[13]   = {0,0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,   0,PORTD,PORTD};
const uint8_t timerPins[13]    = {0,0,  7,    8,    14,   15,   12,   13,    0,    2,    0,   6,    7  };

const uint8_t timerPinMap[13]  = {9,9,  1,    1,    1,    1,    1,    9,     0,    0,    9,   1,    1};
const uint8_t timerCCindex[13] = {9,9,  0,    1,    1,    2,    2,    9,     0,    2,    9,   0,    1};

const uint32_t timerRoutes[13] = {0, // 0
				  0, // 1
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, // 2: PB7  - TIM1_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, // 3: PB8  - TIM1_CC1 #3
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, // 4: PC14 - TIM1_CC1 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, // 5: PC15 - TIM1_CC2 #0
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC2PEN, // 6: PE12 - TIM1_CC2 #1
				  0,
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, // 8: PA0  - TIM0_CC0 #0
				  TIMER_ROUTE_LOCATION_LOC5 | TIMER_ROUTE_CC2PEN, // 9: PF2  - TIM0_CC2 #5
				  0, //10
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC0PEN, //11: PD6  - TIM1_CC0 #4
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC1PEN};//12: PD7  - TIM1_CC1 #4


// ------------------------------------------------------------------------------------------------------------

// This function verifies the pin is valid for this variant
// 1 5 6 8 13 14 17 18 21 23 24
uint8_t valid_pin(uint8_t pin) {
  if((pin < 1) || ((pin >= 2) && (pin <= 4)) || (pin == 7) || ((pin >= 9) && (pin <= 12))
     || (pin == 15) || (pin == 16) || (pin == 19) || (pin == 20) || (pin == 22) || (pin > 24)) {
    return 0;
  } else {
    return 1;
  }
}

uint32_t cmu_hfper_freq_get(void)
{
  return VARIANT_MCK >> (CMU->HFPERCLKDIV & 0xF);
}

// System initialize function called in startup_efm32zg.S
void SystemInit(void)
{
}

void init( void )
{
  init_efm32zg();

  GPIO_config(PORTE,  13, OUTPUT);      // Configure Green LED
  GPIO->P[PORTE].DOUTSET = (1 << 13);   // Green LED off
}

