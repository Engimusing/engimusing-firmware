/*
  Copyright (c) 2016-2017 Engimusing LLC.  All right reserved.
  
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
/* Example for how to print out readings from the TMP102 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a TMP102 temperature sensor.
    See https://www.engimusing.com/products/tmp-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <TMP102Device.h>
#include <Wire.h>

TMP102Device TMP102;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple TMP102 example 0");
  Serial.println("Simple TMP102 example 1");

  
  TMP102.begin(Wire0, -1, true);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;

  TMP102.update();

  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();

    digitalWrite(LED_BUILTIN, on); // toggle the LED (HIGH is the voltage level)
    
  float temp = TMP102.temperature();
  Serial.print("temperature = ");
  Serial.println(temp);

    
  Serial1.print("temperature = ");
  Serial1.println(temp);

    on = (on) ? LOW : HIGH; // on alternates between LOW and HIGH
  }
}