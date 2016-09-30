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

// EFM32WG840

#include <stdint.h>
#include "pins_arduino.h"

// ----------------- Pin and Port Arrays -----------------------------------------------------------------------
// Digital Ports            0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dPorts[]   = {0, PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,  0  ,PORTB,PORTB,PORTB,PORTB,PORTC,PORTC,PORTB,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                         PORTB,PORTA,PORTA,PORTA,  0  ,PORTB,PORTB,  0  ,PORTB,PORTB,  0  ,  0  ,PORTD,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 PORTD,PORTD,PORTD,PORTD,PORTD,PORTC,PORTC,  0  ,  0  ,PORTE,PORTE,PORTE,PORTE,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,PORTF,PORTF,PORTF,  0  ,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,
//                         64
                         PORTA};

// Digital Pins             0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dPins[]    = {0,   0,    1,    2,    3,    4,    5,    6,    0,    3,    4,    5,    6,    4,    5,    7,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    8,  12,   13,   14,    0,   11,   12,    0,   13,   14,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    4,   5,    6,    7,    8,    6,    7,    0,    0,    4,    5,    6,    7,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   14,   0,    0,    2,    3,    4,    5,    0,    8,    9,   10,   11,   12,   13,   14,   15,
//                         64
			   15};

// GPIO Interrupt Ports     0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t iPorts[]   = {0, PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,  0  ,PORTB,PORTB,PORTB,PORTB,PORTC,PORTC,PORTB,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                         PORTB,PORTA,PORTA,PORTA,  0  ,PORTB,PORTB,  0  ,PORTB,PORTB,  0  ,  0  ,PORTD,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 PORTD,PORTD,PORTD,PORTD,PORTD,PORTC,PORTC,  0  ,  0  ,PORTE,PORTE,PORTE,PORTE,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,PORTF,PORTF,PORTF,  0  ,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,
//                         64
                         PORTA};

// GPIO Interrupt Pins      0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t iPins[]    = {0,   0,    1,    2,    3,    4,    5,    6,    0,    3,    4,    5,    6,    4,    5,    7,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    8,  12,   13,   14,    0,   11,   12,    0,   13,   14,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    4,   5,    6,    7,    8,    6,    7,    0,    0,    4,    5,    6,    7,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   14,   0,    0,    2,    3,    4,    5,    0,    8,    9,   10,   11,   12,   13,   14,   15,
//                         64
			   15};


// ADC Ports                0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t adcPorts[] = {0,   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTD,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 PORTD,PORTD,PORTD,PORTD,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         64
                           0  };

// ADC Pins                 0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t adcPins[]  = {0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    4,   5,    6,    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         64
			    0};

				
const uint32_t adcChannel[] =  {-1,   -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  EM_DAC0  ,  EM_DAC1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,EM_ADC0,EM_ADC1,EM_ADC2,EM_ADC3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 EM_ADC4,EM_ADC5,EM_ADC6,EM_ADC7,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1 ,  -1  ,  -1  ,  -1  ,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,
//                         64
                           -1  };
const ADC_SingleInput_TypeDef adcChannelNum[] =  {adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh1, adcSingleInpCh2, adcSingleInpCh3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    adcSingleInpCh4, adcSingleInpCh5, adcSingleInpCh6, adcSingleInpCh7, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			    adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0, adcSingleInpCh0,
//                         64
			    adcSingleInpCh0};
				
// ACMP Ports               0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t acmpPorts[]= {0,   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,PORTD,PORTD,PORTD,PORTC,PORTC,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTE,  0  ,  0  ,
//                         64
                           0  };

// ACMP Pins                0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t acmpPins[] = {0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    4,    5,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    6,    7,    8,    6,    7,    0,    0,    0,    0,    0,    0,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   14,   0,    0,    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,   12,    0,    0,
//                         64
			    0};

