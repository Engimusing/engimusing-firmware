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

#pragma once

#include "Arduino.h"

void LightSensorISR(void);

class QRE1113Class
{
 public:
  void begin(uint8_t pin, const char*);
  void update(void);
  int8_t decode_cmd(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t qre_pin;
  void handle_tick(void);
  void pub_light_sensor(void);
  int8_t compare_token(uint8_t* inTok, const char* cmpTok);
};

