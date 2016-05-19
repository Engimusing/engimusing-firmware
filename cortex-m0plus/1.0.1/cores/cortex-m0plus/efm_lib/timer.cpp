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

#include "timer.h"
#include "Tone.h"
#include "pins_arduino.h"
#include "LEUARTClass.h"
#include "delay.h"

extern LEUARTClass Serial;

TimersLP Timers;

bool TimersLP::timer0_free = true;
bool TimersLP::timer1_free = true;
volatile uint32_t TimersLP::timer0_wake = 0;
volatile uint32_t TimersLP::timer1_wake = 0;
uint32_t TimersLP::timer_freq = 0;
void (*TimersLP::isr0Callback)() = NULL;
void (*TimersLP::isr1Callback)() = NULL;

static timer_counter T0;
static timer_counter T1;
static timer_counter TX;

TimersLP::TimersLP()
{

  T0.index = 0;
  T0.ptr   = TIMER0;
  T0.wake  = &timer0_wake;
  T0.IRQn  = TIMER0_IRQn;

  T1.index = 1;
  T1.ptr   = TIMER1;
  T1.wake  = &timer1_wake;
  T1.IRQn  = TIMER1_IRQn;

  TX.index = -1;
}

timer_counter TimersLP::enable(void (*isr)(), uint8_t timer_req)
{
  timer_freq = cmu_hfper_freq_get();
  if(timer0_free && ((timer_req == REQ_TIMER) || (timer_req == REQ_TIMER0))) {
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
    timer0_free = false;
    isr0Callback = isr;
    *T0.wake = 0;
    return T0;
  }
  if(timer1_free && ((timer_req == REQ_TIMER) || (timer_req == REQ_TIMER1))) {
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1;
    timer1_free = false;
    isr1Callback = isr;
    *T1.wake = 0;
    return T1;
  }
  Serial.println("Timer enable attempted but all timers already in use");
  return TX;
}


void TimersLP::disable(int timer)
{
  if(timer == 0) {
    T0.ptr->CMD = TIMER_CMD_STOP;  // stop the timer counting
    NVIC_EnableIRQ(TIMER0_IRQn);
    T0.ptr->IEN = 0;
    CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER0;
    timer0_free = true;
  } else if(timer == 1) {
    T1.ptr->CMD = TIMER_CMD_STOP;  // stop the timer counting
    NVIC_EnableIRQ(TIMER1_IRQn);
    T1.ptr->IEN = 0;
    CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER1;
    timer1_free = true;
  } else {
    Serial.println("Attempted to disable invalid timer");
  }
}


void TimersLP::delay_ms(uint32_t dly)
{
  timer_counter T = enable(wake_only,REQ_TIMER);
  if(T.index >= 0) {
    T.ptr->TOP = MS_PRESCALE_8;
    T.ptr->CNT = 0;
    T.ptr->CTRL = TIMER_CTRL_MODE_UP | TIMER_CTRL_PRESC_DIV8;
    T.ptr->IEN = TIMER_IEN_OF;
    NVIC_EnableIRQ(T.IRQn);
    T.ptr->CMD = TIMER_CMD_START;
    for(uint32_t i = 0; i < dly;) {
      EMU_EnterEM1();
      if(*T.wake) {
	*T.wake = 0;
	i++;
      }
    }
  }
  disable(T.index);
}


void TimersLP::delay_us(uint32_t dly)
{
  uint32_t start = micros();
  if(dly <= 20) {
    return;
    //    while(micros() < (start + dly));
  }
  uint32_t time = dly * US_PRESCALE_1;
  if(time > 65535) {
    Serial.println("Delay time exceeds counter size (3120 max)");
    return;
  }
  timer_counter T = enable(wake_only,REQ_TIMER);
  if(T.index >= 0) {
    T.ptr->CNT = 0;
    T.ptr->CTRL = TIMER_CTRL_MODE_UP;
    T.ptr->IEN = TIMER_IEN_OF;
    NVIC_EnableIRQ(T.IRQn);
    if(dly > 20) {
      time = (dly - (micros() - start) - 15) * US_PRESCALE_1;
    }
    T.ptr->TOP =  time;
    T.ptr->CMD = TIMER_CMD_START;
    while(1) {
      EMU_EnterEM1();
      if(*T.wake) {
	*T.wake = 0;
	break;
      }
    }
  }
  disable(T.index);
}



