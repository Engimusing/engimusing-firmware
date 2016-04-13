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

#pragma once

#include "Arduino.h"

extern INTRClass INTR;
extern LEUARTClass Serial;
extern AnalogLP Analog;

// --------------------------------- Basic JSON Communication Class -------------------------

#define MODULE_TABLE_ENTRIES    8
#define MODULE_STRING_LENGTH   40
#define COMM_STRING_LENGTH    253
#define ITEM_TOKEN_LENGTH      24
#define ITEM_PAYLOAD_LENGTH    32
#define NUMBER_ELEMENTS         3
#define ITEM_TYPE               0
#define ITEM_ID                 1
#define ITEM_ACTION             2

enum giState {
  Idle,
  gettingLine,
};

class EFM32COMMClass
{
 public:
  uint8_t* topic;
  uint8_t* payload;
  static uint8_t decode_done;
  EFM32COMMClass();
  int8_t decode(void);
  int8_t add_module(uint8_t*, void (*cmd)(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*));
  int8_t compare_token(uint8_t* inTok, const char* cmpTok);
 private:
  int8_t getInputString(char);
  int8_t substrcmp(uint8_t* str, uint8_t* sub, uint8_t start);
  int8_t parseLine(void);
  uint8_t inputString[COMM_STRING_LENGTH+3];
  void addCharToInputString(char c);
  int8_t getToken(uint8_t* str, uint8_t* item, uint8_t tok_length);
  uint8_t item_topic[MODULE_STRING_LENGTH];
  uint8_t item_payload[ITEM_PAYLOAD_LENGTH];
  uint8_t isCnt;
  uint8_t charCnt;
  giState state;
};

extern EFM32COMMClass COMM;

// --------------------------------- Detector Switch Class -------------------------

class detectorSwitchClass
{
 public:
  void begin(uint8_t _pin, const char* module, uint8_t bounce_count);
  void update(void); // publish changes in switch state
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  uint32_t pin;  // connector pin connected to switch
  uint8_t event_in_progress; // switch event in progress
  uint32_t switch_state;
  uint8_t bounce_cnt; // bounce filter value, 0 = no filter, 0xff = momentary
  void switch_msg(uint8_t current_switch);
};

// ------------------------------- Momentary Switch Class -------------------------

class momentarySwitchClass
{
 public:
  void begin(uint8_t _pin, const char* module, uint8_t bounce_count);
  void update(void); // publish changes in switch state
 private:
  uint8_t* module;
  uint32_t tick;
  uint8_t pin;  // connector pin connected to switch
  uint8_t event_in_progress; // switch event in progress
  uint8_t bounce_cnt; // bounce filter value, 0 = no filter, 0xff = momentary
};

// ------------------------------- On/Off Control Class -------------------------

class onOffCtlClass
{
 public:
  void begin(uint8_t _pin, const char* module);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  uint32_t pin;
};

// ------------------------------- Tone Control Class -------------------------

class toneCtlClass
{
 public:
  void begin(uint8_t _pin, const char* module);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  uint32_t pin;
  uint32_t tone_freq;
  uint32_t tone_duration;
  uint32_t tone_state;
  TimersLP Timer;
};

// ------------------------------- ADC Pin Class -------------------------

class adcCtlClass
{
 public:
  void begin(uint8_t _pin, const char* module, uint32_t interval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t current;
  uint32_t interval;
  uint32_t pin;
  void publishADCvoltage(void);
};

// ------------------------------- CPU VDD ADC Class -------------------------

class cpuVDDClass
{
 public:
  void begin(const char* module, uint32_t interval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t current;
  uint32_t interval;
  void publishCPUvoltage(void);
};

// ------------------------------- CPU Temperature Class -------------------------

class cpuTempClass
{
 public:
  void begin(const char* module, uint32_t Finterval, uint32_t Cinterval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t currentF;
  uint32_t currentC;
  uint32_t intervalF;
  uint32_t intervalC;
  void publishCPUtempC(void);
  void publishCPUtempF(void);
};

