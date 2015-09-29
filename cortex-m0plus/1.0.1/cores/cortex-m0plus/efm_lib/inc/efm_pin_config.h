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


#ifndef __EFM_PIN_CONFIG_H
#define __EFM_PIN_CONFIG_H

#include "em_device.h"
#include "em_gpio.h"
#include "wiring_constants.h"

#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

#define GPIO_MODE_MASK                          0x0000000FUL  // BIT MASK
#define GPIO_MODE_DISABLED                      0x00000000UL  // DISABLED
#define GPIO_MODE_INPUT                         0x00000001UL  // INPUT
#define GPIO_MODE_INPUTPULL                     0x00000002UL  // INPUTPULL
#define GPIO_MODE_INPUTPULLFILTER               0x00000003UL  // INPUTPULLFILTER
#define GPIO_MODE_PUSHPULL                      0x00000004UL  // PUSHPULL
#define GPIO_MODE_PUSHPULLDRIVE                 0x00000005UL  // PUSHPULLDRIVE
#define GPIO_MODE_WIREDOR                       0x00000006UL  // WIREDOR
#define GPIO_MODE_WIREDORPULLDOWN               0x00000007UL  // WIREDORPULLDOWN
#define GPIO_MODE_WIREDAND                      0x00000008UL  // WIREDAND
#define GPIO_MODE_WIREDANDFILTER                0x00000009UL  // WIREDANDFILTER
#define GPIO_MODE_WIREDANDPULLUP                0x0000000AUL  // WIREDANDPULLUP
#define GPIO_MODE_WIREDANDPULLUPFILTER          0x0000000BUL  // WIREDANDPULLUPFILTER
#define GPIO_MODE_WIREDANDDRIVE                 0x0000000CUL  // WIREDANDDRIVE
#define GPIO_MODE_WIREDANDDRIVEFILTER           0x0000000DUL  // WIREDANDDRIVEFILTER
#define GPIO_MODE_WIREDANDDRIVEPULLUP           0x0000000EUL  // WIREDANDDRIVEPULLUP
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER     0x0000000FUL  // WIREDANDDRIVEPULLUPFILTER

#define DRIVEMODE_STANDARD                      0x00000000UL
#define DRIVEMODE_LOWEST                        0x00000001UL
#define DRIVEMODE_HIGH                          0x00000002UL
#define DRIVEMODE_LOW                           0x00000003UL

void GPIO_config(uint32_t port, uint32_t pin, uint32_t ulMode);

#endif  // __EFM_PIN_CONFIG_H