#define TONE_TC_TOP     0xFFFF
static volatile int32_t toggleCount[2];
uint32_t get_toggle_count0(void) {return toggleCount[0];}
uint32_t get_toggle_count1(void) {return toggleCount[1];}

static volatile uint32_t int_cnt = 0;
uint32_t get_isr_count(void) {return int_cnt;}

void TimersLP::tone(uint32_t pin, uint32_t frequency, uint32_t duration)
{
  timer_counter TONE;
  uint32_t toneMaxFrequency = get_timer_frequency() / 2;
  uint32_t prescalerConfigBits;
  uint32_t ccValue;

  TONE.index = -1;
  // validate pin
  if((pin > 10) || (pin < 2) || (pin == 8)) {
    Serial.print("Invalid pin = "); Serial.println(pin);
    Serial.println("Must be 2-8 or 10");
    return;
  }
  // acquire timer
  if(timerPinMap[pin] == 1) {
    TONE = enable(tone0_isr,timerPinMap[pin]);
  } else if(timerPinMap[pin] == 2) {
    TONE = enable(tone1_isr,timerPinMap[pin]);
  }
  if(TONE.index < 0) return;

  // set up pin
  TONE.ptr->ROUTE = timerRoutes[pin];
  GPIO_config(timerPorts[pin], timerPins[pin], OUTPUT);

  // Set counter TOP based on frequency
  ccValue = toneMaxFrequency / frequency - 1;
  prescalerConfigBits = TIMER_CTRL_PRESC_DIV1;
  if (ccValue > TONE_TC_TOP) {
    ccValue = toneMaxFrequency / frequency / 2 - 1;
    prescalerConfigBits = TIMER_CTRL_PRESC_DIV2;
    if (ccValue > TONE_TC_TOP) {
      ccValue = toneMaxFrequency / frequency / 4 - 1;
      prescalerConfigBits = TIMER_CTRL_PRESC_DIV4;
      if (ccValue > TONE_TC_TOP) {
	ccValue = toneMaxFrequency / frequency / 8 - 1;
	prescalerConfigBits = TIMER_CTRL_PRESC_DIV8;
	if (ccValue > TONE_TC_TOP) {
	  ccValue = toneMaxFrequency / frequency / 16 - 1;
	  prescalerConfigBits = TIMER_CTRL_PRESC_DIV16;
	  if (ccValue > TONE_TC_TOP) {
	    ccValue = toneMaxFrequency / frequency / 32 - 1;
	    prescalerConfigBits = TIMER_CTRL_PRESC_DIV32;
	    if (ccValue > TONE_TC_TOP) {
	      ccValue = toneMaxFrequency / frequency / 64 - 1;
	      prescalerConfigBits = TIMER_CTRL_PRESC_DIV64;
	      if (ccValue > TONE_TC_TOP) {
		ccValue = toneMaxFrequency / frequency / 128 - 1;
		prescalerConfigBits = TIMER_CTRL_PRESC_DIV128;
		if (ccValue > TONE_TC_TOP) {
		  ccValue = toneMaxFrequency / frequency / 256 - 1;
		  prescalerConfigBits = TIMER_CTRL_PRESC_DIV256;
		  if (ccValue > TONE_TC_TOP) {
		    ccValue = toneMaxFrequency / frequency / 512 - 1;
		    prescalerConfigBits = TIMER_CTRL_PRESC_DIV512;
		    if (ccValue > TONE_TC_TOP) {
		      ccValue = toneMaxFrequency / frequency / 1024 - 1;
		      prescalerConfigBits = TIMER_CTRL_PRESC_DIV1024;
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  TONE.ptr->CTRL = TIMER_CTRL_MODE_UP | prescalerConfigBits;
  TONE.ptr->TOP = ccValue;
  TONE.ptr->CNT = 0; // clear the counter just in case

  if(duration > 0) {
    toggleCount[TONE.index] = frequency * duration * 2 / 1000UL;
    TONE.ptr->IEN = TIMER_IEN_OF;
    NVIC_EnableIRQ(TONE.IRQn);
  }
  TONE.ptr->CC[timerCCindex[pin]].CTRL = TIMER_CC_CTRL_MODE_OUTPUTCOMPARE | TIMER_CC_CTRL_COFOA_TOGGLE;
  TONE.ptr->CMD = TIMER_CMD_START;  // start the timer counting
}

void TimersLP::analogWrite(uint32_t pin, uint32_t value, uint32_t prescale)
{
  static timer_counter PWM = enable(wake_only,REQ_TIMER);
  static uint8_t timer_active[2] = {0,0};

  // validate pin
  if((pin > 10) || (pin < 2) || (pin == 8)) {
    Serial.print("Invalid pin = "); Serial.println(pin);
    Serial.println("Must be 2-8 or 10");
    return;
  }
  // validate prescale
  if(prescale > 10) {
    Serial.print("Invalid prescale = "); Serial.println(prescale);
    Serial.println("Must be 0 to 10");
    return;
  }
  // acquire timer
  if((timerPinMap[pin] == 1) && (timer_active[0] == 0)) {
    PWM = enable(wake_only,timerPinMap[pin]);
    timer_active[0] = pin;
  } else if((timerPinMap[pin] == 2) && (timer_active[1] == 0)) {
    PWM = enable(wake_only,timerPinMap[pin]);
    timer_active[1] = pin;
  }
  if(PWM.index < 0) return;

  if(PWM.index >= 0) {
    // set up pin
    PWM.ptr->ROUTE = timerRoutes[pin];
    GPIO_config(timerPorts[pin], timerPins[pin], OUTPUT);

    PWM.ptr->TOP = 255;
    PWM.ptr->CNT = 0;
    PWM.ptr->CTRL = TIMER_CTRL_MODE_UP | (prescale << _TIMER_CTRL_PRESC_SHIFT);

    PWM.ptr->CC[timerCCindex[pin]].CTRL = TIMER_CC_CTRL_MODE_PWM | TIMER_CC_CTRL_CMOA_TOGGLE | TIMER_CC_CTRL_ICEDGE_BOTH;
    PWM.ptr->CC[timerCCindex[pin]].CCV = value;
    PWM.ptr->CMD = TIMER_CMD_START;  // start the timer counting
  }
}

void TimersLP::noPWM (uint32_t pin)
{
  disable(timerPinMap[pin] - 1);
  GPIO->P[timerPorts[pin]].DOUTSET = (1 << timerPins[pin]);
}


uint32_t TimersLP::tone_active(uint8_t pin)
{
  if(timerPinMap[pin] == 1) {
    return *T0.wake;
  } else if(timerPinMap[pin] == 2) {
    return *T1.wake;
  } else {
    Serial.print("Invalid pin = "); Serial.println(pin);
    return -1;
  }
}

void tone0_isr(void)
{
  if(--toggleCount[0] <= 0) {
    T0.ptr->CMD = TIMER_CMD_STOP;  // stop the timer counting
    NVIC_EnableIRQ(TIMER0_IRQn);
    T0.ptr->IEN = 0;
    CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER0;
    Timers.timer0_free = true;
  }
  *T0.wake = toggleCount[0];
}

void tone1_isr(void)
{
  if(--toggleCount[1] <= 0) {
    T1.ptr->CMD = TIMER_CMD_STOP;  // stop the timer counting
    NVIC_EnableIRQ(TIMER1_IRQn);
    T1.ptr->IEN = 0;
    CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER1;
    Timers.timer1_free = true;
  }
  *T1.wake = toggleCount[1];
}

void TimersLP::noTone (uint32_t pin)
{
  disable(timerPinMap[pin] - 1);
  GPIO->P[timerPorts[pin]].DOUTSET = (1 << timerPins[pin]);
}

void TIMER0_IRQHandler(void)
{
  *T0.wake = TIMER0->IF;
  Timers.isr0Callback();
  TIMER0->IFC = TIMER0->IF;
int_cnt++;
}

void TIMER1_IRQHandler(void)
{
  *T1.wake = TIMER1->IF;
  Timers.isr1Callback();
  TIMER1->IFC = TIMER1->IF;
int_cnt++;
}

void wake_only(void)
{
}

uint32_t TimersLP::pulseIn(uint32_t pin, uint32_t state, uint32_t timeout = 1000000L)
{
  timer_counter PULSE;
  uint32_t pulse_count = 0;
  int loop_count  = 0;
  uint16_t leading_edge_cnt = 0;
  uint16_t trailing_edge_cnt = 0;

  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);

  // validate pin
  if(!((pin == 3) || (pin == 5) || (pin == 8))) {
    Serial.print("Invalid pin = "); Serial.println(pin);
    Serial.println("Must be 3,5 or 8");
    return 0;
  }
  // acquire timer
  PULSE = enable(wake_only,timerPinMap[pin]);
  if(PULSE.index < 0) return 0;

  // set up pin
  PULSE.ptr->ROUTE = timerRoutes[pin];
  GPIO_config(timerPorts[pin], timerPins[pin], INPUT);

  PULSE.ptr->CTRL = TIMER_CTRL_MODE_UP;

  // Set counter TOP based on timeout
  if(timeout < PULSE_INC) {
    PULSE.ptr->TOP = timeout * US_PRESCALE_1;
  } else {
    PULSE.ptr->TOP = PULSE_INC * US_PRESCALE_1;
  }

  // check that signal is in the right state
  // wait low or high until signal is ready
  uint32_t level = LOW;
  if(state == HIGH) {
    level = HIGH;
  }
  uint32_t cnt = PULSE_INC * US_PRESCALE_1 * 10;
  digitalWrite(4,LOW);
  while(((GPIO->P[timerPorts[pin]].DIN >> timerPins[pin]) & 0x1) == level) {
    if(cnt-- <= 0) {
      Serial.println("Timeout - starting level wrong");
      disable(PULSE.index);
      return 0;
    }
  }

  bool edge_received = false;
  loop_count = timeout / PULSE_INC;  // number of loops until timeout

  PULSE.ptr->CNT = 0; // clear the counter just in case
  PULSE.ptr->IEN = TIMER_IEN_OF | TIMER_IEN_CC0;
  NVIC_EnableIRQ(PULSE.IRQn);
  PULSE.ptr->CMD = TIMER_CMD_START;  // start the timer counting
  PULSE.ptr->CC[timerCCindex[pin]].CTRL = TIMER_CC_CTRL_MODE_INPUTCAPTURE | TIMER_CC_CTRL_ICEDGE_BOTH;

  // triggers on the start of the timer
  while(1) {
    EMU_EnterEM1();
    if(*PULSE.wake) {
      if(*PULSE.wake & TIMER_IF_CC0) { // Rising or Falling edge detected
	*PULSE.wake = 0;
	if(edge_received) {
	  digitalWrite(6,HIGH);
	  trailing_edge_cnt = (uint16_t)PULSE.ptr->CC[timerCCindex[pin]].CCV;
	  pulse_count += trailing_edge_cnt - leading_edge_cnt;
	  pulse_count /= US_PRESCALE_1;
	  break;
	} else {
	  leading_edge_cnt = (uint16_t)PULSE.ptr->CC[timerCCindex[pin]].CCV;
	  if(leading_edge_cnt > 10) {
	    digitalWrite(6,LOW);
	    edge_received = true;
	  }
	}
      } else if(*PULSE.wake & TIMER_IF_OF) { // Timer overflowed
	*PULSE.wake = 0;
	loop_count--;
	if(loop_count > 0) {
	  pulse_count += PULSE_INC * US_PRESCALE_1;
	} else { // timeout occurred
	  pulse_count = 0;
	  if(edge_received) {
	    Serial.println("Timeout - pulse did not end ");
	  } else {
	    Serial.println("Timeout - pulse did not start");
	  }
	  break;
	}
      }
      *PULSE.wake = 0;
    }
  }
  digitalWrite(4,HIGH);
  disable(PULSE.index);
  return pulse_count;
}



uint32_t TimersLP::get_timer_frequency(void)
{
  return cmu_hfper_freq_get();
}

void tone(uint32_t _pin, uint32_t frequency, uint32_t duration)
{
  Timers.tone(_pin, frequency, duration);
}

void noTone(uint32_t _pin)
{
  Timers.noTone(_pin);
}


/*
  Generates a square wave of the specified frequency (and 50% duty cycle) on a pin.
  A duration can be specified, otherwise the wave continues until a call to noTone().
  The pin can be connected to a piezo buzzer or other speaker to play tones.

  Only one tone can be generated at a time. If a tone is already playing on a different
  pin, the call to tone() will have no effect. If the tone is playing on the same pin, 
  the call will set its frequency.

  NOTE: if you want to play different pitches on multiple pins, you need to call noTone()
  on one pin before calling tone() on the next pin.

  Syntax:
  tone(pin, frequency) 
  tone(pin, frequency, duration)

  Parameters:

  pin: the pin on which to generate the tone
  frequency: the frequency of the tone in hertz - unsigned int
  duration: the duration of the tone in milliseconds (optional) - unsigned long

  Returns nothing
*/


/*
  Description:
  Reads a pulse (either HIGH or LOW) on a pin. For example, if value is HIGH, pulseIn() waits 
  for the pin to go HIGH, starts timing, then waits for the pin to go LOW and stops timing. 
  Returns the length of the pulse in microseconds or 0 if no complete pulse was received within the timeout.

  The timing of this function has been determined empirically and will probably show errors in shorter pulses. 
  Works on pulses from 10 microseconds to 3 minutes in length. Please also note that if the pin is already 
  high when the function is called, it will wait for the pin to go LOW and then HIGH before it starts counting. 
  This routine can be used only if interrupts are activated. Furthermore the highest resolution is obtained 
  with short intervals.

  Syntax:
  pulseIn(pin, value) 
  pulseIn(pin, value, timeout)

  Parameters:
  pin: the number of the pin on which you want to read the pulse. (int)

  value: type of pulse to read: either HIGH or LOW. (int)

  timeout (optional): the number of microseconds to wait for the pulse to be completed: the function returns 0
  if no complete pulse was received within the timeout. Default is one second (unsigned long).
  Returns:
  the length of the pulse (in microseconds) or 0 if no pulse is completed before the timeout (unsigned long) 
*/


/*
  Timer functions:
  simple millisecond delay - use ISR go into sleep mode
  simple microsecond delay - use ISR go into sleep mode
  short microsecond delay  - do we need a shorter one where we don't sleep?
  pulse length timer
  generate tone
  PWM output(s)
  long timer - RTC?
*/

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */


uint32_t get_counter_value(int timer)
{
  TIMER_TypeDef *TIMER;
  TIMER = (timer) ? TIMER1 : TIMER0;

  return TIMER->CNT;
}




void print_timer_regs(int timer)
{
  TIMER_TypeDef *TIMER;
  uint32_t regs[23];


  if(timer == 0) {
    if((CMU->HFPERCLKEN0 & CMU_HFPERCLKEN0_TIMER0) == 0) {
      Serial.println("Enabled TIMER0 clock - You may want to do this in your code");
      CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
    }
    TIMER = TIMER0;
  } else if(timer == 1) {
    if((CMU->HFPERCLKEN0 & CMU_HFPERCLKEN0_TIMER1) == 0) {
      Serial.println("Enabled TIMER1 clock - You may want to do this in your code");
      CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1;
    }
    TIMER = TIMER1;
  } else {
    Serial.print("Invalid Timer = "); Serial.println(timer);
    return;
  }

  regs[0] = TIMER->CTRL;
  regs[1] = TIMER->CMD;
  regs[2] = TIMER->STATUS;
  regs[3] = TIMER->IEN;
  regs[4] = TIMER->IF;
  regs[5] = TIMER->IFS;
  regs[6] = TIMER->IFC;
  regs[7] = TIMER->TOP;
  regs[8] = TIMER->TOPB;
  regs[9] = TIMER->CNT;
  regs[10] = TIMER->ROUTE;

  regs[11] = TIMER->CC[0].CTRL;
  regs[12] = TIMER->CC[1].CTRL;
  regs[13] = TIMER->CC[2].CTRL;

  regs[14] = TIMER->CC[0].CCV;
  regs[15] = TIMER->CC[1].CCV;
  regs[16] = TIMER->CC[2].CCV;

  regs[17] = TIMER->CC[0].CCVP;
  regs[18] = TIMER->CC[1].CCVP;
  regs[19] = TIMER->CC[2].CCVP;

  regs[20] = TIMER->CC[0].CCVB;
  regs[21] = TIMER->CC[1].CCVB;
  regs[22] = TIMER->CC[2].CCVB;

  uint32_t timer_freq = cmu_hfper_freq_get();
  Serial.print("Timer Frequency HFPER Clock = "); Serial.println(timer_freq);

  Serial.println("");
  Serial.print("TIMER"); Serial.print(timer); Serial.println(" Registers:");

  Serial.print(" CTRL   = "); Serial.println(regs[0],HEX);
  Serial.print(" CMD    = "); Serial.println(regs[1],HEX);
  Serial.print(" STATUS = "); Serial.println(regs[2],HEX);
  Serial.print(" IEN    = "); Serial.println(regs[3],HEX);

  Serial.print(" IF     = "); Serial.println(regs[4],HEX);
  Serial.print(" IFS    = "); Serial.println(regs[5],HEX);
  Serial.print(" IFC    = "); Serial.println(regs[6],HEX);
  Serial.print(" TOP    = "); Serial.println(regs[7],HEX);

  Serial.print(" TOPB   = "); Serial.println(regs[8],HEX);
  Serial.print(" CNT    = "); Serial.println(regs[9],HEX);
  Serial.print(" ROUTE  = "); Serial.println(regs[10],HEX);
  Serial.println("");

  Serial.print(" CC[0].CTRL = "); Serial.print(regs[11],HEX);
  Serial.print("\t\tCC[1].CTRL = "); Serial.print(regs[12],HEX);
  Serial.print("\t\tCC[2].CTRL = "); Serial.println(regs[13],HEX);

  Serial.print(" CC[0].CCV  = ");  Serial.print(regs[14],HEX);
  Serial.print("\t\tCC[1].CCV  = ");  Serial.print(regs[15],HEX);
  Serial.print("\t\tCC[2].CCV  = ");  Serial.println(regs[16],HEX);

  Serial.print(" CC[0].CCVP = "); Serial.print(regs[17],HEX);
  Serial.print("\t\tCC[1].CCVP = "); Serial.print(regs[18],HEX);
  Serial.print("\t\tCC[2].CCVP = "); Serial.println(regs[19],HEX);

  Serial.print(" CC[0].CCVB = "); Serial.print(regs[20],HEX);
  Serial.print("\t\tCC[1].CCVB = "); Serial.print(regs[21],HEX);
  Serial.print("\t\tCC[2].CCVB = "); Serial.println(regs[22],HEX);

  Serial.println("");
}
