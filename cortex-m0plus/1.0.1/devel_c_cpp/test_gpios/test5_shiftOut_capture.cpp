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
static String test_help = "test05 - shiftOut() data capture";

// shiftIn test:
// (SI DATA) Pin 4 to Pin  8 (US1_TX)
// (US1_CK)  Pin 5 to Pin 10 (SI CLK)

void test05_test(void)
{
  static int pins[8] = {2,3,4,5,6,7,8,10};
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static uint8_t indata[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static int err_count = 0;

  // Read 8 bytes sent from test05 using shiftOut()
  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  for(int w = 0; w < 8; w++) {
    uint8_t sftdata = 0;
    for(int i = 0; i < 8; i++) {
      while(digitalRead(5) == LOW);
      sftdata |= digitalRead(4) << (7-i);
      while(digitalRead(5) == HIGH);
    }
    indata[w] = sftdata;
  }
  for(int w = 0; w < 8; w++) {
    Serial.print("data = "); Serial.println(indata[w],HEX);
    if(indata[w] != data[w]) {
      err_count++;
    }
  }
  Serial.print("err_count = "); Serial.println(err_count);
}

void test05_desc(void)
{
  Serial.println("\n\rTest 5 Description:");
  Serial.println("  Companion to Test 4 - Run this one first then Test 4.");
  Serial.println("  This runs on a second board and captures the data");
  Serial.println("  sent by shiftOut() on the first board.");
  Serial.println("  The two boards are connected with a 1 to 1 cable");
}

void test05(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test05_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test05");
    test05_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}

