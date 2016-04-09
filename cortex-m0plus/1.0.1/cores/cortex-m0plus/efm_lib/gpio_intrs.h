/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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

#include "Arduino.h"
#include <stdint.h>
#include "wiring_constants.h"
#include "efm_gpio.h"
#include "pins_arduino.h"

#define NUMBER_GPIO_INTRS 16

class INTRClass
{
  public:
    INTRClass();
    void attachIntr(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);
    void detachIntr(uint8_t pin);
    void GPIO_ODD_IRQHandler(void);
    void GPIO_EVEN_IRQHandler(void);
    uint8_t read_nints(uint8_t);
    uint8_t read_clr_nints(uint8_t);
    uint8_t read_decrement_nints(uint8_t);
  private:
    uint8_t nints[NUMBER_GPIO_INTRS];
};

