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

#include "Arduino.h"
#include "variant.h"
#include <stdbool.h>
#include <stdint.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_usart.h"

/*

EM4 Pin retention:
	output enable
	output value
	pull enable
	pull direction

EM4 Wakeup - PA0, PF1, PF2, PE13

Toggle, Set, and Clear

Data input register

Interrupts:
	2 interrupt lines from 16 pending sources
	Separate enable, status, set, and clear registers
	Asynchronous sensing
	Rising, falling, both edges
	Wake up from EM0-EM3

=======================================================

=======================================================

Pin 1:  Ground

Pin 2:
	PD4:	ADC0_CH4
	PC15:	TIM1_CC2 #0	PRS_CH1 #2
Pin 3:
	PD6:	ADC0_CH6	TIM1_CC0 #4	PCNT_S0IN #3	ACMP0_O #2
	PE12:	TIM1_CC2 #1	CMU_CLK1 #2
	PC14:	TIM1_CC1 #0	PCNT0_S1IN #0	PRS_CH0 #2
Pin 4:
	PB8:	US1_CS #0	TIM1_CC1 #3	
	PC3:	ACMP0_CH3
Pin 5:
	PB7:	US1_CLK #0	TIM1_CC0 #3	
	PC2:	ACMP0_CH2
Pin 6:
	PC4:	ACMP0_CH4
	PB11:	IDAC0_OUT	TIM1_CC2 #3
Pin 7:
	PC1:	US1_RX #0	ACMP0_CH1	TIM0_CC2 #4	PCNT0_S1IN #2	PRS_CH3 #0
	PA1:	I2C0_SCL #0	TIM0_CC1 #0/1	CMU_CLK1 #0	GPIO_EM4WU0
Pin 8:
	PC0:	US1_TX#0	ACMP0_CH0	TIM0_CC1#4	PCNT0_S0IN#2	PRS_CH2 #0
	PA0:	I2C0_SDA#0	TIM0_CC0	PRS_CH0#0	GPIO_EM4WU0
Pin 10:
	PD7:	ADC0_CH7	TIM1_CC1#4	ACMP0_O#2
	PC13:	TIM1_CC2#1	CMU_CLK1#2
	PE13:	GPIO_EM4WU5
*/


uint8_t pins[32], ports[32];

void pinMode(uint8_t pin, uint8_t mode)
{
  switch(pin) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    ports[2] = PORTC;
    pins[2]  = 15;
    break;
  case 3:
    ports[3] = PORTE;
    pins[3]  = 12;
    break;
  case 4:
    ports[4] = PORTB;
    pins[4]  = 8;
    break;
  case 5:
    ports[5] = PORTB;
    pins[5]  = 7;
    break;
  case 6:
    ports[6] = PORTB;
    pins[6]  = 11;
    break;
  case 7:
    ports[7] = PORTC;
    pins[7]  = 1;
    break;
  case 8:
    ports[8] = PORTC;
    pins[8]  = 0;
    break;
  case 9:
    break;
  case 10:
    ports[10] = PORTE;
    pins[10]  = 13;
    break;
  case 11:
    break;
  case 12:
    break;
  case 13:
    ports[13] = PORTA;
    pins[13]  = 8;
    break;
  default:
    break;
  }
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  if(val) {
    GPIO->P[ports[pin]].DOUTSET = (1 << pins[pin]);
  } else {
    GPIO->P[ports[pin]].DOUTCLR = (1 << pins[pin]);
  }
}

int digitalRead(uint8_t pin)
{
}

/*
const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom0, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;
Uart Serial( &sercom5, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX ) ;
void SERCOM0_Handler()
{
  Serial1.IrqHandler();
}

void SERCOM5_Handler()
{
  Serial.IrqHandler();
}
*/

