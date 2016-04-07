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


EFM32COMMClass::EFM32COMMClass()
{
  topic   = &item_topic[0];
  payload = &item_payload[0];
  isCnt = 0;
  charCnt = 0;
  state = Idle;
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

EFM32COMMClass COMM;

