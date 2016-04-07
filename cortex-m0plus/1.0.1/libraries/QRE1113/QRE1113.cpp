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

#include "EFM32COMM.h"
#include "QRE1113.h"
#include "tickHandler.h"
#include "switches.h"
#include <Arduino.h>

extern LEUARTClass Serial;
TimersLP Timer;

static const char *onoff[]   = {"ON","OFF"};

tickHandler lightsens;

switchesClass sw_sen("SENSOR", LightSensorISR, 2, SW_MOMENTARY);

void LightSensorISR(void)
{
  sw_sen.sw_int++;
}

void QRE1113Class::begin(uint8_t pin, const char* mod)
{
  module = (uint8_t*)mod;
  Serial.printf("module = %s\r\n",module);
  tick = 0;
  tick_5s = 0;

  qre_pin = pin;
  sw_sen.begin(pin, module);
  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
}

void QRE1113Class::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    handle_tick();
    tick_5s++;
  }
  if(tick_5s >= 50) { // subscribe every 5s for a heartbeat
    tick_5s = 0;
    Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  }
}

void QRE1113Class::handle_tick(void)
{
  sw_sen.pub_switch(module);
}

int8_t QRE1113Class::compare_token(uint8_t* inTok, const char* cmpTok)
{
  int8_t iLen = strlen((char*) inTok);
  int8_t cLen = strlen((char*) cmpTok);
  if(iLen < cLen) {
    return 0;
  }
  for(int i = 0; i < cLen; i++) {
    if(inTok[i] != cmpTok[i]) {
      return 0;
    }
  }
  return 1;
}

int8_t QRE1113Class::decode_cmd(void)
{
  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return 0;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return 0;
    }
  }
  j++;
  if(compare_token(&COMM.topic[j],"SENSOR/QRE")) {
    Serial.printf("{\"TOP\":\"%s?/SENSOR/QRE\",\"PLD\":\"%s\"}\r\n",module, onoff[intrDigitalRead(qre_pin) & 0x1]);
    return 1;
  }
}


