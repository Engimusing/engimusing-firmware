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
  void begin(uint8_t*);
  void update(void);
  void sch_temp_cel(uint32_t interval, uint8_t* item_module);
  void sch_temp_far(uint32_t interval, uint8_t* item_module);
  void sch_cpu_vdd(uint32_t interval, uint8_t* item_module);
 private:
  uint8_t* module;
  static void decode_cmd(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
  void handle_tick(void);
  void pub_temp_cel(uint8_t* item_module);
  void pub_temp_far(uint8_t* item_module);
  void pub_cpu_vdd(uint8_t* item_module);

  uint32_t tick;
};


extern EFM32ZGUSBClass ZGUSB;

