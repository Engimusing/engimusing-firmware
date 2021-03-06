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
/* Example for how to print out readings from the TCS34725 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a TCS34725 color sensor.
    See https://www.engimusing.com/products/tcs3472-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <TCS34725Device.h>
#include <Wire.h>

TCS34725Device TCS34725;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple TCS34725 example 0");
  Serial1.println("Simple TCS34725 example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
  TCS34725.begin(Wire0, 7, TCS34725_INTEGRATIONTIME_700MS);
}

void loop()
{


  TCS34725.update();

  
  
  if(serialTimer.update())
  { 
    uint16_t r = 0;
    uint16_t g = 0;
    uint16_t b = 0;
    uint16_t c = 0;
    TCS34725.sampleData();
    TCS34725.getRawData(r,g,b,c);
    float colorTemp = TCS34725.calculateColorTemperature(r,g,b);
    float lux = TCS34725.calculateLux(r,g,b);

    Serial.print("red = ");
    Serial.print(r);
    Serial.print(" green = ");
    Serial.print(g);
    Serial.print(" blue = ");
    Serial.print(b);
    Serial.print(" clear = ");
    Serial.println(c);
    Serial.print(" color temperature = ");
    Serial.print(colorTemp);
    Serial.print(" luminance = ");
    Serial.println(lux);
  
    Serial1.print("red = ");
    Serial1.print(r);
    Serial1.print(" green = ");
    Serial1.print(g);
    Serial1.print(" blue = ");
    Serial1.print(b);
    Serial1.print(" clear = ");
    Serial1.println(c);
    Serial1.print(" color temperature = ");
    Serial1.print(colorTemp);
    Serial1.print(" luminance = ");
    Serial1.println(lux);
  
  }
  led.update();
}