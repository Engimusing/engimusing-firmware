/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#define LOW             (0x0)
#define HIGH            (0x1)

// GPIO enumeration
typedef enum
{
	PIN_MODE_GPIO0 = (0x0),
	GPIO_DISABLED = (0x00),
	PIN_MODE_GPIO1 = (0x1),
	DISABLED_PULLUP = (0x01),
	INPUT_ = (0x02),
	INPUT_PULLUP = (0x03),
	INPUT_PULLDOWN = (0x04),
	INPUT_FILTER = (0x05),
	INPUT_PU_FILTER = (0x06),
	INPUT_PD_FILTER = (0x07),
	WIRED_OR = (0x08),
	WIRED_OR_PULLDOWN = (0x09),
	OUTPUT = (0x0A),
	OUTPUT_LOWEST_DRIVE = (0x0B),
	OUTPUT_LOW_DRIVE = (0x0C),
	OUTPUT_HIGH_DRIVE = (0x0D),
	WIRED_AND = (0x0E),
	WIRED_AND_LOWEST_DRIVE = (0x0F),
	WIRED_AND_LOW_DRIVE = (0x10),
	WIRED_AND_HIGH_DRIVE = (0x11),
	WIRED_AND_FILTER = (0x12),
	WIRED_AND_FILTER_LOWEST_DRIVE = (0x13),
	WIRED_AND_FILTER_LOW_DRIVE = (0x14),
	WIRED_AND_FILTER_HIGH_DRIVE = (0x15),
	WIRED_AND_PULLUP = (0x16),
	WIRED_AND_PULLUP_LOWEST_DRIVE = (0x17),
	WIRED_AND_PULLUP_LOW_DRIVE = (0x18),
	WIRED_AND_PULLUP_HIGH_DRIVE = (0x19),
	WIRED_AND_PU_FILTER = (0x1A),
	WIRED_AND_PU_FILTER_LOWEST_DRIVE = (0x1B),
	WIRED_AND_PU_FILTER_LOW_DRIVE =(0x1C),
	WIRED_AND_PU_FILTER_HIGH_DRIVE = (0x1D),
} WiringModeTypeDef;


// Analog Comparator
#define PIN_MODE_ACMP                         (0x2)
#define ACMP0_CH0_INPUT                      (0x20)
#define ACMP0_CH1_INPUT                      (0x21)
#define ACMP0_CH2_INPUT                      (0x22)
#define ACMP0_CH3_INPUT                      (0x23)
#define ACMP0_CH4_INPUT                      (0x24)
#define ACMP0_OUTPUT                         (0x25)

#define ACMP1_CH0_INPUT                      (0x28)
#define ACMP1_CH1_INPUT                      (0x29)
#define ACMP1_CH2_INPUT                      (0x2A)
#define ACMP1_CH3_INPUT                      (0x2B)
#define ACMP1_CH4_INPUT                      (0x2C)
#define ACMP1_OUTPUT                         (0x2D)

// Analog to Digital Converter
#define PIN_MODE_ADC                          (0x3)
#define ADC0_CH0_INPUT                       (0x30)
#define ADC0_CH1_INPUT                       (0x31)
#define ADC0_CH2_INPUT                       (0x32)
#define ADC0_CH3_INPUT                       (0x33)
#define ADC0_CH4_INPUT                       (0x34)
#define ADC0_CH5_INPUT                       (0x35)
#define ADC0_CH6_INPUT                       (0x36)
#define ADC0_CH7_INPUT                       (0x37)

// Analog to Digital Converter & Op Amp
#define PIN_MODE_IDAC                         (0x4)
#define IDAC0_OUTPUT                         (0x40)

#define PIN_MODE_OPAMP_DAC                    (0x5)
#define OPAMP_OPA0_NEG                       (0x50)
#define OPAMP_OPA0_POS                       (0x51)
#define OPAMP_OPA0_OUT                       (0x52)
#define OPAMP_OPA1_NEG                       (0x53)
#define OPAMP_OPA1_POS                       (0x54)
#define OPAMP_OPA1_OUT                       (0x55)
#define OPAMP_OPA2_NEG                       (0x56)
#define OPAMP_OPA2_POS                       (0x57)
#define OPAMP_OPA2_OUT                       (0x58)
#define DAC0_N0                              (0x59)
#define DAC0_P0                              (0x5A)
#define DAC0_N1                              (0x5B)
#define DAC0_P1                              (0x5C)
#define DAC0_OUT0                            (0x5D)
#define DAC0_OUT0ALT                         (0x5E)
#define DAC0_OUT1ALT                         (0x5F)

