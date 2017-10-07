///
///@file timer.h
///@brief Contains TimersLP class which can be used for timer related tasks 
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///


#pragma once

#include "efm_cmu_config.h"
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
 
  ///@brief Constructor which initializes the internal timers
  ///@return Returns a TimerLP object
  ///@details Should not be called except for the global static object Timers
  TimersLP();
  
  ///@brief delay a specified number of milliseconds. Puts the Energy Micro in EM1 while waiting.
  ///@param [in] dly Number of milliseconds to delay before returning.
  void delay_ms(uint32_t dly);
  
  ///@brief delay a specified number of microseconds. Puts the Energy Micro in EM1 while waiting.
  ///@param [in] dly Number of microseconds to delay before returning.
  void delay_us(uint32_t dly);
  
  ///@brief Edge detection on a pin
  ///@param [in] pin the number of the pin on which you want to read the pulse. (int)
  ///@param [in] state type of pulse to read: either HIGH or LOW. (int)
  ///@param [in] timeout the number of microseconds to wait for the pulse to be completed: the function returns 0
  ///  if no complete pulse was received within the timeout. Default is one second (unsigned long).
  ///@return the length of the pulse (in microseconds) or 0 if no pulse is completed before the timeout (unsigned long) 
  ///@details Reads a pulse (either HIGH or LOW) on a pin. For example, if value is HIGH, pulseIn() waits 
  /// for the pin to go HIGH, starts timing, then waits for the pin to go LOW and stops timing. 
  ///  Returns the length of the pulse in microseconds or 0 if no complete pulse was received within the timeout.
  ///  The timing of this function has been determined empirically and will probably show errors in shorter pulses. 
  ///  Works on pulses from 10 microseconds to 3 minutes in length. Please also note that if the pin is already 
  ///  high when the function is called, it will wait for the pin to go LOW and then HIGH before it starts counting. 
  ///  This routine can be used only if interrupts are activated. Furthermore the highest resolution is obtained 
  ///  with short intervals.
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout);
  
  ///@brief Sent a tone out on a pin
  ///@param [in] outputPin the pin on which to generate the tone
  ///@param [in] frequency the frequency of the tone in hertz - unsigned int
  ///@param [in] duration the duration of the tone in milliseconds (optional) - unsigned long
  ///@details Generates a square wave of the specified frequency (and 50% duty cycle) on a pin.
  ///  A duration can be specified, otherwise the wave continues until a call to noTone().
  ///  The pin can be connected to a piezo buzzer or other speaker to play tones.
  ///
  ///  Only one tone can be generated at a time. If a tone is already playing on a different
  ///  pin, the call to tone() will have no effect. If the tone is playing on the same pin, 
  ///  the call will set its frequency.
  ///
  ///  NOTE: if you want to play different pitches on multiple pins, you need to call noTone()
  ///  on one pin before calling tone() on the next pin.
  ///
  ///  Syntax:
  ///  tone(pin, frequency) 
  ///  tone(pin, frequency, duration)
  void tone(uint32_t outputPin, uint32_t frequency, uint32_t duration = 0);
  
  ///@brief Turn off the tone that is on 
  ///@param [in] pin Pin to turn the tone off for
  void noTone (uint32_t pin);
  
  ///@brief Output a squarewave on a pin
  ///@param [in] ulPin pin to output the squarewave on
  ///@param [in] ulValue value between 0-255 for the duty cycle of the squarewave
  ///@param [in] prescale Amount to prescale the timer. (Don't know what this does)
  ///@details These comments for this function have not been verified
  void analogWrite(uint32_t ulPin, uint32_t ulValue, uint32_t prescale=7);
  
  ///@brief Turn off the PWM on a particular pin, so turns off an analogWrite 
  ///@param [in] pin Pin to turn off the PWM for
  void noPWM(uint32_t pin);
  
  ///@brief Get the current CNT value for a timer
  ///@param [in] int Timer to get the count for (either 0 or 1)
  ///@return Current CNT value for the timer
  uint32_t get_counter_value(int);
  
  ///@brief get the frequency being used to run the timers
  ///@return frequency of the timers
  uint32_t get_timer_frequency(void);
  
  volatile static uint32_t timer0_wake;
  volatile static uint32_t timer1_wake;
  static void (*isr0Callback)();
  static void (*isr1Callback)();
  
  ///@brief Disable a timer
  ///@param [in] timer Timer to disable
  void disable(int timer);
  
  ///@brief Check if a tone is active on a particular pin
  ///@param [in] pin Pin to check
  ///@return Remaining time left on the timer (?) 
  uint32_t tone_active(uint8_t pin);
  
  static bool timer0_free;
  static bool timer1_free;

 private:
  ///@brief Enable a timer with a callback method
  ///@param [in] isr Method to call when the timer times out
  ///@return timer_counter that is used with the callback
  timer_counter enable(void (*isr)(), uint8_t timer_req);
  static uint32_t timer_freq;
};
//Callback functions for the timers

///@brief Callback for a timer that just wakes up the timer and does nothing else
void wake_only(void);

///@brief Decrements the toggleCount for timer0 and ends the timer if it reaches 0
void tone0_isr(void);
///@brief Decrements the toggleCount for timer1 and ends the timer if it reaches 0
void tone1_isr(void);

///@brief Get the current toggleCount for timer0
///@return Current toggleCount remaining for timer0
uint32_t get_toggle_count0(void);

///@brief Get the current toggleCount for timer1
///@return Current toggleCount remaining for timer1
uint32_t get_toggle_count1(void);

///@brief Get the number of times the isrs for both timers have been called
///@return number of times the isrs have been called
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

