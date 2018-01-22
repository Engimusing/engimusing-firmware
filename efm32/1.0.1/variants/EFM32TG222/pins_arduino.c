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
//                                       5     6    17    18    23    24     1     21    8     13    14    8
const uint8_t dPorts[]         =    {0, PORTA, PORTA, PORTA, 0, 0, PORTC, PORTC, PORTC, PORTC, PORTC, PORTB, PORTB, PORTA, PORTA, PORTA, //0-15
                                              0, PORTB, 0, 0, PORTB, PORTB, 0, 0, PORTD, PORTD, PORTD, PORTD, 0, 0, PORTC, PORTC, //16-31
                                              PORTC, PORTC, PORTC, PORTC, PORTC, PORTF, PORTF, PORTF, PORTF, PORTF, PORTF, 0, 0, PORTE, PORTE, PORTE, //32-47
                                              PORTE}; //48
const uint8_t dPins[]          =    {0, 0,  1, 2, 0, 0, 0, 1, 2, 3, 4, 7, 8, 8, 9, 10, 
                                             0, 11, 0, 0, 13, 14, 0, 0, 4, 5, 6, 7, 0, 0, 8, 9, 
                                             10, 11, 13, 14, 15, 0, 1, 2, 3, 4, 5, 0, 0, 10, 11, 12,
                                             13};

// GPIO Interrupt Pins                  X1    X2    X3    X4    X5    X6    X7    SWO   LED   SDA   SCL
const uint8_t iPorts[]         = {0, PORTA, PORTA, PORTA, 0, 0, PORTC, PORTC, PORTC, PORTC, PORTC, PORTB, PORTB, PORTA, PORTA, PORTA, 0, PORTB, 0, 0, PORTB, PORTB, 0, 0, PORTD, PORTD, PORTD, PORTD, 0, 0, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTF, PORTF, PORTF, PORTF, PORTF, PORTF, 0, 0, PORTE, PORTE, PORTE, PORTE};
const uint8_t iPins[]          = {0, 0,  1, 2, 0, 0, 0, 1, 2, 3, 4, 7, 8, 8, 9, 10, 0, 11, 0, 0, 13, 14, 0, 0, 4, 5, 6, 7, 0, 0, 8, 9, 10, 11, 13, 14, 15, 0, 1, 2, 3, 4, 5, 0, 0, 10, 11, 12, 13};

// ADC Pins
const uint8_t adcPorts[]       = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t adcPins[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// ACMP Pins
const uint8_t acmpPorts[]      = {0, 0, 0, 0, 0, 0, PORTC, PORTC, PORTC, PORTC, PORTC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t acmpPins[]       = {0, 0, 0, 0, 0, 0,     0,     1,     2,     3,     4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,     8,     9,    10,    11,    13,    14,    15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// DAC Pins
//                                       5     6    17    18    23    24     1     21    8     13    14
const uint8_t dacPorts[]       = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PORTB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t dacPins[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//                                     X1    X2     X3    X4    X5    X6    X7    SWO   LED  SDA  SCL
//                                      5     6     17    18    23    24     1     21    8    13   14
//const uint8_t timerPorts[]   = {0,0,PORTB,PORTB,PORTC,PORTC,PORTE,PORTE,PORTA,PORTF,   0,PORTD,PORTD,0};
//const uint8_t timerPins[]    = {0,0,  7,    8,    14,   15,   12,   13,    0,    2,    0,   6,    7 ,0};

//const uint8_t timerPinMap[]  = {9,9,  1,    1,    1,    1,    1,    9,     0,    0,    9,   1,    1, 0,0};
//const uint8_t timerCCindex[] = {9,9,  0,    1,    1,    2,    2,    9,     0,    2,    9,   0,    1, 0,0};

/*const uint32_t timerRoutes[] = {0, // 0
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
				TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC1PEN,  //12: PD7  - TIM1_CC1 #4
				0};
*/

const uint32_t adcChannel[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DAC0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const ADC_SingleInput_TypeDef adcChannelNum[] =  {adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh0,
														   adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh0,
														   adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh0,
														   adcSingleInpCh0,adcSingleInpCh0,adcSingleInpCh6, 
														   adcSingleInpCh7, adcSingleInpCh0};
//                                      0,     1,     2,     3,     4,     5,     6,     7,     8,     9,     A,     B,     C,     D,    #,      *
const uint8_t ledPorts[LED_COUNT]  = {PORTD, PORTD, PORTF, PORTB, PORTB, PORTF, PORTB, PORTA, PORTF, PORTA, PORTE, PORTE, PORTE, PORTE, PORTA, PORTA};
const uint8_t ledPins[LED_COUNT]   = {    5,     4,     4,     8,    11,     3,     7,    10,     5,     2,    10,    11,    12,    13,     1,     9};
const uint8_t ledId[LED_COUNT]     = {   25,    24,    41,     12,   17,    40,    11,    15,    42,     3,    45,    46,    47,    48,     2,    14};
														   
// ------------------------------------------------------------------------------------------------------------

//Debug Pins
const uint8_t debugPinId[3] = {37,38,39}; //SWCLK, SWDIO, SWO



// This function verifies the pin is valid for this variant
// 2-13
uint8_t valid_pin(uint8_t pin) {
  if((pin < 1) || (pin > 48)) {
    return 0;
  } else {
    return 1;
  }
}

// System initialize function called in startup_efm32zg.S
void init( void )
{
  init_efm32();

  pinMode(ledId[0], OUTPUT);      // Configure Green LED
  digitalWrite(ledId[0], HIGH);   // Green LED off
}