//Removed opamp pins from this since they are not really DAC pins
//Alt pins are also not setup yet. They require the OPAMPS setup to use
// DAC Ports                0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dacPorts[] = {0,   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  , 0, 0,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,  0  ,  0  ,  0  ,  0  ,PORTB,PORTB,  0  ,  0  ,  0  ,  0  ,  0  ,PORTD,PORTD,  0  ,  0  ,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,0,0,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         64
                           0  };

// DAC Pins                 0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dacPins[]  = {0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   0,    0,    0,    0,   11,   12,    0,    0,    0,    0,    0,    0,    1,    0,    0,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    0,    0,    0,    0,    0,    0,    8,    0,    0,    0,    0,    0,    0,
//                         64
			    0};

// GPIO Timer Ports         0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPorts[]={0, PORTA,PORTA,PORTA,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTB,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                         PORTB,PORTA,PORTA,PORTA,  0  ,PORTB,  0  ,  0  ,  0,    0  ,  0  ,  0  ,  0  ,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,PORTD,PORTD,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,
//                         64
                         PORTE};

// GPIO Timer Pins          0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPins[]= {0,   0,    1,    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    8,  12,   13,   14,    0,   11,    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    6,    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    2,    0,    0,    0,    0,    0,    0,    0,   11,   12,    0,   14,   15,
//                         64
			   15};

// Timer Pin Map               0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPinMap[] = {9,   0,    0,    0,    9,    9,    0,    9,    9,    9,    9,    9,    9,    9,    9,    1,
//                            16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			       1,   2,    2,    2,    9,    1,    9,    9,    9,    9,    9,    9,    9,    0,    0,    0,
//                            32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			       9,   9,    1,    1,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    1,    1,
//                            48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			       1,   9,    9,    0,    9,    9,    9,    9,    9,    9,    9,    1,    1,    9,    9,    3,
//                            64
			       3};

// Timer Pin CC Index Map      0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerCCindex[]= {9,   0,    1,    2,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    0,
//                            16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			       1,   0,    1,    2,    9,    2,    9,    9,    9,    9,    9,    9,    9,    0,    1,    2,
//                            32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			       9,   9,    0,    1,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    0,    1,
//                            48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			       2,   9,    9,    2,    9,    9,    9,    9,    9,    9,    0,    1,    2,    9,    0,    1,
//                            64
			       2};


