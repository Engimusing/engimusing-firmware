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
#include "wiring_constants.h"

#pragma once

/*
  This class 
 */

class TOGGLEClass
{
 public:
  TOGGLEClass();
  void begin(int toggle_time);
  void begin(int low_time, int high_time);
  void begin(uint32_t dwPin, int low_time, int high_time);
  void begin(uint32_t dwPin, WiringModeTypeDef dwMode, int low_time, int high_time);
  void update(void);
 private:
  int lastMillis;
  int hi_time;
  int lo_time;
  int on;
  uint32_t pin;
};

