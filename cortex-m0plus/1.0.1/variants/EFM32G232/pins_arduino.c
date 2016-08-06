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

// EFM32G232

#include <stdint.h>
#include "pins_arduino.h"


// ----------------- Pin and Port Arrays -----------------------------------------------------------------------
// Digital Ports            0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dPorts[]   = {0, PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,PORTB,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                         PORTB,PORTA,PORTA,PORTA,  0  ,PORTB,  0  ,  0  ,PORTB,PORTB,  0  ,  0  ,PORTD,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 PORTD,PORTD,PORTD,PORTD,PORTD,PORTC,PORTC,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,PORTF,PORTF,PORTF,  0  ,  0  ,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,
//                         64
                         PORTE};

// Digital Pins             0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dPins[]    = {0,   0,    1,    2,    3,    4,    5,    0,    0,    0,    1,    2,    3,    4,    5,    7,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    8,   8,    9,   10,    0,   11,    0,    0,   13,   14,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    4,   5,    6,    7,    8,    6,    7,    0,    0,    8,    9,   10,   11,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    2,    3,    4,    5,    0,    0,    8,    9,   10,   11,   12,   13,   14,
//                         64
			   15};

// GPIO Interrupt Ports     0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t iPorts[]   = {0, PORTA,PORTA,PORTA,PORTA,PORTA,PORTA,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,PORTB,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                         PORTB,PORTA,PORTA,PORTA,  0  ,PORTB,  0  ,  0  ,PORTB,PORTB,  0  ,  0  ,PORTD,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 PORTD,PORTD,PORTD,PORTD,PORTD,PORTC,PORTC,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,PORTF,PORTF,PORTF,  0  ,  0  ,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,PORTE,
//                         64
                         PORTE};

// GPIO Interrupt Pins      0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t iPins[]    = {0,   0,    1,    2,    3,    4,    5,    0,    0,    0,    1,    2,    3,    4,    5,    7,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    8,   8,    9,   10,    0,   11,    0,    0,   13,   14,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    4,   5,    6,    7,    8,    6,    7,    0,    0,    8,    9,   10,   11,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    2,    3,    4,    5,    0,    0,    8,    9,   10,   11,   12,   13,   14,
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
//                         16   17    18    19    2-1    21    22    23    24    25    26    27    28    29    30    31
                           -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  EM_DAC0  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,EM_ADC0,EM_ADC1,EM_ADC2,EM_ADC3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			 EM_ADC4,EM_ADC5,EM_ADC6,EM_ADC7,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,  -1  ,
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
const uint8_t acmpPorts[]= {0,   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,  0  ,  0  ,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,PORTF,PORTF,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTE,  0  ,
//                         64
                           0  };

// ACMP Pins                0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t acmpPins[] = {0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,    4,    5,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    0,    0,    0,    6,    7,    0,    0,    8,    9,   10,   11,   12,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    2,    3,    4,    5,    0,    0,    8,    9,   10,   11,   12,   13,   14,
//                         64
			   15};

// DAC Ports                0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dacPorts[] = {0,   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,  0  ,  0  ,  0  ,  0  ,PORTB,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         64
                           0  };

// DAC Pins                 0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t dacPins[]  = {0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   0,    0,    0,    0,   11,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         64
			    0};

// GPIO Timer Ports         0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPorts[]={0, PORTA,PORTA,PORTA,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
                           0  ,PORTA,PORTA,PORTA,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTD,PORTD,PORTD,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			   0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTC,PORTC,PORTC,  0  ,  0  ,PORTC,PORTC,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			 PORTC,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,  0  ,PORTE,PORTE,PORTE,  0  ,  0  ,
//                         64
                           0  };

// GPIO Timer Pins          0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPins[]= {0,   0,    1,    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
//                         16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			    0,   8,    9,   10,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
//                         32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			    0,   0,    0,    0,    0,    0,    0,    0,    0,  PORTC,PORTC,PORTC,  0,    0,   13,   14,
//                         48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			   15,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   10,   11,   12,    0,    0,
//                         64
			    0};

