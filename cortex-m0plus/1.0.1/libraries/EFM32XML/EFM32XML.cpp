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

#include "EFM32XML.h"
#include <Arduino.h>

extern LEUARTClass Serial;
extern boardIO IO;

static uint8_t isCnt = 0;
static uint8_t charCnt = 0;



EFM32XMLClass::EFM32XMLClass()
{
}

void EFM32XMLClass::begin(void)
{
  Serial.printf("xml setup\r\n");
}


void EFM32XMLClass::decode(void)
{
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

int8_t EFM32XMLClass::parse(uint8_t* s, uint8_t cnt, char c)
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

int8_t EFM32XMLClass::substrcmp(uint8_t* str, uint8_t* sub, uint8_t start)
{
  uint8_t debug = 0;

  uint8_t len = strlen((char*)sub);
  char tmp[len];


  memcpy(tmp, &str[start], len);
  tmp[len] = '\0';

  if(debug) {
    uint8_t lent = strlen((char*)tmp);
    Serial.printf("substrcmp - len= %d  tmp= %s  sub= %s lent = %d\r\n",len,tmp,sub,lent);
    if(strcmp((char*)sub, (char*)tmp)) {
      Serial.printf("substrcmp debug - not equal\r\n");
    } else {
      Serial.printf("substrcmp debug - equal\r\n");
    }
  }

  return strcmp((char*)sub, (char*)tmp);
}

void EFM32XMLClass::addCharToInputString(char c)
{
  inputString[isCnt++] = c;
  if(isCnt >= XMLSTRING_LENGTH) {
    isCnt = 0;
    //    state = Idle;
  }
}

void EFM32XMLClass::getInputString(char c)
{
  static uint8_t devS[]   = "<DEV";
  static uint8_t devE[]   = "</DEV>";

  enum giState {
    Idle,
    gettingLine,
  };

  static giState state = Idle;

  int8_t r = 0;

  if(state == Idle) {
    r = parse(devS, charCnt++, c);
    if(r < 0) {
      isCnt = 0;
      charCnt = 0;
    } else if(r > 0) {
      addCharToInputString(c);
      state = gettingLine;
    } else {
      addCharToInputString(c);
    }
  } else {
    r = parse(devE, charCnt++, c);
    if(r < 0) {
      charCnt = 0;
      addCharToInputString(c);
    } else if(r > 0) {
      state = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
      decodeAddress();
    } else {
      addCharToInputString(c);
    }
  }
}


// Test Strings:
// must change cpuid to match actual CPU you are using for test

// 01234567890123456789012345678901234567890123
// <DEV><TYPE>val</TYPE><ACT>val</ACT></DEV>     debug #1
// <DEVcpuid="24353a02522fa331"></DEV>           debug #2
// <DEVcpuid="24353a02522fa332"></DEV>           debug #3
// <DEVcpuid"24353a02522fa332"></DEV>            debug #4
// <DEVcpuid=%24353a02522fa332"></DEV>           debug #5
// <DEVcpuid="24353a02522fa331"addx="01"></DEV>  debug #6
// <DEVcpuid="24353a02522fa331"addr="01%></DEV>  debug #7
// <DEVcpuid="24353a02522fa331"addr="01"></DEV>  debug #8
// <DEVadr="01"><TYPE>val</TYPE></DEV>           debug #9
// <DEVaddr="01^><TYPE>val</TYPE></DEV>          debug #10
// <DEVaddr="02"><TYPE>val</TYPE></DEV>          debug #11
// <DEVaddr="01"><TYPE>val</TYPE></DEV>          debug #12

void EFM32XMLClass::decodeAddress(void)
{
  static uint8_t debug = 0;

  uint8_t cpuidS[] = "cpuid=";
  uint8_t adrS[]   = "addr=";
  int8_t r = 0;
  uint8_t *cid;
  uint8_t *myid;
  static uint8_t myAddr[] = "00";

  if(debug) {
    Serial.printf("\r\n\r\n----%d----decodeAddress - inputString1 = %s\r\n",debug,inputString);
    debug++;
  }
  switch(inputString[4]) {
  case '>': // belongs to this module
    if(debug) {Serial.printf("debug #1 - belongs to this module - no attributes\r\n");}
    parseLine();
    break;
  case 'c': // test for cpuid attribute matching this module
    if(substrcmp(inputString, cpuidS, 4)) {
      if(debug) {Serial.printf("debug #4 - cpuid= - spelled wrong\r\n");}
      invalidCPUid();
      return;
    }
    if((inputString[10] != '"') || (inputString[27] != '"')) {
      if(debug) {Serial.printf("debug #5 - no double quote found\r\n");}
      invalidCPUid();
      return;
    }
    myid = (uint8_t*)IO.getChipID();
    if(debug) {Serial.printf("myid = %s\r\n",myid);}

    if(substrcmp(inputString, myid, 11)) { // another DEVs address
      if(debug) {Serial.printf("debug #3 - Another devices address\r\n");}
      transferLine();
      return;
    }
    if(inputString[28] == '>') {
      if(debug) {Serial.printf("debug #2 - address equal but no addr attribute\r\n");}
      Serial.printf("\r\n");
      parseLine();
      return;
    }
    if(substrcmp(inputString, adrS, 28)) {
      if(debug) {Serial.printf("debug #6 - addr= spelled wrong\r\n");}
      invalidAddr();
      return;
    }
    if((inputString[33] != '"') || (inputString[36] != '"')) {
      if(debug) {Serial.printf("debug #7 - no double quote found\r\n");}
      invalidAddr();
      return;
    }
    myAddr[0] = inputString[34];
    myAddr[1] = inputString[35];
    if(debug) {Serial.printf("debug #8 - myAddr %s stored\r\n",myAddr);}
    parseLine();

    break;

  case 'a': // test for address attribute matching this module

    if(substrcmp(inputString, adrS, 4)) {
      if(debug) {Serial.printf("debug #9 - addr= - spelled wrong\r\n");}
      invalidAddr();
      return;
    }
    if((inputString[9] != '"') || (inputString[12] != '"')) {
      if(debug) {Serial.printf("debug #10 - no double quote found\r\n");}
      invalidAddr();
      return;
    }
    if(substrcmp(inputString, myAddr, 10)) { // another DEVs address
      if(debug) {Serial.printf("debug #11 - Another devices address\r\n");}
      transferLine();
      return;
    } else {
      if(debug) {Serial.printf("debug #12 - address matches\r\n");}
      parseLine();
    }
    break;
  default: // belongs to another device
    transferLine();
    break;
  }
}


// Test Strings:
// must change cpuid to match actual CPU you are using for test

// 01234567890123456789012345678901234567890123
// <DEV><TYPE>val</TYPE><ACT>val</ACT></DEV>     debug #1
// <DEVcpuid="24353a02522fa331"></DEV>           debug #2
// <DEVcpuid="24353a02522fa331"addr="01"></DEV>  debug #3
// <DEVaddr="01"><TYPE>val</TYPE></DEV>          debug #4
void EFM32XMLClass::parseLine(void)
{
  uint8_t modS[]  = "<MOD>";
  uint8_t modE[]  = "</MOD>";
  uint8_t typeS[]  = "<TYPE>";
  uint8_t typeE[]  = "</TYPE>";
  uint8_t idS[]    = "<ID>";
  uint8_t idE[]    = "</ID>";
  uint8_t actS[]   = "<ACT>";
  uint8_t actE[]   = "</ACT>";

  uint8_t p1S[]   = "<PARAM1>";
  uint8_t p1E[]   = "</PARAM1>";
  uint8_t p2S[]   = "<PARAM2>";
  uint8_t p2E[]   = "</PARAM2>";

  static uint8_t item_module[ITEM_TOKEN_LENGTH];
  static uint8_t item_type[ITEM_TOKEN_LENGTH];
  static uint8_t item_id[ITEM_TOKEN_LENGTH];
  static uint8_t item_action[ITEM_TOKEN_LENGTH];
  static uint8_t item_p1[ITEM_TOKEN_LENGTH];
  static uint8_t item_p2[ITEM_TOKEN_LENGTH];

  static uint8_t debug = 0;
  int i = 0;
  isCnt = 0;

  // trim off <DEV...> and </DEV> tags
  for(i = 0; i < XMLSTRING_LENGTH; i++) {
    if(inputString[i] == '>') break;
  }
  for(i++; (i < XMLSTRING_LENGTH) && inputString[i]; i++) {
    inputString[isCnt++] = inputString[i];
  }
  if(isCnt < 8) {
    if(debug) {Serial.printf("no elements to parse\r\n");}
    return;
  }
  inputString[isCnt-8] = '\r';
  inputString[isCnt-7] = '\n';
  inputString[isCnt-6] = '\0';
  if(debug) {Serial.printf("\r\nparseLine trimmed inputString = %s\r\n", inputString);}

  uint8_t len = isCnt - 8;
  isCnt = 0;

  uint8_t last = 0;
  while(isCnt < len) {
    last = isCnt;

    getToken(modS, modE, item_module);
    getToken(typeS, typeE, item_type);
    getToken(idS, idE, item_id);
    getToken(actS, actE, item_action);
    getToken(p1S, p1E, item_p1);
    getToken(p2S, p2E, item_p2);

    if(debug) {Serial.printf("item_module = %s\r\n",item_module);}
    if(debug) {Serial.printf("item_type   = %s\r\n",item_type);}
    if(debug) {Serial.printf("item_id     = %s\r\n",item_id);}
    if(debug) {Serial.printf("item_act    = %s\r\n",item_action);}
    if(debug) {Serial.printf("item_p1     = %s\r\n",item_p1);}
    if(debug) {Serial.printf("item_p2     = %s\r\n",item_p2);}
  }
  execute_cmd(item_module, item_type, item_id, item_action, item_p1, item_p2);
  inputString[0] = '\0';
  item_module[0] = '\0';
  item_type[0] = '\0';
  item_id[0] = '\0';
  item_action[0] = '\0';
  item_p1[0] = '\0';
  item_p2[0] = '\0';
  isCnt = 0;
}

static uint8_t module_table[8][16] = {'\0'};
static void (*moduleCmd[16])(uint8_t* item_type, 
			     uint8_t* item_id, 
			     uint8_t* item_action,
			     uint8_t* item_p1,
			     uint8_t* item_p2);

void EFM32XMLClass::execute_cmd(uint8_t* item_module, 
				uint8_t* item_type, 
				uint8_t* item_id, 
				uint8_t* item_action,
				uint8_t* item_p1,
				uint8_t* item_p2
				)
{
  uint8_t debug = 0;

  if(debug) {Serial.printf("execute_cmd - item_module = %s\r\n",item_module);}
  for(int i = 0; (i < 8) && module_table[i][0]; i++) {
    if(debug) {Serial.printf("m[%d] = %s\r\n",i,module_table[i]);}
    if(strcmp((char*)item_module, (char*)module_table[i]) == 0) {
      if(debug) {Serial.printf("equal\r\n");}
      moduleCmd[i](item_type, item_id, item_action, item_p1, item_p2);
      return;
    }
  }
  Serial.printf("<ERR><MOD>%s</MOD></ERR>\r\n",item_module);
}

int8_t EFM32XMLClass::add_module(uint8_t* str,
				 void (*cmd)(uint8_t* item_type, 
					     uint8_t* item_id, 
					     uint8_t* item_action,
					     uint8_t* item_p1,
					     uint8_t* item_p2))
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

// 012345678901234567890123456789
// <TYPE>val</TYPE><ACT>val</ACT>

int8_t EFM32XMLClass::getToken(uint8_t* tokS, uint8_t* tokE, uint8_t* item)
{
  int i;

  if(substrcmp(inputString, tokS, isCnt) == 0) {
    isCnt += strlen((char*)tokS);
    for(i = 0; (i < ITEM_TOKEN_LENGTH) && (inputString[isCnt] != '<'); i++) {
      item[i] = inputString[isCnt++];
    }
    item[i] = '\0';
    if(substrcmp(inputString, tokE, isCnt) == 0) {
      isCnt += strlen((char*)tokE);
      return 1;
    }
    return 0;
  }
}


void EFM32XMLClass::transferLine(void)
{
  // transfer to other serial port if this isnt end of line
  Serial.printf("\r\n<ERROR>INVALID ADDRESS</ERROR>\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}

void EFM32XMLClass::invalidCPUid(void)
{
  Serial.printf("\r\n<ERROR>INVALID CPUID</ERROR>\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}

void EFM32XMLClass::invalidAddr(void)
{
  Serial.printf("\r\n<ERROR>INVALID ADDR</ERROR>\r\n");
  inputString[0] = '\0';
  isCnt = 0;
}


EFM32XMLClass XML;


