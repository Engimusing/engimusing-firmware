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
#include "EFM32ZGUSB.h"
#include "tickHandler.h"
#include <Arduino.h>


extern LEUARTClass Serial;
extern AnalogLP Analog;

static const char *onoff[]   = {"ON","OFF"};

tickHandler tempcpub;
tickHandler tempfpub;
tickHandler vddpub;

void EFM32ZGUSBClass::begin(const char* mod)
{
  module = (uint8_t*)mod;
  Serial.printf("module = %s\r\n",module);
  tick = 0;
}

void EFM32ZGUSBClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    handle_tick();
  }
}

void EFM32ZGUSBClass::handle_tick(void)
{
  if(tempcpub.serviceTick()) {pub_temp_cel();}
  if(tempfpub.serviceTick()) {pub_temp_far();}
  if(vddpub.serviceTick())   {pub_cpu_vdd();}
}

void EFM32ZGUSBClass::sch_temp_cel(uint32_t interval)
{
  tempcpub.setInterval(interval);
}

void EFM32ZGUSBClass::sch_temp_far(uint32_t interval)
{
  tempfpub.setInterval(interval);
}

void EFM32ZGUSBClass::sch_cpu_vdd(uint32_t interval)
{
  vddpub.setInterval(interval);
}

void EFM32ZGUSBClass::pub_temp_cel(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/CPU/TMPC\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeC, tempval.fracC);
}

void EFM32ZGUSBClass::pub_temp_far(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/CPU/TMPF\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeF, tempval.fracF);
}

void EFM32ZGUSBClass::pub_cpu_vdd(void)
{
  uPvdd vddval = Analog.analogReadVDD();
  Serial.printf("{\"TOP\":\"%s?/CPU/VDD\",\"PLD\":\"%d.%d\"}\r\n",module, vddval.wholeVDD, vddval.fracVDD);
}

int8_t EFM32ZGUSBClass::compare_token(uint8_t* inTok, const char* cmpTok)
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

int8_t EFM32ZGUSBClass::decode_cmd(void)
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
  if(compare_token(&COMM.topic[j],"LED/RED")) {
    if(compare_token(COMM.payload,"ON")) {
      digitalWrite(RED_LED, LOW);
    } else if(compare_token(COMM.payload,"OFF")) {
      digitalWrite(RED_LED, HIGH);
    } else if(compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/LED/RED\",\"PLD\":\"%s\"}\r\n",module, onoff[digitalRead(RED_LED)]);
    } else {return 0;}
    return 1;
  }
  if(compare_token(&COMM.topic[j],"LED/BLUE")) {
    if(compare_token(COMM.payload,"ON")) {
      digitalWrite(BLUE_LED, LOW);
    } else if(compare_token(COMM.payload,"OFF")) {
      digitalWrite(BLUE_LED, HIGH);
    } else if(compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/LED/BLUE\",\"PLD\":\"%s\"}\r\n",module, onoff[digitalRead(BLUE_LED)]);
    } else {return 0;}
    return 1;
  }
  if(compare_token(&COMM.topic[j],"LED/GREEN")) {
    if(compare_token(COMM.payload,"ON")) {
      digitalWrite(GREEN_LED, LOW);
    } else if(compare_token(COMM.payload,"OFF")) {
      digitalWrite(GREEN_LED, HIGH);
    } else if(compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/LED/GREEN\",\"PLD\":\"%s\"}\r\n",module, onoff[digitalRead(GREEN_LED)]);
    } else {return 0;}
    return 1;
  }
  if(compare_token(&COMM.topic[j],"CPU/TMPC")) {
    pub_temp_cel();
    return 1;
  }
  if(compare_token(&COMM.topic[j],"CPU/TMPF")) {
    pub_temp_far();
    return 1;
  }
  if(compare_token(&COMM.topic[j],"CPU/VDD")) {
    pub_cpu_vdd();
    return 1;
  }
}


EFM32ZGUSBClass ZGUSB;