// Timer Pin Map               0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerPinMap[] = {9,   0,    0,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
//                            16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			       9,   2,    2,    2,    9,    9,    9,    9,    9,    9,    9,    9,    9,    0,    0,    0,
//                            32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			       9,   9,    9,    9,    9,    9,    9,    9,    9,    2,    2,    9,    9,    9,    1,    1,
//                            48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			       1,   9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    1,    1,    1,    9,    9,
//                            64
			       9};

// Timer Pin CC Index Map      0    1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
const uint8_t timerCCindex[]= {9,   0,    1,    2,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
//                            16   17    18    19    20    21    22    23    24    25    26    27    28    29    30    31
			       9,   0,    1,    2,    9,    9,    9,    9,    9,    9,    9,    9,    9,    0,    1,    2,
//                            32   33    34    35    36    37    38    39    40    41    42    43    44    45    46    47
			       9,   9,    9,    9,    9,    9,    9,    9,    9,    0,    1,    2,    9,    9,    1,    1,
//                            48   49    50    51    52    53    54    55    56    57    58    59    60    61    62    63
			       1,   9,    9,    9,    9,    9,    9,    9,    9,    9,    9,    0,    1,    2,    9,    9,
//                            64
			       9};


const uint32_t timerRoutes[] = {0, // 0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN,  // 1  PA0 TIM0_CC0 #0/1/4
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, // 2  PA1 TIM0_CC1 #0/1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, // 3  PA2 TIM0_CC2 #0/1
				  0, // 4  PA3
				  0, // 5  PA4
				  0, // 6  PA5
				  0, // 9  PB3
				  0, //10  PB4
				  0, //11  PB5
				  0, //12  PB6
				  0, //13  PC4
				  0, //14  PC5
				  0, //15  PB7
				  0, //16  PB8
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, //17 PA12 TIM2_CC0 #1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, //18 PA13 TIM2_CC1 #1
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, //19 PA14 TIM2_CC2 #1
				  0, // 21 PB11
				  0, //24 PB13
				  0, //25 PB14
				  0, //28  PD0
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC0PEN, //29  PD1 TIM0_CC0 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC1PEN, //30  PD2 TIM0_CC1 #3
				  TIMER_ROUTE_LOCATION_LOC3 | TIMER_ROUTE_CC2PEN, //31  PD3 TIM0_CC2 #3
				  0, //32  PD4
				  0, //33  PD5
				  0, //34  PD6
				  0, //35  PD7
				  0, //36  PD8
				  0, //37  PC6
				  0, //38  PC7
				  TIMER_ROUTE_LOCATION_LOC2 | TIMER_ROUTE_CC0PEN, //41 PC8   TIM2_CC0 #2
				  TIMER_ROUTE_LOCATION_LOC2 | TIMER_ROUTE_CC1PEN, //42 PC9   TIM2_CC1 #2
				  TIMER_ROUTE_LOCATION_LOC2 | TIMER_ROUTE_CC2PEN, //43 PC10  TIM2_CC2 #2
				  0, //44  PE7
				  0, //45 PC12
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC0PEN, //46 PC13 TIM1_CC1 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC1PEN, //47 PC14 TIM1_CC1 #0
				  TIMER_ROUTE_LOCATION_LOC0 | TIMER_ROUTE_CC2PEN, //48 PC15 TIM1_CC1 #0
				  0, //51  PF2
				  0, //52  PF3
				  0, //53  PF4
				  0, //54  PF5
				  0, //57  PE8
				  0, //58  PE9
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC0PEN, //59 PE10 TIM1_CC0 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC1PEN, //60 PE11 TIM1_CC1 #1
				  TIMER_ROUTE_LOCATION_LOC1 | TIMER_ROUTE_CC2PEN, //61 PE12 TIM1_CC2 #1
				  0, //62 PE13
				  0, //63 PE14
				  0}; //64 PE15

// LED Pins                    Red,  Blue,  Green
const uint8_t ledPorts[3]  = {PORTA, PORTA, PORTA};
const uint8_t ledPins[3]   = {  8,     9,    10  };
const uint8_t ledId[3] = { 17, 18, 19 };
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

  GPIO_config(PORTA,  8, OUTPUT);      // Configure Green LED
  GPIO_config(PORTA,  9, OUTPUT);      // Configure Blue LED
  GPIO_config(PORTA, 10, OUTPUT);      // Configure Red LED
  GPIO->P[PORTA].DOUTSET = (1 << 8);   // Green LED off
  GPIO->P[PORTA].DOUTSET = (1 << 9);   // Blue LED off
  GPIO->P[PORTA].DOUTSET = (1 << 10);  // Red LED off
}

