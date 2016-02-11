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
static String test_help = "test03 - help entry";
extern AnalogLP Analog;

void test03_test(void)
{
  int8_t vddh = 0;

  delay(1000);

  uPvdd vdd = Analog.analogReadVDD();

  Serial.printf("VDD = %d.%dV\r\n", vdd.wholeVDD, vdd.fracVDD);
  Analog.commVDD();

  temperature temp = Analog.analogReadTemp();

  Serial.printf("Temp = %d.%dC (%d.%dF)\r\n", temp.wholeC, temp.fracC, temp.wholeF, temp.fracF);
  Analog.commTemperature();
}

void test03_desc(void)
{
  Serial.println("\n\rTest 03 Description:");
}

void test03(uint8_t function)
{
  switch (function) {
    case TESTHELP:
      Serial.print(test_help);
      break;
    case DESCRIPTION:
      test03_desc();
      break;
    case RUNTEST:
      Serial.println("\n\rRun test03");
      test03_test();
      break;
    default:
      Serial.println("\n\rBad Test Function");
      break;
  }
}

