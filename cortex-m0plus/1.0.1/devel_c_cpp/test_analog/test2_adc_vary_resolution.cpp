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
static String test_help = "test02 - ADC Test varying resolutions";
extern AnalogLP Analog;

void test02_test(void)
{
  uint32_t sample = 0;

  while(1) {
    delay(1000);
    Analog.analogReadResolution(6);
    sample = Analog.analogRead(3);
    Serial.print("sample  6 bits = "); Serial.println(sample,HEX);

    delay(1000);
    Analog.analogReadResolution(8);
    sample = Analog.analogRead(3);
    Serial.print("sample  8 bits = "); Serial.println(sample,HEX);

    delay(1000);
    Analog.analogReadResolution(12);
    sample = Analog.analogRead(3);
    Serial.print("sample 12 bits = "); Serial.println(sample,HEX);

    delay(1000);
    Analog.analogReadResolution(16);
    sample = Analog.analogRead(3);
    Serial.print("sample 16 bits = "); Serial.println(sample,HEX);
    Serial.println();
  }
}

void test02_desc(void)
{
  Serial.println("\n\rTest 02 Description:");
  Serial.println("  Read from ADC once per second in single mode");
  Serial.println("  Vary resolution through the 4 basic options.");
}

void test02(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test02_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test02");
    test02_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}

