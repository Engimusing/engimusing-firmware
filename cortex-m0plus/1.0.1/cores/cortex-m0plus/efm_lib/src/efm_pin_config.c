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

// P5-2:
// PD4  - ADC4
// PC15 - GPIO

// P5-3:
// PD6  - ADC6
// PC14 - GPIO
// PE12 - PE12

// P5-4:
// PB8  - US1_CS
// PC3  - GPIO

// P5-5:
// PB7  - US1_CLK
// PC2  - GPIO

// P5-6:
// PB11 - IDAC OUT
// PC4  - ACMP4

// P5-7:
// PA1  - I2C0_SCL
// PC1  - US1_RX

// P5-8:
// PA0  - I2C0_SDA
// PC0  - US1_TX

// P5-10:
// PD7  - ADC7
// PC13 - 
// PE13 - 

// PA8  - LED_GREEN
// PA9  - LED_BLUE
// PA10 - LED_RED

// 0..13  - Digital pins
// 0/1    - SERCOM/UART (Serial1)
// 2..12
// 13 (LED)
// 14..19 - Analog pins
// 20..21 I2C pins (SDA/SCL and also EDBG:SDA/SCL)
// 22..24 - SPI pins (ICSP:MISO,SCK,MOSI)
// 25..26 - RX/TX LEDS (PB03/PA27)
// 27..29 - USB
// 30..41 - EDBG
// 30/31  - EDBG/UART
// 32/33 I2C (SDA/SCL and also EDBG:SDA/SCL)
// 34..37 - EDBG/SPI
// 38..41 - EDBG/Digital
// 42 (AREF)
// 43     - Alternate use of A0 (DAC output)

#include "efm_pin_config.h"

void GPIO_pinMode(GPIO_Port_TypeDef port, unsigned int pin, GPIO_Mode_TypeDef mode)
{
  uint32_t mask, val;

  if(pin < 8) {
    mask = GPIO_MODE_MASK << (pin << 2);
    val = GPIO->P[port].MODEL & ~mask;
    GPIO->P[port].MODEL = val | mode << (pin << 2);
  } else {
    mask = GPIO_MODE_MASK << ((pin & 0x7) << 2);
    val = GPIO->P[port].MODEH & ~mask;
    GPIO->P[port].MODEH = val | mode << ((pin & 0x7) << 2);
  }
}


void GPIO_config(uint32_t port, uint32_t pin, uint32_t ulMode)
{
  uint32_t mode = GPIO_MODE_DISABLED;

  switch(ulMode) {
  case DISABLED_PULLUP:
    mode = GPIO_MODE_DISABLED;
    GPIO->P[port].DOUTSET = 1 << pin;
    break;
  case INPUT:
    mode = GPIO_MODE_INPUT;
    break;
  case INPUT_FILTER:
    mode = GPIO_MODE_INPUT;
    break;
  case INPUT_PULLDOWN:
    mode = GPIO_MODE_INPUTPULL;
    GPIO->P[port].DOUTCLR = 1 << pin;
    break;
  case INPUT_PULLUP:
    mode = GPIO_MODE_INPUTPULL;
    GPIO->P[port].DOUTSET = 1 << pin;
    break;
  case INPUT_PD_FILTER:
    mode = GPIO_MODE_INPUTPULLFILTER;
    GPIO->P[port].DOUTCLR = 1 << pin;
    break;
  case INPUT_PU_FILTER:
    mode = GPIO_MODE_INPUTPULLFILTER;
    GPIO->P[port].DOUTSET = 1 << pin;
    break;
  case OUTPUT:
    mode = GPIO_MODE_PUSHPULL;
    GPIO->P[port].CTRL = DRIVEMODE_STANDARD;
    break;
  case OUTPUT_LOWEST_DRIVE:
    mode = GPIO_MODE_PUSHPULL;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case OUTPUT_LOW_DRIVE:
    mode = GPIO_MODE_PUSHPULL;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case OUTPUT_HIGH_DRIVE:
    mode = GPIO_MODE_PUSHPULL;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_OR:
    mode = GPIO_MODE_WIREDOR;
    break;
  case WIRED_OR_PULLDOWN:
    mode = GPIO_MODE_WIREDORPULLDOWN;
    break;
  case WIRED_AND:
    mode = GPIO_MODE_WIREDAND;
    break;
  case WIRED_AND_LOWEST_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVE;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_LOW_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVE;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_HIGH_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVE;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_FILTER:
    mode = GPIO_MODE_WIREDANDFILTER;
    break;
  case WIRED_AND_FILTER_LOWEST_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_FILTER_LOW_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_FILTER_HIGH_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_PULLUP:
    mode = GPIO_MODE_WIREDANDPULLUP;
  case WIRED_AND_PULLUP_LOWEST_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUP;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_PULLUP_LOW_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUP;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_PULLUP_HIGH_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUP;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_PU_FILTER:
    mode = GPIO_MODE_WIREDANDPULLUPFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_STANDARD;
    break;
  case WIRED_AND_PU_FILTER_LOWEST_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUPFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_PU_FILTER_LOW_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUPFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_PU_FILTER_HIGH_DRIVE:
    mode = GPIO_MODE_WIREDANDDRIVEPULLUPFILTER;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case GPIO_DISABLED:
  default:
    mode = GPIO_MODE_DISABLED;
    break;
  }
  GPIO_pinMode(port, pin, mode);
}


void pinDrive(GPIO_Port_TypeDef port, GPIO_DriveMode_TypeDef ulDrive)
{
  GPIO->P[port].CTRL = ulDrive;
}
