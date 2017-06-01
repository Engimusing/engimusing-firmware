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
  This class is used for setting up a digital output to toggle between high and low at a set interval. 
 */

class TOGGLEClass
{
 public:
  TOGGLEClass();
  void begin(int toggleTime, uint8_t activeLevel = HIGH);
  void begin(uint32_t dwPin, int lowTime, int highTime, uint8_t activeLevel = HIGH);
  void begin(uint32_t dwPin, WiringModeTypeDef dwMode, int lowTime, int highTime, uint8_t activeLevel = HIGH);
  void update(void);
  
  void setToggleTime(int time) ;
  
  void setLowHiTimes(int loTime, int hiTime);
  
  int lowTime();
  
  int highTime();
  
 private:
  int myLastMillis;
  int myHiTime;
  int myLoTime;
  int myOn;
  uint32_t myPin;
  uint8_t myActiveLevel;
};

