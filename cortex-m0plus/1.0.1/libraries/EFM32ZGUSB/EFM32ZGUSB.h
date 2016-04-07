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

#define RED_LED       15
#define BLUE_LED      14
#define GREEN_LED     13


class EFM32ZGUSBClass
{
 public:
  void begin(const char*);
  void update(void);
  void sch_temp_cel(uint32_t interval);
  void sch_temp_far(uint32_t interval);
  void sch_cpu_vdd(uint32_t interval);
  int8_t decode_cmd(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  void handle_tick(void);
  void pub_temp_cel(void);
  void pub_temp_far(void);
  void pub_cpu_vdd(void);
  int8_t compare_token(uint8_t* inTok, const char* cmpTok);
};


extern EFM32ZGUSBClass ZGUSB;

