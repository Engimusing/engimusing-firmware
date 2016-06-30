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


#include "efm_pin_config.h"
#include "pins_arduino.h"
#include "cmsis.h"

uint8_t pinMode(uint32_t pin, uint32_t mode)
{
  if(valid_pin(pin)) {
    GPIO_config(dPorts[pin], dPins[pin], mode);
    return 1;
  }
  return 0;
}

uint8_t intrPinMode(uint32_t pin, uint32_t mode)
{
  if(valid_pin(pin)) {
    GPIO_config(iPorts[pin], iPins[pin], mode);
    return 1;
  }
  return 0;
}

int intrDigitalRead(uint32_t pin)
{
  if(valid_pin(pin)) {
    return (GPIO->P[iPorts[pin]].DIN >> iPins[pin]) & 0x1;
  }
  return 0;
}

void digitalWrite(uint32_t pin, uint32_t val)
{
  if(valid_pin(pin)) {
    if(val == HIGH) {
      GPIO->P[dPorts[pin]].DOUTSET = (1 << dPins[pin]);
    } else {
      GPIO->P[dPorts[pin]].DOUTCLR = (1 << dPins[pin]);
    }
  }
}

int digitalRead(uint32_t pin)
{
  if(valid_pin(pin)) {
    return (GPIO->P[dPorts[pin]].DIN >> dPins[pin]) & 0x1;
  }
  return 0;
}

void GPIO_pinMode(GPIO_Port_TypeDef port, uint32_t pin, GPIO_Mode_TypeDef mode)
{
  int shift = (pin & 0x7) << 2;
  uint32_t mask  = GPIO_MODE_MASK << shift;
  uint32_t pmode = mode << shift;

  if(pin < 8) {
    GPIO->P[port].MODEL = (GPIO->P[port].MODEL & ~mask) | pmode;
  } else {
    GPIO->P[port].MODEH = (GPIO->P[port].MODEH & ~mask) | pmode;
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

