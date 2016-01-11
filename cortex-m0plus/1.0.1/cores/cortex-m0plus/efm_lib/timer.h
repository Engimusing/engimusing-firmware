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

#include "efm_cmu_config.h"
#include "efm_pin_config.h"
#include "efm_emu.h"
#include "wiring_digital.h"
#include "efm_timer.h"

// Variant stuff:

#define MS_PRESCALE_8  2625
#define US_PRESCALE_1    21
#define PULSE_INC      1024

struct timer_counter {
  TIMER_TypeDef *ptr;
  int index;
  volatile uint32_t *wake;
  IRQn_Type IRQn;
};

enum timer_req {
  REQ_TIMER,
  REQ_TIMER0,
  REQ_TIMER1
};

class TimersLP
{
 public:
  TimersLP();
  void delay_ms(uint32_t);
  void delay_us(uint32_t);
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout);
  void tone(uint32_t outputPin, uint32_t frequency, uint32_t duration = 0);
  void noTone (uint32_t pin);
  void analogWrite(uint32_t ulPin, uint32_t ulValue, uint32_t prescale=7);
  void noPWM(uint32_t pin);
  uint32_t get_counter_value(int);
  uint32_t get_timer_frequency(void);
  volatile static uint32_t timer0_wake;
  volatile static uint32_t timer1_wake;
  static void (*isr0Callback)();
  static void (*isr1Callback)();
  void disable(int timer);
  uint32_t tone_active(uint8_t pin);
  static bool timer0_free;
  static bool timer1_free;

 private:
  timer_counter enable(void (*isr)(), uint8_t timer_req);
  static uint32_t timer_freq;
};

void wake_only(void);
void tone0_isr(void);
void tone1_isr(void);
uint32_t get_toggle_count0(void);
uint32_t get_toggle_count1(void);
uint32_t get_isr_count(void);

// Library stuff:



#ifdef __cplusplus
extern "C"{

  // Timer modes

  // Measures the length in microseconds of a pulse on the pin
  // state if HIGH measures a positive going pulse
  // if LOW a negative pulse.
  //  --TODO-- Need to characterize start up time
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout);


  // Provides a version of pulseIn with a default argument (C++ only)
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout = 1000000L);

  void print_timer_regs(int timer);
} // extern "C"

#endif

