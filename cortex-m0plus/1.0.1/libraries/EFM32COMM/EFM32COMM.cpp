/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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
#include <Arduino.h>

extern LEUARTClass Serial;

// --------------------------------- Basic JSON Communication Class -------------------------

uint8_t EFM32COMMClass::decode_done = 0;

EFM32COMMClass::EFM32COMMClass()
{
  topic   = &item_topic[0];
  payload = &item_payload[0];
  isCnt = 0;
  charCnt = 0;
  state = Idle;
  subscribe_heartbeat = 300;
}

int8_t EFM32COMMClass::decode(void)
{
  if (Serial.available()) {
    char c = (char)Serial.read(); // get the new byte:
    if(isgraph(c)) {
      //Serial.print(c);
      return getInputString(c);
    } else {
      return 0;
    }
  }
  decode_done = 0;
}

int8_t EFM32COMMClass::getInputString(char c)
{
  if(c == '{') {
    state = gettingLine;
    isCnt = 0;
    addCharToInputString(c);
    return 0;
  } else if(state != Idle) {
    if(c == '}') {
      state = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
      //Serial.printf("%s\r\n",inputString);
      int8_t r = parseLine();
      inputString[0]  = '\0';
      isCnt = 0;
      return r;
    } else {
      addCharToInputString(c);
      return 0;
    }
  }
}

void EFM32COMMClass::addCharToInputString(char c)
{
  //  Serial.printf("isCnt = %d c = %c\r\n",isCnt,c);
  inputString[isCnt++] = c;
  if(isCnt >= COMM_STRING_LENGTH) {
    isCnt = 0;
    state = Idle;
  }
}


int8_t EFM32COMMClass::parseLine(void)
{
  static uint8_t debug = 0;

  item_topic[0]   = '\0';
  item_payload[0] = '\0';

  int8_t r = 0;

  for(isCnt = 0; inputString[isCnt] != '\0'; isCnt++) {
    uint8_t* c = &inputString[isCnt];
    if( (c[0] == '{') || (c[0] == ',') && (c[1] == '\"')) {
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	r = getToken(&c[5], item_topic, MODULE_STRING_LENGTH);
	if(debug) {Serial.printf("TOP = %s\r\n", item_topic);}
      }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	r += getToken(&c[5], item_payload, ITEM_PAYLOAD_LENGTH);
	if(debug) {Serial.printf("PLD = %s\r\n", item_payload);}
      }
    }
  }
  if(debug) {Serial.printf("topic   = %s\r\n", topic);}
  if(debug) {Serial.printf("payload = %s\r\n\r\n", payload);}
  return r;
}

int8_t EFM32COMMClass::getToken(uint8_t* str, uint8_t* item, uint8_t tok_length)
{
  uint8_t i;

  if((str[0] == '\"') && (str[1] == ':') && (str[2] == '\"')) {
    for(i = 3; (i < tok_length) && (str[i] != '\"') && (str[i] != '\0'); i++) {
      item[i-3] = str[i];
    }
    item[i-3] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int8_t EFM32COMMClass::compare_token(uint8_t* inTok, const char* cmpTok)
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

EFM32COMMClass COMM;

// ------------------------------- Detector Switch Class -------------------------

void detectorSwitchClass::begin(uint8_t _pin, const char* mod, uint8_t bounce_count)
{
  pin = _pin;
  module = (uint8_t*)mod;
  bounce_cnt = bounce_count;
  intrPinMode(pin, INPUT_PU_FILTER);
  switch_state = (~intrDigitalRead(pin) & 0x01);
  switch_msg(switch_state);
  event_in_progress = 0;
}

void detectorSwitchClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    uint8_t current_switch = (~intrDigitalRead(pin) & 0x01);

    if((event_in_progress == 0) && (switch_state != current_switch) ) { // switch event happened
      event_in_progress = 1;
    } else if((event_in_progress > 0) && (event_in_progress < bounce_cnt)) { // wait until bounce count
      event_in_progress++;
    } else if(event_in_progress >= bounce_cnt) { // report event
      if(switch_state != current_switch) {
	switch_state = current_switch;
	switch_msg(current_switch);
      }
      event_in_progress = 0;
      return;
    }
    if(tick_5s++ >= COMM.subscribe_heartbeat) { // subscribe every 5s for a heartbeat
      tick_5s = 0;
      Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
    }
  }
}