/*
Pin Name Analog		Timers		Communication		Other

 1 PA0   		TIM0_CC0 #0/1	I2C0_SDA #0
 2 PA1   		TIM0_CC1 #0/1	I2C0_SCL #0		CMU_CLK1 #0
 3 PA2   		TIM0_CC2 #0/1				CMU_CLK0 #0
 4 PA3   		TIM0_CDTI0 #0
 5 PA4   		TIM0_CDTI1 #0
 6 PA5   		TIM0_CDTI2 #0	LEU1_TX #1
 9 PC0   ACMP0_CH0	PCNT0_S0IN #2	US1_TX #0
10 PC1   ACMP0_CH1	PCNT0_S1IN #2	US1_RX #0
11 PC2   ACMP0_CH2			US2_TX #0
12 PC3   ACMP0_CH3			US2_RX #0
13 PC4   ACMP0_CH4	LETIM0_OUT0 #3	US2_CLK #0
			PCNT1_S0IN #0
14 PC5   ACMP0_CH5	LETIM0_OUT1 #3	US2_CS #0
			PCNT1_S1IN #0
15 PB7   				US1_CLK #0
16 PB8   				US1_CS #0
17 PA8   		TIM2_CC0 #0
18 PA9   		TIM2_CC1 #0
19 PA10  		TIM2_CC2 #0
21 PB11  DAC0_OUT0	LETIM0_OUT0 #1
24 PB13  				LEU0_TX #1
25 PB14  				LEU0_RX #1
28 PD0   ADC0_CH0	PCNT2_S0IN #0	US1_TX #1
29 PD1   ADC0_CH1	TIM0_CC0 #3	US1_RX #1
			PCNT2_S1IN #0
30 PD2   ADC0_CH2	TIM0_CC1 #3 	US1_CLK #1
31 PD3   ADC0_CH3	TIM0_CC2 #3 	US1_CS #1
32 PD4   ADC0_CH4			LEU0_TX #0
33 PD5   ADC0_CH5			LEU0_RX #0
34 PD6   ADC0_CH6	LETIM0_OUT0 #0	I2C0_SDA #1
35 PD7   ADC0_CH7	LETIM0_OUT1 #0	I2C0_SCL #1
36 PD8   							CMU_CLK1 #1
37 PC6   ACMP0_CH6	LEU1_TX #0	I2C0_SDA #2
38 PC7   ACMP0_CH7	LEU1_RX #0	I2C0_SCL #2
41 PC8   ACMP1_CH0	TIM2_CC0 #2	US0_CS #2 
42 PC9   ACMP1_CH1	TIM2_CC1 #2	US0_CLK #2 
43 PC10  ACMP1_CH2	TIM2_CC2 #2	US0_RX #2
44 PC11  ACMP1_CH3			US0_TX #2
45 PC12  ACMP1_CH4						CMU_CLK0 #1
46 PC13  ACMP1_CH5	TIM0_CDTI1 #1/3
			TIM1_CC1 #0
			PCNT0_S1IN #0

47 PC14  ACMP1_CH6	TIM0_CDTI1 #1/3
			TIM1_CC1 #0
			PCNT0_S1IN #0

48 PC15  ACMP1_CH7	TIM0_CDTI1 #1/3
			TIM1_CC1 #0
			PCNT0_S1IN #0

51 PF2   ACMP1_O #0
52 PF3   		TIM0_CDTI0 #2
53 PF4   		TIM0_CDTI1 #2
54 PF5   		TIM0_CDTI2 #2
57 PE8   		PCNT2_S0IN #1
58 PE9   		PCNT2_S1IN #1
59 PE10  		TIM1_CC0 #1	US0_TX #0
60 PE11  		TIM1_CC1 #1	US0_RX #0
61 PE12  		TIM1_CC2 #1	US0_CLK #0
62 PE13  ACMP0_O #0			US0_CS #0	
63 PE14  				LEU0_TX #2
64 PE15  				LEU0_RX #2
*/


