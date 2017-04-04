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
/* Example for how to print out readings from the TCS34725  DF11 board using the ZB USB Engimusing board
    There are 2 devices on this board. An LED and a TCS34725 color sensor.
    See https://www.engimusing.com/products/tcs3472-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <TCS34725Device.h>
#include <Wire.h>

TCS34725Device TCS34725;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple TCS34725 example 0");

  
  TCS34725.begin(Wire0, 5, TCS34725_INTEGRATIONTIME_700MS);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;

  TCS34725.update();

  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();

    digitalWrite(LED_BUILTIN, on);   // toggle the LED (HIGH is the voltage level)
    
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

    on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  }
}