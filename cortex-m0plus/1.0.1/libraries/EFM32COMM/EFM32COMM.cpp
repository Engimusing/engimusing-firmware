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
extern boardIO IO;

static uint8_t isCnt = 0;
static uint8_t charCnt = 0;

enum giState {
  Idle,
  gettingLine,
};

static uint8_t item_module[MODULE_STRING_LENGTH];

static giState state = Idle;

static uint8_t module_table[MODULE_TABLE_ENTRIES][MODULE_STRING_LENGTH] = {'\0'};

static void (*moduleCmd[MODULE_TABLE_ENTRIES])(uint8_t* item_module,
					       uint8_t* item_type, 
					       uint8_t* item_id, 
					       uint8_t* item_action,
					       uint8_t* item_payload);


void EFM32COMMClass::decode(void)
{
  static uint32_t tick = millis();

  if (Serial.available()) {
    char c = (char)Serial.read(); // get the new byte:
    if(isgraph(c)) {
      //Serial.print(c);
      getInputString(c);
    } else {
      return;
    }
  }
}

void EFM32COMMClass::getInputString(char c)
{
  const char devS[] = "{";
  const char devE[] = "}";

  int8_t r = 0;

  if(c == '{') {
    state = gettingLine;
    isCnt = 0;
    addCharToInputString(c);
  } else if(state != Idle) {
    if(c == '}') {
      state = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
      //Serial.printf("%s\r\n",inputString);
      parseLine();
      inputString[0]  = '\0';
      isCnt = 0;
    } else {
      addCharToInputString(c);
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


void EFM32COMMClass::parseLine(void)
{
  // MQTT items
  static uint8_t item_topic[MODULE_STRING_LENGTH];
  static uint8_t item_payload[ITEM_PAYLOAD_LENGTH];
  // JSON items
  static uint8_t item_action[ITEM_TOKEN_LENGTH];
  static uint8_t item_id[ITEM_TOKEN_LENGTH];
  static uint8_t item_type[ITEM_TOKEN_LENGTH];

  static uint8_t debug = 1;

  item_topic[0]   = '\0';
  item_module[0]  = '\0';
  item_type[0]    = '\0';
  item_id[0]      = '\0';
  item_action[0]  = '\0';
  item_payload[0] = '\0';

  for(isCnt = 0; inputString[isCnt] != '\0'; isCnt++) {
    uint8_t* c = &inputString[isCnt];
    if( (c[0] == '{') || (c[0] == ',') && (c[1] == '\"')) {
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	getToken(&c[5], item_topic, MODULE_STRING_LENGTH);
	if(debug) {Serial.printf("TOP = %s\r\n", item_topic);}
      }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	getToken(&c[5], item_payload, ITEM_PAYLOAD_LENGTH);
	if(debug) {Serial.printf("PLD = %s\r\n", item_payload);}
      }
    }
  }
  int topic_length = strlen((char*)item_topic);

  if(debug) {Serial.printf("topic_length = %d\r\n", topic_length);}

  uint8_t i, m, s;
  uint8_t done = false;
  uint8_t equal = false;

  if(topic_length == 0) {
    for(i = 0; (i < MODULE_TABLE_ENTRIES) && module_table[i][0]; i++) {
      if(strcmp((char*)item_module, (char*)module_table[i]) == 0) {
	moduleCmd[i](item_module, item_type, item_id, item_action, item_payload);
	done = true;
	break;
      }
    }
    if(done == false) {
      Serial.printf("{\"ERROR\":\"INVALID_MODULE_%s\"}\r\n",item_module);
    }
  }
  if(topic_length) {
    for(m = 0; (m < MODULE_TABLE_ENTRIES) && module_table[m][0]; m++) {
      if(debug) Serial.printf("module_table[%d] = %s\r\n",m,module_table[m]);
      for(s = 0; s < MODULE_STRING_LENGTH; s++) {
	item_module[s] = module_table[m][s];
	if(item_topic[s] != module_table[m][s]) {
	  if(debug) Serial.printf("topic not equal %d\r\n",m);
	  break;
	}
      }
      if((item_topic[s] == '/') && (module_table[m][s] == '\0')) {
	equal = true;
	if(debug) Serial.printf("topic equal\r\n");
	break;
      }
    }
  }
  if(equal == true) {
    s++;
    for(i = 0; ((i < ITEM_TOKEN_LENGTH) && (item_topic[s] != '/')); i++, s++) {
      item_type[i] = item_topic[s];
    }
    item_type[i] = '\0';
    s++;
    for(i = 0; ((i < ITEM_TOKEN_LENGTH) && (item_topic[s] != '/')); i++, s++) {
      item_id[i] = item_topic[s];
    }
    item_id[i] = '\0';
    s++;
    for(i = 0; ((i < ITEM_TOKEN_LENGTH) && (item_topic[s] != '/')); i++, s++) {
      item_action[i] = item_topic[s];
    }
    item_action[i] = '\0';

    if(debug) {
      Serial.printf("\r\nmoduleCmd[%d] - item_module = %s, item_type = %s, item_id = %s, item_action = %s, item_payload = %s\r\n",
		    m, item_module, item_type, item_id, item_action, item_payload);
    }
    moduleCmd[m](item_module, item_type, item_id, item_action, item_payload);
    done = true;
  }
  if(done == false) {
    transferLine();
  }
  if(debug) {Serial.printf("\r\n\r\n");}
}

int8_t EFM32COMMClass::getToken(uint8_t* str, uint8_t* item, uint8_t tok_length)
{
  uint8_t i;

  if((str[0] == '\"') && (str[1] == ':') && (str[2] == '\"')) {
    for(i = 3; (i < tok_length) && (str[i] != '\"') && (str[i] != '\0'); i++) {
      item[i-3] = str[i];
    }    
  }
  item[i-3] = '\0';
}

int8_t EFM32COMMClass::add_module(uint8_t* str,
				  void (*cmd)(uint8_t* item_module,
					      uint8_t* item_type, 
					      uint8_t* item_id, 
					      uint8_t* item_action,
					      uint8_t* item_payload))
{
  static uint8_t index = 0;
  if(index < 8) {
    strcpy((char*)module_table[index],(char*)str);
    moduleCmd[index++] = cmd;
    return index;
  } else {
    return -1;
  }
}


void EFM32COMMClass::transferLine(void)
{
  // transfer to other serial port if this isnt end of line
  Serial.printf("{\"ERROR\":\"NO_TRANSFER_VALID\"}\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}

EFM32COMMClass COMM;