void detectorSwitchClass::decode(void)
{
  if(COMM.decode_done) {return;}
  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"SWITCH")) {
    switch_msg(~intrDigitalRead(pin) & 0x1);
    COMM.decode_done = 1;
    return;
  }
}

void detectorSwitchClass::switch_msg(uint8_t current_switch)
{

  Serial.printf("{\"TOP\":\"%s?/SWITCH\",\"PLD\":\"", module);

  if(current_switch) {
    Serial.printf("CLOSED\"}\r\n");
  } else {
    Serial.printf("OPEN\"}\r\n");
  }
}

// ------------------------------- Momentary Switch Class ------------------------

void momentarySwitchClass::begin(uint8_t _pin, const char* mod, uint8_t bounce_count)
{
  pin = _pin;
  intrPinMode(pin, INPUT_PU_FILTER);
  module = (uint8_t*)mod;
  INTR.attachIntrCounter(pin, RISING);
  event_in_progress = 0;
  bounce_cnt = bounce_count;
  tick = 0;
}

void momentarySwitchClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    uint8_t sw_int = INTR.read_clr_nints(pin);

    if((event_in_progress == 0) && (sw_int > 0) ) { // switch event happened
      event_in_progress = 1;
    } else if((event_in_progress > 0) && (event_in_progress < bounce_cnt)) { // wait until bounce count
      event_in_progress++;
    } else if(event_in_progress >= bounce_cnt) { // report event
      Serial.printf("{\"TOP\":\"%s?/SWITCH\",\"PLD\":\"CLOSED\"}\r\n", module);
      event_in_progress = 0;
      return;
    }
  }
}

// ------------------------------- On/Off Control Class --------------------------

void onOffCtlClass::begin(uint8_t _pin, const char* mod, uint8_t act)
{
  pin = _pin;
  module = (uint8_t*)mod;
  active = act;
  if(active == HIGH) {
    on = HIGH;
    off = LOW;
  } else {
    on = LOW;
    off = HIGH;
  }

  pinMode(pin, OUTPUT);       // LED

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
  tick_5s = 0;
}

void onOffCtlClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(tick_5s++ >= COMM.subscribe_heartbeat) { // subscribe every 5s for a heartbeat
      tick_5s = 0;
      Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
    }
  }
}

void onOffCtlClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"CTL")) {
    if(COMM.compare_token(COMM.payload,"ON")) {
      digitalWrite(pin, on);
    } else if(COMM.compare_token(COMM.payload,"OFF")) {
      digitalWrite(pin, off);
    } else if(COMM.compare_token(COMM.payload,"STATUS")) {
      uint8_t val = (active == HIGH) ? digitalRead(pin) : ~digitalRead(pin);
      Serial.printf("{\"TOP\":\"%s?/LED\",\"PLD\":\"%s\"}\r\n",module, onoff[val & 0x01]);
    } else {return;}
    COMM.decode_done = 1;
    return;
  }
}

// ------------------------------- Tone Control Class ----------------------------

void toneCtlClass::begin(uint8_t _pin, const char* mod)
{
  pin = _pin;
  module = (uint8_t*)mod;

  pinMode(pin, OUTPUT);       // LED

  tone_freq     = 1000;
  tone_duration = 0;
  tone_state    = 0;

  TimersLP Timer;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
  tick_5s = 0;
}

void toneCtlClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(tick_5s++ >= COMM.subscribe_heartbeat) { // subscribe every 5s for a heartbeat
      tick_5s = 0;
      Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
    }
  }
}

void toneCtlClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"TONE")) {
    if(COMM.compare_token(COMM.payload,"ON")) {
      Timer.noTone(pin);
      Timer.tone(pin, tone_freq, tone_duration);
      tone_state = 1;
    } else if(COMM.compare_token(COMM.payload,"OFF")) {
      Timer.noTone(pin);
      tone_state = 0;
    } else if(COMM.compare_token(COMM.payload,"F")) {
      uint32_t f = atoi((char*)&COMM.payload[1]);
      if((f >= 0) && (f < 20000)) {
	tone_freq = f;
      }
    } else if(COMM.compare_token(COMM.payload,"D")) {
      uint32_t d = atoi((char*)&COMM.payload[1]);
      if(d >= 0) {
	tone_duration = d;
      }
    } else if(COMM.compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/TONE\",\"PLD\":\"%s\"}\r\n",module, onoff[tone_state]);
    } else {return;}
    COMM.decode_done = 1;
    return;
  }
}

// ------------------------------- ADC Pin Class ---------------------------------

void adcCtlClass::begin(uint8_t _pin, const char* mod, uint32_t intrval)
{
  pin = _pin;
  module = (uint8_t*)mod;
  interval = intrval;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void adcCtlClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(interval != 0) {
      if(current <= 0) {
	current = interval;
	publishADCvoltage();
      } else {
	current--;
      }
    }
  }
}

void adcCtlClass::publishADCvoltage(void)
{
  uint32_t r = Analog.analogReadVDDsample();
  Analog.analogReference(INTERNALVDD);
  Analog.analogReadResolution(RES_12BITS);
  uint32_t v = Analog.analogReadPin(pin);
  uint32_t mV =  ((v * r)/4096);
  Serial.printf("{\"TOP\":\"%s?/ADC\",\"PLD\":\"%d.%dV\"}\n\r",module, mV/1000, mV%1000);
}

void adcCtlClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"ADC")) {
    publishADCvoltage();
    COMM.decode_done = 1;
    return;
  }
}

// ------------------------------- CPU VDD ADC Class -----------------------------

void cpuVDDClass::begin(const char* mod, uint32_t intrval)
{
  module = (uint8_t*)mod;
  interval = intrval;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void cpuVDDClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(interval != 0) {
      if(current <= 0) {
	current = interval;
	publishCPUvoltage();
      } else {
	current--;
      }
    }
  }
}

void cpuVDDClass::publishCPUvoltage(void)
{
  uPvdd vddval = Analog.analogReadVDD();
  Serial.printf("{\"TOP\":\"%s?/ADC\",\"PLD\":\"%d.%dV\"}\r\n",module, vddval.wholeVDD, vddval.fracVDD);
}

void cpuVDDClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"ADC")) {
    publishCPUvoltage();
    COMM.decode_done = 1;
    return;
  }
}

// ------------------------------- CPU Temperature Class -------------------------

void cpuTempClass::begin(const char* mod, uint32_t Fintrval, uint32_t Cintrval)
{
  module = (uint8_t*)mod;
  intervalF = Fintrval;
  intervalC = Cintrval;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void cpuTempClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(intervalC != 0) {
      if(currentC <= 0) {
	currentC = intervalC;
	publishCPUtempC();
      } else {
	currentC--;
      }
    }
    if(intervalF != 0) {
      if(currentF <= 0) {
	currentF = intervalF;
	publishCPUtempF();
      } else {
	currentF--;
      }
    }
  }
}

void cpuTempClass::publishCPUtempC(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/TMPC\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeC, tempval.fracC);
}

void cpuTempClass::publishCPUtempF(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/TMPF\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeF, tempval.fracF);
}

void cpuTempClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"TMPC")) {
    publishCPUtempC();
    COMM.decode_done = 1;
    return;
  }
  if(COMM.compare_token(&COMM.topic[j],"TMPF")) {
    publishCPUtempF();
    COMM.decode_done = 1;
    return;
  }
}







