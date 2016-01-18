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

static String test_help = "test01 - ADC Test varying references";
extern AnalogLP Analog;

void test01_test(void)
{
  uint32_t sample = 0;

  while(1) {
    delay(1000);
    Analog.analogReference(DEFAULT);
    sample = Analog.analogRead(3);
    Serial.print("sample VDD   = "); Serial.println(sample,HEX);

    delay(1000);
    Analog.analogReference(INTERNAL2V5);
    sample = Analog.analogRead(3);
    Serial.print("sample 2.5V  = "); Serial.println(sample,HEX);

    delay(1000);
    Analog.analogReference(INTERNAL1V25);
    sample = Analog.analogRead(3);
    Serial.print("sample 1.25V = "); Serial.println(sample,HEX);
    Serial.println();
  }
}

void test01_desc(void)
{
  Serial.println("\n\rTest 01 Description:");
  Serial.println("  Read from ADC once per second in single mode");
  Serial.println("  Vary reference through the 3 internal options.");
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