const uint32_t timerRoutes[] = {0, // 0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN,  // 1  PA0 TIM0_CC0 #0/1/4
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, // 2  PA1 TIM0_CC1 #0/1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, // 3  PA2 TIM0_CC2 #0/1
				  0, // 4  PA3
				  0, // 5  PA4
				  0, // 6  PA5
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, // 15 PB7	TIM1_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, // 16 PB8	TIM1_CC1 #3
				  0, // 9  PB3
				  0, //10  PB4
				  0, //11  PB5
				  0, //12  PB6
				  0, //13  PC4
				  0, //14  PC5
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, //15  PB7 TIM1_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, //16  PB8 TIM1_CC1 #3
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC0PEN, //17 PA12 TIM2_CC0 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC1PEN, //18 PA13 TIM2_CC1 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC2PEN, //19 PA14 TIM2_CC2 #1
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC2PEN, //21 PB11 TIM1_CC2 #3
				  0, //24 PB13
				  0, //25 PB14
				  0, //28  PD0
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, //29  PD1 TIM0_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, //30  PD2 TIM0_CC1 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC2PEN, //31  PD3 TIM0_CC2 #3
				  0, //32  PD4
				  0, //33  PD5
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC0PEN, //34  PD6 TIM1_CC0 #4
				  TIMER_ROUTE_LOCATION_LOC4 | TIMER_ROUTE_CC1PEN, //35  PD7 TIM1_CC1 #4
				  0, //36  PD8
				  0, //37  PC6
				  0, //38  PC7
				  0, //41  PE4
				  0, //42  PE5
				  0, //43  PE6
				  0, //44  PE7
				  0, //45 PC12
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, //46 PC13 TIM1_CC0 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, //47 PC14 TIM1_CC1 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, //48 PC15 TIM1_CC2 #0
				  TIMER_ROUTE_LOCATION_LOC5 | TIMER_ROUTE_CC2PEN, //51  PF2 TIM0_CC2 #5
				  0, //52  PF3
				  0, //53  PF4
				  0, //54  PF5
				  0, //57  PE8
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC0PEN, //58 PE10 TIM1_CC0 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC0PEN, //59 PE11 TIM1_CC1 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC2PEN, //60 PE12 TIM1_CC2 #1
				  0, //61 PE13
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, //62 PE14 TIM3_CC0 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, //63 PE15 TIM3_CC1 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN}; //64 PA15 TIM3_CC2 #0

				  
				  

#define TIMER_COUNT 4

	const uint32_t pwmChannel[] = {0, // 0
				  PWM0_CH0_LOC0,  // 1  PA0 TIM0_CC0 #0/1/4
				  PWM0_CH1_LOC0, // 2  PA1 TIM0_CC1 #0/1
				  PWM0_CH2_LOC0, // 3  PA2 TIM0_CC2 #0/1
				  0, // 4  PA3
				  0, // 5  PA4
				  0, // 6  PA5
				  PWM1_CH0_LOC3, // 15 PB7	TIM1_CC0 #3
				  PWM1_CH1_LOC3, // 16 PB8	TIM1_CC1 #3
				  0, // 9  PB3
				  0, //10  PB4
				  0, //11  PB5
				  0, //12  PB6
				  0, //13  PC4
				  0, //14  PC5
				  PWM1_CH0_LOC3, //15  PB7 TIM1_CC0 #3
				  PWM1_CH1_LOC3, //16  PB8 TIM1_CC1 #3
				  PWM2_CH0_LOC1, //17 PA12 TIM2_CC0 #1
				  PWM2_CH1_LOC1, //18 PA13 TIM2_CC1 #1
				  PWM2_CH2_LOC1, //19 PA14 TIM2_CC2 #1
				  PWM1_CH2_LOC3, //21 PB11 TIM1_CC2 #3
				  0,
				  0,
				  0,
				  0, //24 PB13
				  0, //25 PB14
				  0, 
				  0,
				  0, //28  PD0
				  PWM0_CH0_LOC3, //29  PD1 TIM0_CC0 #3
				  PWM0_CH1_LOC3, //30  PD2 TIM0_CC1 #3
				  PWM0_CH2_LOC3, //31  PD3 TIM0_CC2 #3
				  0, //32  PD4
				  0, //33  PD5
				  PWM1_CH0_LOC4, //34  PD6 TIM1_CC0 #4
				  PWM1_CH1_LOC4, //35  PD7 TIM1_CC1 #4
				  0, //36  PD8
				  0, //37  PC6
				  0, //38  PC7
				  0,
				  0,
				  0, //41  PE4
				  0, //42  PE5
				  0, //43  PE6
				  0, //44  PE7
				  0, //45 PC12
				  PWM1_CH0_LOC0, //46 PC13 TIM1_CC0 #0
				  PWM1_CH1_LOC0, //47 PC14 TIM1_CC1 #0
				  PWM1_CH2_LOC0, //48 PC15 TIM1_CC2 #0
				  0,
				  0,
				  PWM0_CH2_LOC5, //51  PF2 TIM0_CC2 #5
				  0, //52  PF3
				  0, //53  PF4
				  0, //54  PF5
				  0,
				  0,
				  0, //57  PE8
				  PWM1_CH0_LOC0, //58 PE10 TIM1_CC0 #1
				  PWM1_CH1_LOC1, //59 PE11 TIM1_CC1 #1
				  PWM1_CH2_LOC1, //60 PE12 TIM1_CC2 #1
				  0, //61 PE13
				  PWM3_CH0_LOC0, //62 PE14 TIM3_CC0 #0
				  PWM3_CH1_LOC0, //63 PE15 TIM3_CC1 #0
				  PWM3_CH2_LOC0}; //64 PA15 TIM3_CC2 #0





				  
				  
				  
// LED Pins                    Red,  Blue,  Green
const uint8_t ledPorts[3]  = {PORTD, PORTA, PORTA};
const uint8_t ledPins[3]   = {  8,     6,    15  };
const uint8_t ledId[3] = { 36, 7, 64 };
// ------------------------------------------------------------------------------------------------------------

// This function verifies the pin is valid for this variant
uint8_t valid_pin(uint8_t pin) {
  if((pin >= PINS_COUNT)) {
    return 0;
  } else {
    return 1;
  }
}


void init( void )
{
  init_efm32();

  GPIO_config(PORTD,  8, OUTPUT);      // Configure Green LED
  GPIO_config(PORTA,  6, OUTPUT);      // Configure Blue LED
  GPIO_config(PORTA, 15, OUTPUT);      // Configure Red LED
  GPIO->P[PORTD].DOUTSET = (1 << 8);   // Green LED off
  GPIO->P[PORTA].DOUTSET = (1 << 6);   // Blue LED off
  GPIO->P[PORTA].DOUTSET = (1 << 15);  // Red LED off
}

/*
Pin Name Analog		Timers		Communication		Other

 1 PA0			TIM0_CC0 #0/1/4	LEU0_RX #4		GPIO_EM4WU0
					I2C0_SDA #0		PRS_CH0 #0

 2 PA1			TIM0_CC1 #0/1	I2C0_SCL #0		CMU_CLK1 #0
								PRS_CH1 #0

 3 PA2			TIM0_CC2 #0/1				CMU_CLK0 #0
								ETM_TD0 #3

 4 PA3			TIM0_CDTI0 #0				LES_ALTEX2 #0
								ETM_TD1 #3

 5 PA4			TIM0_CDTI1 #0				LES_ALTEX3 #0
								ETM_TD2 #3

 6 PA5			TIM0_CDTI2 #0	LEU1_TX #1		LES_ALTEX4 #0
								ETM_TD3 #3

 7 PA6					LEU1_RX #1		ETM_TCLK #3
								GPIO_EM4WU1

 9 PB3			PCNT1_S0IN #1	US2_TX #1

10 PB4			PCNT1_S1IN #1	US2_RX #1

11 PB5					US2_CLK #1

12 PB6					US2_CS #1

13 PC4	ACMP0_CH4	TIM0_CDTI2 #4	US2_CLK #0		LES_CH4 #0
	DAC0_P0		LETIM0_OUT0 #3	I2C1_SDA #0
	OPAMP_P0	PCNT1_S0IN #0

14 PC5	ACMP0_CH5	LETIM0_OUT1 #3	US2_CS #0		LES_CH5 #0
	DAC0_N0 /	PCNT1_S1IN #0	I2C1_SCL #0
	OPAMP_N0

15 PB7			TIM1_CC0 #3	US0_TX #4
					US1_CLK #0

16 PB8			TIM1_CC1 #3	US0_RX #4
					US1_CS #0

17 PA12			TIM2_CC0 #1

18 PA13			TIM2_CC1 #1

19 PA14			TIM2_CC2 #1

21 PB11	DAC0_OUT0	TIM1_CC2 #3	I2C1_SDA #1
	OPAMP_OUT0	LETIM0_OUT0 #1

22 PB12	DAC0_OUT1	LETIM0_OUT1 #1	I2C1_SCL #1
	OPAMP_OUT1

24 PB13					US0_CLK #4/5
					LEU0_TX #1

25 PB14					US0_CS #4/5
					LEU0_RX #1

28 PD0	ADC0_CH0	PCNT2_S0IN #0	US1_TX #1
	DAC0_OUT0ALT #4/
	OPAMP_OUT0ALT
	OPAMP_OUT2 #1

29 PD1	ADC0_CH1	TIM0_CC0 #3	US1_RX #1		DBG_SWO #2
	DAC0_OUT1ALT #4	PCNT2_S1IN #0
	OPAMP_OUT1ALT	

30 PD2	ADC0_CH2	TIM0_CC1 #3	US1_CLK #1		DBG_SWO #3

31 PD3	ADC0_CH3	TIM0_CC2 #3	US1_CS #1		ETM_TD1 #0/2
	OPAMP_N2

32 PD4	ADC0_CH4			LEU0_TX #0		ETM_TD2 #0/2
	OPAMP_P2

33 PD5	ADC0_CH5			LEU0_RX #0		ETM_TD3 #0/2
	OPAMP_OUT2 #0

34 PD6	ADC0_CH6	TIM1_CC0 #4	US1_RX #2		LES_ALTEX0 #0
	DAC0_P1		LETIM0_OUT0 #0	I2C0_SDA #1		ETM_TD0 #0
	OPAMP_P1	PCNT0_S0IN #3
	ACMP0_O #2

35 PD7	ADC0_CH7	TIM1_CC1 #4	US1_TX #2		CMU_CLK0 #2
	DAC0_N1		LETIM0_OUT1 #0	I2C0_SCL #1		LES_ALTEX1 #0
	OPAMP_N1	PCNT0_S1IN #3				ETM_TCLK #0
	ACMP1_O #2

36 PD8	BU_VIN							CMU_CLK1 #1

37 PC6	ACMP0_CH6			LEU1_TX #0		LES_CH6 #0
					I2C0_SDA #2 		ETM_TCLK #2

38 PC7	ACMP0_CH7			LEU1_RX #0		LES_CH7 #0
					I2C0_SCL #2 		ETM_TD0 #2

41 PE4					US0_CS #1

42 PE5					US0_CLK #1

43 PE6					US0_RX #1

44 PE7					US0_TX #1

45 PC12	ACMP1_CH4						CMU_CLK0 #1
	DAC0_OUT1ALT #0						LES_CH12 #0
	OPAMP_OUT1ALT

46 PC13	ACMP1_CH5	TIM0_CDTI0 #1/3				LES_CH13 #0
	DAC0_OUT1ALT #1	TIM1_CC0 #0
	OPAMP_OUT1ALT	TIM1_CC2 #4
			PCNT0_S0IN #0

47 PC14	ACMP1_CH6	TIM0_CDTI1 #1/3	US0_CS #3		LES_CH14 #0
	DAC0_OUT1ALT #2	TIM1_CC1 #0
	OPAMP_OUT1ALT	PCNT0_S1IN #0

48 PC15	ACMP1_CH7	TIM0_CDTI2 #1/3	US0_CLK #3		LES_CH15 #0
	DAC0_OUT1ALT #3	TIM1_CC2 #0				DBG_SWO #1
	OPAMP_OUT1ALT

51 PF2	ACMP1_O #0	TIM0_CC2 #5	LEU0_TX #4		GPIO_EM4WU4
								DBG_SWO #0

52 PF3			TIM0_CDTI0 #2/5				PRS_CH0 #1
								ETM_TD3 #1

53 PF4			TIM0_CDTI1 #2/5				PRS_CH1 #1

54 PF5			TIM0_CDTI2 #2/5				PRS_CH2 #1

56 PE8			PCNT2_S0IN #1				PRS_CH3 #1

57 PE9			PCNT2_S1IN #1

58 PE10			TIM1_CC0 #1	US0_TX #0

59 PE11			TIM1_CC1 #1	US0_RX #0		LES_ALTEX5 #0

60 PE12			TIM1_CC2 #1	US0_RX #3		CMU_CLK1 #2
					US0_CLK #0		LES_ALTEX6 #0
					I2C0_SDA #6

61 PE13	ACMP0_O #0			US0_TX #3		LES_ALTEX7 #0
					US0_CS #0		GPIO_EM4WU5
					I2C0_SCL #6

62 PE14			TIM3_CC0 #0	LEU0_TX #2

63 PE15			TIM3_CC1 #0	LEU0_RX #2

64 PA15			TIM3_CC2 #0
 */


