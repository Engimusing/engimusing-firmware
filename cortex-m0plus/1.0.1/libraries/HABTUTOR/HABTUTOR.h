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

#define BLKSW_PIN     2
#define POT_PIN       3
#define REEDSW_PIN    4
#define HABLED_PIN    5
#define BUZZER_PIN    6
#define SWPULL_PIN    7
#define LTSENS_PIN    8
#define REDSW_PIN    10


void ReedSwitchISR(void);
void RedSwitchISR(void);
void BlackSwitchISR(void);
void LightSensorISR(void);


class HABTUTORClass
{
 public:
  void begin(const char*);
  void update(void);
  void sch_pot_voltage(uint32_t interval);
  int8_t decode_cmd(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  uint32_t buzzer_freq;
  uint32_t buzzer_duration;
  uint32_t buzzer_state;
  void handle_tick(void);
  void pub_red_switch(void);
  void pub_black_switch(void);
  void pub_reed_switch(void);
  void pub_light_sensor(void);
  void pub_pot_voltage(void);
  int8_t compare_token(uint8_t* inTok, const char* cmpTok);
};


extern HABTUTORClass HABT;

