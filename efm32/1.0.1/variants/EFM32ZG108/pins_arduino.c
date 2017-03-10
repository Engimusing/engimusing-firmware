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
#include "wiring_constants.h"
#include "efm_lib/efm_gpio.h"
#include "pins_arduino.h"


// ----------------- Pin and Port Arrays -----------------------------------------------------------------------

//                                       2     3     4     5     6     7     8      9    10    11    12    13
//                                      X1    X2    X3    X4    X5    X6    X7    SWO   LED   SDA   SCL   LED
//                                       5     6    17    18    23    24     1     21    8     13    14     8
const uint8_t dPorts[]         = {0, 0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,PORTB,PORTD,PORTD,PORTB, PORTA};
const uint8_t dPins[]          = {0, 0,  7,    8,   14,   15,   12,   13,    0,    2,   11,    6,    7,   11, 0  };

// GPIO Interrupt Pins                  X1    X2    X3    X4    X5    X6    X7    SWO   LED   SDA   SCL
const uint8_t iPorts[]         = {0,0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,PORTE,PORTD,PORTD,0,PORTA};
const uint8_t iPins[]          = {0,0,   7,    8,   14,   15,   12,   13,    0,    2,   13,    6,    7 ,0,0};

// ADC Pins
const uint8_t adcPorts[14]       = {0};
const uint8_t adcPins[14]        = {0};

const uint32_t adcChannel[14] =  {0};
const ADC_SingleInput_TypeDef adcChannelNum[14] =  {adcSingleInpCh0};

// ACMP Pins
const uint8_t acmpPorts[14] = {0};
const uint8_t acmpPins[14]  = {0};

// DAC Pins
const uint8_t dacPorts[14] = {0};
const uint8_t dacPins[14]  = {0};

//                                     X1    X2     X3    X4    X5    X6    X7    SWO   LED  SDA  SCL
//                                      5     6     17    18    23    24     1     21    8    13   14
const uint8_t timerPorts[]   = {0,0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,   0,PORTD,PORTD,0};
const uint8_t timerPins[]    = {0,0,  7,    8,    14,   15,   12,   13,    0,    2,    0,   6,    7 ,0};

const uint8_t timerPinMap[]  = {9,9,  1,    1,    1,    1,    1,    9,     0,    0,    9,   1,    1, 0};
const uint8_t timerCCindex[] = {9,9,  0,    1,    1,    2,    2,    9,     0,    2,    9,   0,    1, 0};

const uint32_t timerRoutes[] = {0, // 0
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
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC1PEN, //12: PD7  - TIM1_CC1 #4
				  0};

// ------------------------------------------------------------------------------------------------------------

const uint8_t ledPorts[1]  = {PORTB};
const uint8_t ledPins[1]   = { 11 };
const uint8_t ledId[1] = {13};

// This function verifies the pin is valid for this variant
// 2-13
uint8_t valid_pin(uint8_t pin) {
  if( (pin > 14)) {
    return 0;
  } else {
    return 1;
  }
}



void init( void )
{
  init_efm32();

  pinMode(ledId[0], OUTPUT);      // Configure Green LED
  digitalWrite(ledId[0], LOW);   // Green LED off
}



