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
// Digital Pins             0  1   2     3     4     5     6     7     8     9    10    11  12  13    14    15
const uint8_t dPorts[]   = {0, 0,PORTC,PORTE,PORTB,PORTB,PORTB,PORTC,PORTC,PORTF,PORTE,  PORTA,PORTA,PORTA,PORTA,PORTA, PORTF, PORTF};
const uint8_t dPins[]    = {0, 0, 15,   12,    8,    7,   11,    1,    0,    2,   13,    0,  1,  8,    9,    10, 0, 1};

// GPIO Interrupt Pins      0 1   2     3     4     5     6     7     8     9    10
const uint8_t iPorts[11] = {0,0,PORTC,PORTE,PORTC,PORTC,PORTB,PORTA,PORTA,  0,  PORTC};
const uint8_t iPins[11]  = {0,0, 15,   12,    3,    2,   11,    1,    0,    0,   13};

// ADC Pins                     0 1   2     3    4  5  6  7  8  9   10
const uint8_t adcPorts[11]  = {0,0,PORTD,PORTD, 0, 0, 0, 0, 0, 0, PORTD};
const uint8_t adcPins[11]   = {0,0,  4,    6,   0, 0, 0, 0, 0, 0,   7  };


const uint32_t adcChannel[] =  {-1,-1,EM_ADC4,EM_ADC6,-1,-1,-1,EM_DAC0,-1,-1, -1, EM_ADC7};
const ADC_SingleInput_TypeDef adcChannelNum[] =  {adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh4,
						  adcSingleInpCh6,adcSingleInpCh0,adcSingleInpCh0,
						  adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh0,
						  adcSingleInpCh0,adcSingleInpCh0, adcSingleInpCh7};



// ACMP Pins                    0  1  2  3   4     5     6     7     8    9  10   
const uint8_t acmpPorts[11] = {0, 0, 0, 0,PORTC,PORTC,PORTC,PORTC,PORTC, 0,PORTE};
const uint8_t acmpPins[11]  = {0, 0, 0, 0,  3,    2,    4,    1,    0,   0, 13  };

// DAC Pins                    0  1  2  3  4  5   6    7  8  9 10   
const uint8_t dacPorts[11] = {0, 0, 0, 0, 0, 0,PORTB, 0, 0, 0, 0};
const uint8_t dacPins[11]  = {0, 0, 0, 0, 0, 0,  11,  0, 0, 0, 0};

// Timer Pins                      0 1   2     3     4     5     6     7     8   9   10   
const uint8_t timerPorts[11]    = {0,0,PORTC,PORTD,PORTB,PORTB,PORTB,PORTA,PORTA,0,PORTE};
const uint8_t timerPins[11]     = {0,0, 15,    6,    8,    7,   11,    0,    0,  0,  13};
const uint8_t timerPinMap[11]   = {9,9,  2,    2,    2,    2,    2,    1,    1,  9,   2};
const uint8_t timerCCindex[11]  = {9,9,  2,    0,    1,    0,    2,    1,    0,  9,   2};
const uint32_t timerRoutes[11] = {0, // 0
				  0, // 1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, // 2: PC15 - TIM1_CC2 #0
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC0PEN, // 3: PD6  - TIM1_CC0 #4
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, // 4: PB8  - TIM1_CC1 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, // 5: PB7  - TIM1_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC2PEN, // 6: PB11 - TIM1_CC2 #3
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, // 7: PA1  - TIM0_CC1 #0/1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, // 8: PA0  - TIM0_CC0 #0/1/4
				  0, // 9
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC1PEN};//10: PD7  - TIM1_CC1 #4

// LED Pins                    Red,  Blue,  Green
const uint8_t ledPorts[3]  = {PORTA, PORTA, PORTA};
const uint8_t ledPins[3]   = {  8,     9,    10  };
const uint8_t ledId[3]   = {  13,    14,    15  };

// ------------------------------------------------------------------------------------------------------------

//Debug Pins
const uint8_t debugPinId[3] = {15,16,9}; //SWCLK, SWDIO, SWO

// This function verifies the pin is valid for this variant
uint8_t valid_pin(uint8_t pin) {
  if((pin < 2) || (pin > 15)) {
    return 0;
  } else {
    return 1;
  }
}



void init( void )
{
  init_efm32();

  pinMode(ledId[0], OUTPUT);      // Configure Green LED
  digitalWrite(ledId[0], HIGH);   // Green LED off
  
  pinMode(ledId[1], OUTPUT);      // Configure Green LED
  digitalWrite(ledId[1], HIGH);   // Green LED off
  
  pinMode(ledId[2], OUTPUT);      // Configure Green LED
  digitalWrite(ledId[2], HIGH);   // Green LED off
}

