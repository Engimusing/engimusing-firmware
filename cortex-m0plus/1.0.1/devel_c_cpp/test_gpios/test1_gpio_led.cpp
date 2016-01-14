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
static String test_help = "test01 - GPIO LED Test";

#define PINS_TO_TEST    8
#define TEST_ITERATIONS 4
#define LED_DELAY  200

void test01_test(void)
{
  static int pins[8] = {2,4,6,3,5,7,8,10};

  for(int p = 0; p < PINS_TO_TEST; p++) {
    pinMode(pins[p], OUTPUT);
    digitalWrite(pins[p], HIGH);
  }

  for(int i = 0; i < TEST_ITERATIONS; i++) {
    for(int p = 0; p < PINS_TO_TEST; p++) {
      digitalWrite(pins[p], LOW);
      delay(LED_DELAY);
      digitalWrite(pins[p], HIGH);
      delay(LED_DELAY);
    }
  }
  Serial.println("  Test Complete");
}

void test01_desc(void)
{
  Serial.println("\n\rTest 01 Description:");
  Serial.println("  This test is used to test that the 8");
  Serial.println("  connector pins can be driven.");
  Serial.println("  The DF11_10H_to_DF11_10R_X2 LED ");
  Serial.println("  logic analyzer board is used to");
  Serial.println("  visually watch the LEDs go through");
  Serial.println("  a test pattern.");
}

void test01(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test01_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test01");
    test01_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}

