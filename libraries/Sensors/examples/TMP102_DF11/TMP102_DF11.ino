/*
  Copyright (c) 2016-2018 Engimusing LLC.  All right reserved.
  
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
/* Example for how to print out readings from the TMP102  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a TMP102 temperature sensor.
    See https://www.engimusing.com/products/tmp102-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <TMP102Device.h>
#include <Wire.h>
TMP102Device TMP102;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  led.begin(1000);
  serialTimer.begin(1000,true);
  Serial.println("Simple TMP102 example 0");
  
  TMP102.begin(Wire0, 5, true);
  
}

void loop()
{
  TMP102.update();

  if(serialTimer.update())
  { 
    float temp = TMP102.temperature();
    Serial.print("temperature = ");
    Serial.println(temp);
  }
  led.update();
}