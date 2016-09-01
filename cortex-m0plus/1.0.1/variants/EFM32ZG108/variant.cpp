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

  Pin 2:
  PD4:	ADC0_CH4
  PC15:	PRS_CH1 #2	TIM1_CC2 #0
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
  PD7:	ADC0_CH7	TIM1_CC1#4	ACMP0_O#2 CMU_CLK0
  PC13:	TIM1_CC2#1	CMU_CLK1#2
  PE13:	GPIO_EM4WU5
*/


RingBuffer rx_buffer1;
RingBuffer rx_buffer2;

UARTClass Serial(USART1, USART1_RX_IRQn, &rx_buffer1, USART_ROUTE_LOCATION_LOC0, cmuClock_USART1);
UARTClass Serial1(LEUART0, LEUART0_IRQn, &rx_buffer2, LEUART_ROUTE_LOCATION_LOC1, cmuClock_LEUART0);

// IT handlers
void USART1_RX_IRQHandler(void)
{
  Serial.IrqHandler();
}

void LEUART0_IRQHandler(void)
{
  Serial1.IrqHandler();
}

void check_for_reset()
  {
	if(Serial.isResetReceived() || Serial1.isResetReceived())
	{
		SCB->AIRCR = 0x05FA0004;
		//BOOT_reset();
	}
  }

void initVariant() 
{ 
	Serial.begin(115200);
	Serial1.begin(115200);
}


#define LEUART0_RXDATAXP ((uint32_t *) (0x40084018UL))
#define USART1_RXDATAXP  ((uint32_t *) (0x4000C418UL))
#define SCB_AIRCR        ((uint32_t *) (0xE000ED0CUL))
#define RXDATAXP_BREAK   ((uint32_t)        (1 << 15))
/* check for reset is handled inside UARTClass now but thought I should keep this around just in case
void check_for_reset(void)
{
  if((*LEUART0_RXDATAXP & RXDATAXP_BREAK) || (*USART1_RXDATAXP & RXDATAXP_BREAK)) {
    for(volatile int i = 0; i < 150000; i++);
    *SCB_AIRCR = 0x05FA0004;  // Write to the Application Interrupt/Reset Command Register to reset
  }
}
*/


// -------------------------------------------------------------------------------------------------------------

void print_gpio_regs(void)
{
  char port[6] = {'A','B','C','D','E','F'};
  Serial.printf("\r\n");
  for(int i = 0; i < 6; i++) {
    Serial.printf("PORT %c:\r\n",port[i]);
    Serial.printf(" CTRL    = %x\r\n",GPIO->P[i].CTRL);
    Serial.printf(" MODEL   = %x\r\n",GPIO->P[i].MODEL);
    Serial.printf(" MODEH   = %x\r\n",GPIO->P[i].MODEH);
    Serial.printf(" DOUT    = %x\r\n",GPIO->P[i].DOUT);
    Serial.printf(" DOUTSET = %x\r\n",GPIO->P[i].DOUTSET);
    Serial.printf(" DOUTCLR = %x\r\n",GPIO->P[i].DOUTCLR);
    Serial.printf(" DOUTTGL = %x\r\n",GPIO->P[i].DOUTTGL);
    Serial.printf(" DIN     = %x\r\n",GPIO->P[i].DIN);
  }
  Serial.printf(" GPIO->EXTIPSELL = %x\r\n",GPIO->EXTIPSELL);
  Serial.printf(" GPIO->EXTIPSELH = %x\r\n",GPIO->EXTIPSELH);
  Serial.printf(" GPIO->EXTIRISE  = %x\r\n",GPIO->EXTIRISE);
  Serial.printf(" GPIO->EXTIFALL  = %x\r\n",GPIO->EXTIFALL);
  Serial.printf(" IEN             = %x\r\n",GPIO->IEN);
  Serial.printf(" IF              = %x\r\n",GPIO->IF);
}

extern void serialEventRun(void) __attribute__((weak));
extern void serialEvent() __attribute__((weak));
void serialEventRun(void)
{
if (Serial.available() && serialEvent) serialEvent();
if (Serial1.available() && serialEvent) serialEvent();

}
