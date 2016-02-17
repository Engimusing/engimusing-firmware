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
#include <Arduino.h>

extern LEUARTClass Serial;
extern boardIO IO;

static uint8_t isCnt = 0;
static uint8_t charCnt = 0;

enum giState {
  Idle,
  gettingLine,
};

static giState state = Idle;

static uint8_t module_table[MODULE_TABLE_ENTRIES][MODULE_STRING_LENGTH] = {'\0'};

static void (*moduleCmd[MODULE_TABLE_ENTRIES])(uint8_t* item_type, 
					       uint8_t* item_id, 
					       uint8_t* item_action,
					       uint8_t* item_payload);

EFM32COMMClass::EFM32COMMClass()
{
}

void EFM32COMMClass::begin(void)
{
}


void EFM32COMMClass::decode(void)
{
  if (Serial.available()) {
    char c = (char)Serial.read(); // get the new byte:
    if(isgraph(c)) {
      Serial.print(c);
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

  if(state == Idle) {
    if(c == '{') {
      state = gettingLine;
    }
    addCharToInputString(c);
  } else {
    if(c == '}') {
      state = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
      parseLine();
    } else {
      addCharToInputString(c);
    }
  }
}

void EFM32COMMClass::addCharToInputString(char c)
{
  inputString[isCnt++] = c;
  if(isCnt >= COMM_STRING_LENGTH) {
    isCnt = 0;
    state = Idle;
  }
}


int8_t EFM32COMMClass::parse(uint8_t* s, uint8_t cnt, char c)
{
  if((c == s[cnt]) && (s[cnt+1] == 0)) {
    charCnt = 0;
    return 1;   // parse equal to string
  } else if((c != s[cnt]) || (s[cnt] == 0)) {
    charCnt = 0;
    return -1;  // parse failed
  } else {
    return 0;   // parse incomplete
  }
}



// Test Strings:
// must change cpuid to match actual CPU you are using for test

// 01234567890123456789012345678901234567890123
// {"TYPE":"val","ACT":"val"}                debug #1
// {"CPUID":"24353a02522fa331"}              debug #2
// {"CPUID":"24353a02522fa331","ADDR":"01"}  debug #3
// {"ADDR":"01","TYPE":"val"}                debug #4

// {"ACT":"Action","ADR":"Address","CID":"CPU ID","IID":"Item ID","MOD":"Module","PM1":"Param1","PM2":"Param2","TYP":"Type"}
void EFM32COMMClass::parseLine(void)
{
  // MQTT items
  static uint8_t item_topic[ITEM_TOPIC_LENGTH];
  static uint8_t item_payload[ITEM_PAYLOAD_LENGTH];
  // JSON items
  static uint8_t item_action[ITEM_TOKEN_LENGTH];
  static uint8_t item_addr[ITEM_TOKEN_LENGTH];
  static uint8_t item_cpuid[ITEM_TOKEN_LENGTH];
  static uint8_t item_id[ITEM_TOKEN_LENGTH];
  static uint8_t item_module[ITEM_TOKEN_LENGTH];
  static uint8_t item_type[ITEM_TOKEN_LENGTH];
  uint8_t *myid;
  static uint8_t myAddr[] = "00";

  static uint8_t debug = 1;

  myid = (uint8_t*)IO.getChipID();
  //if(debug) {Serial.printf("myid = %s\r\n",myid);}
  if(debug) {Serial.printf("\r\n\r\n",myid);}

  for(isCnt = 0; inputString[isCnt] != '\0'; isCnt++) {
    uint8_t* c = &inputString[isCnt];

    if( (c[0] == '{') || (c[0] == ',') && (c[1] == '\"')) {
      if((c[2] == 'A') && (c[3] == 'C') && (c[4] == 'T')) {
	getToken(&c[5], item_action, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("ACT = %s\r\n", item_action);}
      }
      if((c[2] == 'A') && (c[3] == 'D') && (c[4] == 'R')) {
	getToken(&c[5], item_addr, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("ADR = %s\r\n", item_addr);}
      }
      if((c[2] == 'C') && (c[3] == 'I') && (c[4] == 'D')) {
	getToken(&c[5], item_cpuid, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("CID = %s\r\n", item_cpuid);}
      }
      if((c[2] == 'I') && (c[3] == 'I') && (c[4] == 'D')) {
	getToken(&c[5], item_id, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("IID = %s\r\n", item_id);}
      }
      if((c[2] == 'M') && (c[3] == 'O') && (c[4] == 'D')) {
	getToken(&c[5], item_module, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("MOD = %s\r\n", item_module);}
      }
      if((c[2] == 'T') && (c[3] == 'Y') && (c[4] == 'P')) {
	getToken(&c[5], item_type, ITEM_TOKEN_LENGTH);
	if(debug) {Serial.printf("TYP = %s\r\n", item_type);}
      }
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	getToken(&c[5], item_topic, ITEM_TOPIC_LENGTH);
	if(debug) {Serial.printf("TOP = %s\r\n", item_topic);}
      }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	getToken(&c[5], item_payload, ITEM_PAYLOAD_LENGTH);
	if(debug) {Serial.printf("PLD = %s\r\n", item_payload);}
      }
    }
  }
  int cpuid_equal = (strcmp((char*)myid, (char*)item_cpuid) == 0) ? 1 : 0;
  int addr_equal = (strcmp((char*)myAddr, (char*)item_addr) == 0) ? 1 : 0;
  int cpuid_length = strlen((char*)item_cpuid);
  int addr_length = strlen((char*)item_addr);
  int topic_length = strlen((char*)item_topic);

  if(debug) {Serial.printf("cpuid_equal = %d addr_equal = %d cpuid_length = %d addr_length = %d\r\n",
			   cpuid_equal, addr_equal, cpuid_length, addr_length);}

  if((cpuid_length == 16) && cpuid_equal && (addr_length == 2)) {
    myAddr[0] = item_addr[0];
    myAddr[1] = item_addr[1];
    addr_equal = 1;
  }

  uint8_t i, m, s;
  uint8_t done = false;
  uint8_t equal = false;

  if(cpuid_equal || addr_equal) {
    execute_cmd(item_module, item_type, item_id, item_action, item_payload);
    done = true;
  }
  if(topic_length) {
    for(m = 0; (m < MODULE_TABLE_ENTRIES) && module_table[m][0]; m++) {
      if(debug) Serial.printf("module_table[%d] = %s\r\n",m,module_table[m]);
      for(s = 0; s < MODULE_STRING_LENGTH; s++) {
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
      Serial.printf("\r\nmoduleCmd[%d] - item_type = %s, item_id = %s, item_action = %s, item_payload = %s\r\n",
		    m, item_type, item_id, item_action, item_payload);
    }
    moduleCmd[m](item_type, item_id, item_action, item_payload);
    done = true;
  }
  if(done == false) {
    transferLine();
  }
  inputString[0]  = '\0';
  item_topic[0]   = '\0';
  item_payload[0] = '\0';
  item_module[0]  = '\0';
  item_type[0]    = '\0';
  item_id[0]      = '\0';
  item_action[0]  = '\0';
  isCnt = 0;
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

void EFM32COMMClass::execute_cmd(uint8_t* item_module, 
				 uint8_t* item_type, 
				 uint8_t* item_id, 
				 uint8_t* item_action,
				 uint8_t* item_payload
				 )
{
  uint8_t debug = 1;

  if(debug) {Serial.printf("execute_cmd - item_module = %s\r\n",item_module);}
  for(int i = 0; (i < MODULE_TABLE_ENTRIES) && module_table[i][0]; i++) {
    if(debug) {Serial.printf("m[%d] = %s\r\n",i,module_table[i]);}
    if(strcmp((char*)item_module, (char*)module_table[i]) == 0) {
      if(debug) {Serial.printf("equal\r\n");}
      moduleCmd[i](item_type, item_id, item_action, item_payload);
      return;
    }
  }
  Serial.printf("{\"ERROR\":\"INVALID_MODULE_%s\"}\r\n",item_module);
}

int8_t EFM32COMMClass::add_module(uint8_t* str,
				  void (*cmd)(uint8_t* item_type, 
					      uint8_t* item_id, 
					      uint8_t* item_action,
					      uint8_t* item_payload))
{
  static uint8_t index = 0;
  if(index < 8) {
    strcpy((char*)module_table[index],(char*)str);
    moduleCmd[index++] = cmd;
    return 1;
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

void EFM32COMMClass::invalidCPUid(void)
{
  Serial.printf("{\"ERROR\":\"INVALID_CPUID\"}\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}

void EFM32COMMClass::invalidAddr(void)
{
  Serial.printf("{\"ERROR\":\"INVALID_ADDRESS\"}\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}

EFM32COMMClass COMM;