// Timer
#define PIN_MODE_TIMER                        (0x6)
#define TIMER0_CC0_INPUT                     (0x60)
#define TIMER0_CC1_INPUT                     (0x61)
#define TIMER0_CC2_INPUT                     (0x62)
#define TIMER0_CC0_OUTPUT                    (0x63)
#define TIMER0_CC1_OUTPUT                    (0x64)
#define TIMER0_CC2_OUTPUT                    (0x65)
#define TIMER1_CC0_INPUT                     (0x68)
#define TIMER1_CC1_INPUT                     (0x69)
#define TIMER1_CC2_INPUT                     (0x6A)
#define TIMER1_CC0_OUTPUT                    (0x6B)
#define TIMER1_CC1_OUTPUT                    (0x6C)
#define TIMER1_CC2_OUTPUT                    (0x6D)

// Peripheral Reflex System GPIO Inputs
#define PIN_MODE_PRS_PCNT_WAKE                (0xA)
#define PRS_CH0                              (0xA0)
#define PRS_CH1                              (0xA1)
#define PRS_CH2                              (0xA2)
#define PRS_CH3                              (0xA3)

// Pulse Counter Inputs
#define PCNT0_S0_IN                          (0xA8)
#define PCNT0_S1_IN                          (0xA9)
#define PCNT1_S0_IN                          (0xAA)
#define PCNT1_S1_IN                          (0xAB)
#define PCNT2_S0_IN                          (0xAC)
#define PCNT2_S1_IN                          (0xAD)

// EM4 Wake Up
#define EM4_WAKE_LOW                         (0xAE)  // Low polarity  EM4 wake up (A0,F1,F2,E13)
#define EM4_WAKE_HIGH                        (0xAF)  // High polarity EM4 wake up (A0,F1,F2,E13)

// CMU_OUT0:
#define PIN_MODE_CMU                          (0xB)
#define CMU_CLK0_HFRCO                       (0xB0)  // 0 HFRCO     (directly from osc)
#define CMU_CLK0_HFXO                        (0xB1)  // 1 HFXO      (directly from osc)
#define CMU_CLK0_HFCLK2                      (0xB2)  // 2 HFCLK2    (HFCLK/2)
#define CMU_CLK0_HFCLK4                      (0xB3)  // 3 HFCLK4    (HFCLK/4)
#define CMU_CLK0_HFCLK8                      (0xB4)  // 4 HFCLK8    (HFCLK/8)
#define CMU_CLK0_HFCLK16                     (0xB5)  // 5 HFCLK16   (HFCLK/16)
#define CMU_CLK0_ULFRCO                      (0xB6)  // 6 ULFRCO    (directly from osc)
#define CMU_CLK0_AUXHFRCO                    (0xB7)  // 7 AUXHFRCO  (directly from osc)

// CMU_OUT1:
#define CMU_CLK1_LFRCO                       (0xB8)  // 0 LFRCO     (directly from osc)
#define CMU_CLK1_LFXO                        (0xB9)  // 1 LFXO      (directly from osc)
#define CMU_CLK1_HFCLK                       (0xBA)  // 2 HFCLK
#define CMU_CLK1_LFXOQ                       (0xBB)  // 3 LFXOQ     (LFXO qualified)
#define CMU_CLK1_HFXOQ                       (0xBC)  // 4 HFXOQ     (HFXO qualified)
#define CMU_CLK1_LFRCOQ                      (0xBD)  // 5 LFRCOQ    (LFRCO qualified)
#define CMU_CLK1_HFRCOQ                      (0xBE)  // 6 HFRCOQ    (HFRCO qualified)
#define CMU_CLK1_AUXHFRCOQ                   (0xBF)  // 7 AUXHFRCOQ (AUXHFRCO qualified)

// USART
#define PIN_MODE_USART                        (0xC)
#define USART0_SPI_CLK                       (0xC0)
#define USART0_SPI_CS                        (0xC1)
#define USART0_SPI_RX                        (0xC2)
#define USART0_SPI_TX                        (0xC3)
#define USART0_UART_RX                       (0xC4)
#define USART0_UART_TX                       (0xC5)

#define USART1_SPI_CLK                       (0xC8)
#define USART1_SPI_CS                        (0xC9)
#define USART1_SPI_RX                        (0xCA)
#define USART1_SPI_TX                        (0xCB)
#define USART1_UART_RX                       (0xCC)
#define USART1_UART_TX                       (0xCD)

// I2C
#define PIN_MODE_I2C                          (0xD)
#define I2C0_SCL                             (0xD0)
#define I2C0_SDA                             (0xD1)
#define I2C1_SCL                             (0xD2)
#define I2C1_SDA                             (0xD3)

// ----------------------------------------------------------------------------

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
