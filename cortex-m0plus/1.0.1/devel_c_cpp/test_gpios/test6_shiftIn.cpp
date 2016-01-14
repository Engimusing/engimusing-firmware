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

#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test06 - shiftIn() test";

void test06_test(void)
{
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static uint8_t indata[8] = {0,0,0,0,0,0,0,0};
  uint32_t datain = 0;
  static int err_count = 0;
  static int pins[8] = {2,3,4,5,6,7,8,10};

  int idata = 4;
  int sclk = 5;
  int gate = 2;

  Serial.println("shiftIn Test");

  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  digitalWrite(gate,LOW);
  pinMode(gate, OUTPUT);
  digitalWrite(sclk,LOW);
  pinMode(sclk, OUTPUT);
  delayMicroseconds(20);

  for(int w = 0; w < 8; w++) {
    digitalWrite(gate,HIGH);
    delayMicroseconds(10);
    datain = shiftIn(idata,sclk,MSBFIRST);
    indata[w] = datain;
    digitalWrite(gate,LOW);
    delayMicroseconds(50);
  }
  for(int w = 0; w < 8; w++) {
    Serial.print("data = "); Serial.println(indata[w],HEX);
    Serial.print("cdata = "); Serial.println(data[w],HEX);
    if(indata[w] != data[w]) {
      err_count++;
    }
  }
  Serial.print("err_count = "); Serial.println(err_count);
}

void test06_desc(void)
{
  Serial.println("\n\rTest 6 Description:");
  Serial.println("  This tests the shiftIn() function.");
  Serial.println("  It requires a second board to generate the data.");
  Serial.println("  The second board should be started before this board.");
  Serial.println("  The boards are connected with a 1 to 1 cable.");
}

void test06(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test06_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test06");
    test06_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}

