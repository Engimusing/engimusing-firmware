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
#include "HABTUTOR.h"
#include "tickHandler.h"
#include "switches.h"
#include <Arduino.h>

extern LEUARTClass Serial;
extern AnalogLP Analog;
TimersLP Timer;

static const char *onoff[]   = {"ON","OFF"};

tickHandler redsw;
tickHandler blacksw;
tickHandler reedsw;
tickHandler lightsens;
tickHandler potpub;

switchesClass sw_reed("REED",  ReedSwitchISR,  3, SW_DETECTOR);
switchesClass sw_red("RED",    RedSwitchISR,   2, SW_MOMENTARY);
switchesClass sw_blk("BLACK",  BlackSwitchISR, 2, SW_MOMENTARY);
switchesClass sw_sen("SENSOR", LightSensorISR, 2, SW_MOMENTARY);

void ReedSwitchISR(void)
{
}

void RedSwitchISR(void)
{
  sw_red.sw_int++;
}

void BlackSwitchISR(void)
{
  sw_blk.sw_int++;
}

void LightSensorISR(void)
{
  sw_sen.sw_int++;
}


// PD7 - Red Switch
// PC0 - QRE Sensor Out
// PC1 - Switch Pullup
// PC4 - Buzzer
// PB7 - Red LED
// PB8 - Reed Switch
// PD6 - ADC Voltage
// PD4 - Black Switch
void HABTUTORClass::begin(const char* mod)
{
  pinMode( SWPULL_PIN, OUTPUT);       // Switch pull up
  digitalWrite(SWPULL_PIN, HIGH);

  sw_red.begin(REDSW_PIN, module);
  sw_blk.begin(BLKSW_PIN, module);
  sw_reed.begin(REEDSW_PIN, module);
  sw_sen.begin(LTSENS_PIN, module);

  pinMode(HABLED_PIN, OUTPUT);       // LED
  pinMode(BUZZER_PIN, OUTPUT);       // Buzzer

  buzzer_freq     = 1000;
  buzzer_duration = 0;
  buzzer_state    = 0;

  module = (uint8_t*)mod;
  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
  tick_5s = 0;
}

void HABTUTORClass::update(void)
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

void HABTUTORClass::handle_tick(void)
{
  sw_red.pub_switch(module);
  sw_blk.pub_switch(module);
  sw_reed.pub_switch(module);
  sw_sen.pub_switch(module);
  if(potpub.serviceTick()) {pub_pot_voltage();}
}

void HABTUTORClass::sch_pot_voltage(uint32_t interval)
{
  potpub.setInterval(interval);
}

void HABTUTORClass::pub_pot_voltage(void)
{
  uint32_t r = Analog.analogReadVDDsample();
  Analog.analogReference(INTERNALVDD);
  Analog.analogReadResolution(RES_12BITS);
  uint32_t v = Analog.analogReadPin(POT_PIN);
  uint32_t mV =  ((v * r)/4096);
  Serial.printf("{\"TOP\":\"%s?/POT\",\"PLD\":\"%d.%dV\"}\n\r",module, mV/1000, mV%1000);
}

int8_t HABTUTORClass::compare_token(uint8_t* inTok, const char* cmpTok)
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

int8_t HABTUTORClass::decode_cmd(void)
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
  if(compare_token(&COMM.topic[j],"LED")) {
    if(compare_token(COMM.payload,"ON")) {
      digitalWrite(HABLED_PIN, HIGH);
    } else if(compare_token(COMM.payload,"OFF")) {
      digitalWrite(HABLED_PIN, LOW);
    } else if(compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/LED\",\"PLD\":\"%s\"}\r\n",module, onoff[digitalRead(HABLED_PIN)]);
    } else {return 0;}
    return 1;
  }
  if(compare_token(&COMM.topic[j],"POT")) {
    pub_pot_voltage();
    return 1;
  }
  if(compare_token(&COMM.topic[j],"SWITCH/RED")) {
    Serial.printf("{\"TOP\":\"%s?/SWITCH/RED\",\"PLD\":\"%s\"}\r\n",module,onoff[digitalRead(REDSW_PIN)]);
    return 1;
  }
  if(compare_token(&COMM.topic[j],"SWITCH/BLACK")) {
    Serial.printf("{\"TOP\":\"%s?/SWITCH/BLACK\",\"PLD\":\"%s\"}\r\n",module,onoff[digitalRead(BLKSW_PIN)]);
    return 1;
  }
  if(compare_token(&COMM.topic[j],"SWITCH/REED")) {
    Serial.printf("{\"TOP\":\"%s?/SWITCH/REED\",\"PLD\":\"%s\"}\r\n",module,onoff[digitalRead(REEDSW_PIN)]);
    return 1;
  }
  if(compare_token(&COMM.topic[j],"SENSOR/QRE")) {
    Serial.printf("{\"TOP\":\"%s?/SENSOR/QRE\",\"PLD\":\"%s\"}\r\n",module,onoff[digitalRead(LTSENS_PIN)]);
    return 1;
  }
  if(compare_token(&COMM.topic[j],"BUZZER")) {
    if(compare_token(COMM.payload,"ON")) {
      Timer.noTone(BUZZER_PIN);
      Timer.tone(BUZZER_PIN, buzzer_freq, buzzer_duration);
      buzzer_state = 1;
    } else if(compare_token(COMM.payload,"OFF")) {
      Timer.noTone(BUZZER_PIN);
      buzzer_state = 0;
    } else if(compare_token(COMM.payload,"F")) {
      uint32_t f = atoi((char*)&COMM.payload[1]);
      if((f >= 0) && (f < 20000)) {
	buzzer_freq = f;
      }
    } else if(compare_token(COMM.payload,"D")) {
      uint32_t d = atoi((char*)&COMM.payload[1]);
      if(d >= 0) {
	buzzer_duration = d;
      }
    } else if(compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/BUZZER\",\"PLD\":\"%s\"}\r\n",module, buzzer_state);
    } else {return 0;}
    return 1;
  }
}

HABTUTORClass HABT;


