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

#ifdef __cplusplus
extern "C" {
#endif

  // Required CMSIS global variable that must be kept up-to-date.
  uint32_t SystemCoreClock = VARIANT_MCK;

  RingBuffer rx_buffer0;
  RingBuffer tx_buffer0;

  LEUARTClass Serial(LEUART0, LEUART0_IRQn, 0, &rx_buffer0, &tx_buffer0, PORTB, 13, 14,
		     LEUART_ROUTE_LOCATION_LOC1, CMU_LFBCLKEN0_LEUART0);

  // ----------------- Pin and Port Arrays -----------------------------------------------------------------------
  // Digital Pins             0  1   2     3     4     5     6     7     8     9    10    11  12  13    14    15
  const uint8_t dPorts[]   = {0, 0,PORTC,PORTE,PORTB,PORTB,PORTB,PORTC,PORTC,PORTF,PORTE,  9,  9,PORTA,PORTA,PORTA};
  const uint8_t dPins[]    = {0, 0, 15,   12,    8,    7,   11,    1,    0,    2,   13,    0,  0,  8,    9,    10};

  // GPIO Interrupt Pins      0 1   2     3     4     5     6     7     8     9    10
  const uint8_t iPorts[11] = {0,0,PORTC,PORTE,PORTC,PORTC,PORTB,PORTA,PORTA,  0,  PORTC};
  const uint8_t iPins[11]  = {0,0, 15,   12,    3,    2,   11,    1,    0,    0,   13};

  // ADC Pins                     0 1   2     3    4  5  6  7  8  9   10
  const uint8_t adcPorts[11]  = {0,0,PORTD,PORTD, 0, 0, 0, 0, 0, 0, PORTD};
  const uint8_t adcPins[11]   = {0,0,  4,    6,   0, 0, 0, 0, 0, 0,   7  };

  // ACMP Pins                    0  1  2  3   4     5     6     7     8    9  10   
  const uint8_t acmpPorts[11] = {0, 0, 0, 0,PORTC,PORTC,PORTC,PORTC,PORTC, 0,PORTE};
  const uint8_t acmpPins[11]  = {0, 0, 0, 0,  3,    2,    4,    1,    0,   0, 13  };

  // DAC Pins                    0  1  2  3  4  5   6    7  8  9 10   
  const uint8_t dacPorts[11] = {0, 0, 0, 0, 0, 0,PORTB, 0, 0, 0, 0};
  const uint8_t dacPins[11]  = {0, 0, 0, 0, 0, 0,  11,  0, 0, 0, 0};


  // -------------------------------------------------------------------------------------------------------------



  // GPIO Interrupts
  volatile voidFuncPtr intFunc[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
  // storage for 16 interrupt functions
  // corresponding to #bits in IEN



  // This function verifies the pin is valid for this variant
  int valid_pin(uint8_t pin) {
    if((pin < 2) || (pin == 11) || (pin == 12) || (pin > 15)) {
      Serial.println("pinMode - pin not support for this board"); // Error
      return 0;
    } else {
      return 1;
    }
  }



  void ledRedOff(void)   {GPIO->P[PORTA].DOUTSET = (1 <<  8);}
  void ledRedOn(void)    {GPIO->P[PORTA].DOUTCLR = (1 <<  8);}
  void ledGreenOff(void) {GPIO->P[PORTA].DOUTSET = (1 << 10);}
  void ledGreenOn(void)  {GPIO->P[PORTA].DOUTCLR = (1 << 10);}
  void ledBlueOff(void)  {GPIO->P[PORTA].DOUTSET = (1 <<  9);}
  void ledBlueOn(void)   {GPIO->P[PORTA].DOUTCLR = (1 <<  9);}

  void ledAllOff(void)
  {
    GPIO->P[PORTA].DOUTSET = (0x7 <<  8);
  }

  void ledAllOn(void)
  {
    GPIO->P[PORTA].DOUTCLR = (0x7 <<  8);
  }

  uint32_t readGPIOregs(uint8_t port)
  {
    return GPIO->P[port].DIN;
  }

  uint32_t cmu_hfper_freq_get(void)
  {
    return VARIANT_MCK >> (CMU->HFPERCLKDIV & 0xF);
  }


  // System initialize function called in startup_efm32zg.S
  void SystemInit(void)
  {
  }


#ifdef __cplusplus
}
#endif


// LEUART0 Interrupt handler
void LEUART0_IRQHandler(void)
{
  Serial.IrqHandler();
}

static uint32_t mode_reg[18];

void init( void )
{
  init_efm32zg();

  GPIO_config(PORTA,  8, OUTPUT);      // Configure Green LED
  GPIO_config(PORTA,  9, OUTPUT);      // Configure Blue LED
  GPIO_config(PORTA, 10, OUTPUT);      // Configure Red LED
  GPIO->P[PORTA].DOUTSET = (1 << 8);   // Green LED off
  GPIO->P[PORTA].DOUTSET = (1 << 9);   // Blue LED off
  GPIO->P[PORTA].DOUTSET = (1 << 10);  // Red LED off
}



//                          0 1   2     3     4     5     6     7     8     9    10    11  12  13    14    15
static uint8_t ports[16] = {0,0,PORTC,PORTE,PORTB,PORTB,PORTB,PORTC,PORTC,PORTF,PORTE,  9,  9,PORTA,PORTA,PORTA};
static uint8_t pins[16]  = {0,0, 15,   12,    8,    7,   11,    1,    0,    2,   13,    0,  0,  8,    9,    10};
