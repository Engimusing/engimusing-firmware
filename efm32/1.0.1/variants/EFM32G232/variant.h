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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"

#define LED_BUILTIN 35

#define EFMZG_LEUART_CLKDIV 0x59D0
#define EFMTG_LEUART_CLKDIV 0x77C0
#define EFMWG_LEUART_CLKDIV 0x77C0
#define LEUART_CLKDIV EFMZG_LEUART_CLKDIV

static const uint8_t A0  = 28;
static const uint8_t A1  = 29;
static const uint8_t A2  = 30;
static const uint8_t A3  = 31;
static const uint8_t A4  = 32;
static const uint8_t A5  = 33;
static const uint8_t A6  = 34;

#define ADC_RESOLUTION		12

// PWM Resolution
#define PWM_INTERFACE        PWM
#define PWM_INTERFACE_ID     ID_PWM
#define PWM_FREQUENCY	     1000
#define PWM_MAX_DUTY_CYCLE   255
#define PWM_MIN_DUTY_CYCLE   0
#define PWM_RESOLUTION	     16

/* LESENSE number of channels possible to use*/
#define NUM_LESENSE_CHANNELS    0

#define SPI_INTERFACES_COUNT 0

void print_gpio_regs(void);

void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
void detachInterrupt(uint8_t pin);
uint32_t cmu_hfper_freq_get(void);

void check_for_reset(void);
extern void initVariant(void);


