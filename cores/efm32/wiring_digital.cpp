/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
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

#include "pins_arduino.h"
#include "em_device.h"

#define INPUT INPUT_




uint8_t pinMode(uint32_t pin, WiringModeTypeDef mode)
{
  if(valid_pin(pin)) {
    GPIO_config(dPorts[pin], dPins[pin], mode);
    return 1;
  }
  return 0;
}

uint8_t intrPinMode(uint32_t pin, WiringModeTypeDef mode)
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
     GPIO_PinOutSet((GPIO_Port_TypeDef)dPorts[pin], dPins[pin]);
    } else {
     GPIO_PinOutClear((GPIO_Port_TypeDef)dPorts[pin], dPins[pin]);
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


void GPIO_config(uint32_t port, uint32_t pin, WiringModeTypeDef ulMode)
{
  GPIO_Mode_TypeDef mode = gpioModeDisabled;

  switch(ulMode) {
  case DISABLED_PULLUP:
    mode = gpioModeDisabled;
    GPIO_PinOutSet((GPIO_Port_TypeDef)port, pin);
    break;
  case INPUT:
    mode = gpioModeInput;
    break;
  case INPUT_FILTER:
    mode = gpioModeInput;
    break;
  case INPUT_PULLDOWN:
    mode = gpioModeInputPull;
    GPIO_PinOutClear((GPIO_Port_TypeDef)port, pin);
    break;
  case INPUT_PULLUP:
    mode = gpioModeInputPull;
    GPIO_PinOutSet((GPIO_Port_TypeDef)port, pin);
    break;
  case INPUT_PD_FILTER:
    mode = gpioModeInputPullFilter;
    GPIO_PinOutClear((GPIO_Port_TypeDef)port, pin);
    break;
  case INPUT_PU_FILTER:
    mode = gpioModeInputPullFilter;
    GPIO_PinOutSet((GPIO_Port_TypeDef)port, pin);
    break;
  case OUTPUT:
    mode = gpioModePushPull;
    GPIO->P[port].CTRL = DRIVEMODE_STANDARD;
    break;
  case OUTPUT_LOWEST_DRIVE:
    mode = gpioModePushPull;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case OUTPUT_LOW_DRIVE:
    mode = gpioModePushPull;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case OUTPUT_HIGH_DRIVE:
    mode = gpioModePushPull;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_OR:
    mode = gpioModeWiredOr;
    break;
  case WIRED_OR_PULLDOWN:
    mode = gpioModeWiredOrPullDown;
    break;
  case WIRED_AND:
    mode = gpioModeWiredAnd;
    break;
    #if defined(_GPIO_P_MODEL_MODE0_WIREDANDDRIVE)
  case WIRED_AND_LOWEST_DRIVE:
    mode = gpioModeWiredAndDrive;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_LOW_DRIVE:
    mode = gpioModeWiredAndDrive;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_HIGH_DRIVE:
    mode = gpioModeWiredAndDrive;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_FILTER_LOWEST_DRIVE:
    mode = gpioModeWiredAndDriveFilter;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_FILTER_LOW_DRIVE:
    mode = gpioModeWiredAndDriveFilter;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_FILTER_HIGH_DRIVE:
    mode = gpioModeWiredAndDriveFilter;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_PULLUP_LOWEST_DRIVE:
    mode = gpioModeWiredAndDrivePullUp;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_PULLUP_LOW_DRIVE:
    mode = gpioModeWiredAndDrivePullUp;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_PULLUP_HIGH_DRIVE:
    mode = gpioModeWiredAndDrivePullUp;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
  case WIRED_AND_PU_FILTER_LOWEST_DRIVE:
    mode = gpioModeWiredAndDrivePullUpFilter;
    GPIO->P[port].CTRL = DRIVEMODE_LOWEST;
    break;
  case WIRED_AND_PU_FILTER_LOW_DRIVE:
    mode = gpioModeWiredAndDrivePullUpFilter;
    GPIO->P[port].CTRL = DRIVEMODE_LOW;
    break;
  case WIRED_AND_PU_FILTER_HIGH_DRIVE:
    mode = gpioModeWiredAndDrivePullUpFilter;
    GPIO->P[port].CTRL = DRIVEMODE_HIGH;
    break;
#endif 
 case WIRED_AND_FILTER:
    mode = gpioModeWiredAndFilter;
    break;
  case WIRED_AND_PULLUP:
    mode = gpioModeWiredAndPullUp;
  case WIRED_AND_PU_FILTER:
    mode = gpioModeWiredAndPullUpFilter;
    GPIO->P[port].CTRL = DRIVEMODE_STANDARD;
    break;
  case GPIO_DISABLED:
  default:
    mode = gpioModeDisabled;
    break;
  }
  GPIO_pinMode((GPIO_Port_TypeDef)port, pin, mode);
}

void enableDebugPins()
{
  //Disable the debug interface so those pins can be used as GPIO or other peripherals 
  GPIO_DbgSWDIOEnable(false);
}
/*
void pinDrive(GPIO_Port_TypeDef port, GPIO_DriveMode_TypeDef ulDrive)
{
  GPIO->P[port].CTRL = ulDrive;
}
*/
