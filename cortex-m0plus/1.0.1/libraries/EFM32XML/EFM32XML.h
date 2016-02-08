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

#define XMLSTRING_LENGTH 253
#define ITEM_TOKEN_LENGTH 16
#define NUMBER_ELEMENTS    3
#define ITEM_TYPE          0
#define ITEM_ID            1
#define ITEM_ACTION        2


class EFM32XMLClass
{
 public:
  EFM32XMLClass();
  void begin(void);
  void decode(void);
  int8_t add_module(uint8_t*, void (*cmd)(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*));
 private:
  void getInputString(char);
  int8_t parse(uint8_t* s, uint8_t cnt, char c);
  int8_t substrcmp(uint8_t* str, uint8_t* sub, uint8_t start);
  void decodeAddress(void);
  void parseLine(void);
  void transferLine(void);
  uint8_t inputString[XMLSTRING_LENGTH+3];
  void addCharToInputString(char c);
  void invalidCPUid(void);
  void invalidAddr(void);
  int8_t getToken(uint8_t* tokS, uint8_t* tokE, uint8_t* item);
  void execute_cmd(uint8_t* item_module, 
		   uint8_t* item_type, 
		   uint8_t* item_id, 
		   uint8_t* item_action,
		   uint8_t* item_p1,
		   uint8_t* item_p2);
};


extern EFM32XMLClass XML;

