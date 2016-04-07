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
  EFM32COMMClass();
  int8_t decode(void);
  int8_t add_module(uint8_t*, void (*cmd)(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*));
  uint8_t* topic;
  uint8_t* payload;
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


