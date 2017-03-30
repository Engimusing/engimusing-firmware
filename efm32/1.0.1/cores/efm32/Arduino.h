/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2015 Engimusing LLC.  All right reserved.
  Copyright (c) 2014 Arduino LLC.  All right reserved.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <em_device.h>


#if !defined(ADC_COUNT) || (ADC_COUNT == 0)

/** Dummy typedef for when no ADC on processor **/
typedef enum
{
  /* Differential mode disabled */
    adcSingleInpCh0      = 0,
    adcSingleInpCh1      = 0,
    adcSingleInpCh2      = 0,
    adcSingleInpCh3      = 0,
    adcSingleInpCh4      = 0,
    adcSingleInpCh5      = 0,
    adcSingleInpCh6      = 0,
    adcSingleInpCh7      = 0,
    adcSingleInpTemp     = 0,
    adcSingleInpVDDDiv3  = 0,
    adcSingleInpVDD      = 0,
    adcSingleInpVSS      = 0,
    adcSingleInpVrefDiv2 = 0,
    adcSingleInpDACOut0  = 0,
    adcSingleInpDACOut1  = 0,
    adcSingleInpATEST    = 0,
    adcSingleInpCh0Ch1   = 0,
    adcSingleInpCh2Ch3   = 0,
    adcSingleInpCh4Ch5   = 0,
    adcSingleInpCh6Ch7   = 0,
    adcSingleInpDiff0    = 0,
} ADC_SingleInput_TypeDef;

#endif



#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;

// some libraries and sketches depend on this AVR stuff,
// assuming Arduino.h or WProgram.h automatically includes it...
//
#include "avr/pgmspace.h"
#include "avr/interrupt.h"

#include "binary.h"
#include "itoa.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#define clockCyclesPerMicrosecond() ( SystemCoreClock / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (SystemCoreClock / 1000L) )
#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

  void yield( void ) ;

  void init(void);

#include "wiring_shift.h"

  /* sketch */
  void setup( void ) ;
  void loop( void ) ;

#ifdef __cplusplus
} // extern "C"
#endif

// The following headers are for C++ only compilation
#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
#include "Tone.h"
#include "WMath.h"
#include "HardwareSerial.h"
#include "RingBuffer.h"
#endif

#include "delay.h"

#ifdef __cplusplus
//#include "efm_lib/LEUARTClass.h"
#include "efm_lib/UARTClass.h"
#include "efm_lib/timer.h"
#include "efm_lib/analog.h"
#include "efm_lib/efm_gpio.h"
#include "efm_lib/gpio_intrs.h"
#endif

#include "variant.h"

#include "wiring_digital.h"

#include "wiring_analog.h"

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts() __enable_irq()
#define noInterrupts() __disable_irq()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

/**
 * Pin Attributes to be OR-ed
 */
#define PIN_ATTR_COMBO         (1UL<<0)
#define PIN_ATTR_ANALOG        (1UL<<1)
#define PIN_ATTR_DIGITAL       (1UL<<2)
#define PIN_ATTR_PWM           (1UL<<3)
#define PIN_ATTR_TIMER         (1UL<<4)


/* Definitions and types for pins */
typedef enum _EAnalogChannel
{
  NO_ADC=-1,
  EM_ADC0=0,
  EM_ADC1,
  EM_ADC2,
  EM_ADC3,
  EM_ADC4,
  EM_ADC5,
  EM_ADC6,
  EM_ADC7,
  EM_ADC8,
  EM_ADC9,
  EM_ADC10,
  EM_ADC11,
  EM_ADC12,
  EM_ADC13,
  EM_ADC14,
  EM_ADC15,
  EM_DAC0,
  EM_DAC1
} EAnalogChannel ;

// Definitions for PWM channels
typedef enum _EPWMChannel
{
  NOT_ON_PWM=-1,
  PWM0_CH0_LOC0=0,
  PWM0_CH0_LOC1,
  PWM0_CH0_LOC2,
  PWM0_CH0_LOC3,
  PWM0_CH0_LOC4,
  PWM0_CH0_LOC5,
  PWM0_CH1_LOC0=8,
  PWM0_CH1_LOC1,
  PWM0_CH1_LOC2,
  PWM0_CH1_LOC3,
  PWM0_CH1_LOC4,
  PWM0_CH1_LOC5,
  PWM0_CH2_LOC0=16,
  PWM0_CH2_LOC1,
  PWM0_CH2_LOC2,
  PWM0_CH2_LOC3,
  PWM0_CH2_LOC4,
  PWM0_CH2_LOC5,
  PWM1_CH0_LOC0=32,
  PWM1_CH0_LOC1,
  PWM1_CH0_LOC2,
  PWM1_CH0_LOC3,
  PWM1_CH0_LOC4,
  PWM1_CH0_LOC5,
  PWM1_CH1_LOC0=40,
  PWM1_CH1_LOC1,
  PWM1_CH1_LOC2,
  PWM1_CH1_LOC3,
  PWM1_CH1_LOC4,
  PWM1_CH1_LOC5,
  PWM1_CH2_LOC0=48,
  PWM1_CH2_LOC1,
  PWM1_CH2_LOC2,
  PWM1_CH2_LOC3,
  PWM1_CH2_LOC4,
  PWM1_CH2_LOC5,
  PWM2_CH0_LOC0=64,
  PWM2_CH0_LOC1,
  PWM2_CH0_LOC2,
  PWM2_CH0_LOC3,
  PWM2_CH0_LOC4,
  PWM2_CH0_LOC5,
  PWM2_CH1_LOC0=72,
  PWM2_CH1_LOC1,
  PWM2_CH1_LOC2,
  PWM2_CH1_LOC3,
  PWM2_CH1_LOC4,
  PWM2_CH1_LOC5,
  PWM2_CH2_LOC0=80,
  PWM2_CH2_LOC1,
  PWM2_CH2_LOC2,
  PWM2_CH2_LOC3,
  PWM2_CH2_LOC4,
  PWM2_CH2_LOC5,
  PWM3_CH0_LOC0=96,
  PWM3_CH0_LOC1,
  PWM3_CH0_LOC2,
  PWM3_CH0_LOC3,
  PWM3_CH0_LOC4,
  PWM3_CH0_LOC5,
  PWM3_CH1_LOC0=104,
  PWM3_CH1_LOC1,
  PWM3_CH1_LOC2,
  PWM3_CH1_LOC3,
  PWM3_CH1_LOC4,
  PWM3_CH1_LOC5,
  PWM3_CH2_LOC0=112,
  PWM3_CH2_LOC1,
  PWM3_CH2_LOC2,
  PWM3_CH2_LOC3,
  PWM3_CH2_LOC4,
  PWM3_CH2_LOC5
} EPWMChannel ;

#include "wiring_constants.h"

#define INPUT INPUT_
