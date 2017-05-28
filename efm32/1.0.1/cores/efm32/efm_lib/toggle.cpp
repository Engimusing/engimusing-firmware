/*
  Copyright (c) 2017 Engimusing LLC.  All right reserved.
  
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

#include <Arduino.h>
#include "toggle.h"

TOGGLEClass::TOGGLEClass()
{
}

void TOGGLEClass::begin(int toggle_time)
{
  TOGGLEClass::begin(LED_BUILTIN, OUTPUT, toggle_time, toggle_time);
}

void TOGGLEClass::begin(int low_time, int high_time)
{
  TOGGLEClass::begin(LED_BUILTIN, OUTPUT, low_time, high_time);
}

void TOGGLEClass::begin(uint32_t dwPin, int low_time, int high_time)
{
  TOGGLEClass::begin(dwPin, OUTPUT, low_time, high_time);
}

void TOGGLEClass::begin(uint32_t dwPin, WiringModeTypeDef dwMode, int low_time, int high_time)
{
  pin = dwPin;
  GPIO_config(dPorts[pin], dPins[pin], dwMode);
  hi_time = high_time;
  lo_time = low_time;
  lastMillis = 0;
  on = HIGH;
}

void TOGGLEClass::update(void)
{
  if(on == HIGH) {
    if(millis() - lastMillis > hi_time) {
      lastMillis = millis();
      GPIO->P[dPorts[pin]].DOUTSET = (1 << dPins[pin]);
      on = LOW;
    }
  }
  if(on == LOW) {
    if (millis() - lastMillis > lo_time) {
      lastMillis = millis();
      GPIO->P[dPorts[pin]].DOUTCLR = (1 << dPins[pin]);
      on = HIGH;
    }
  }
}

