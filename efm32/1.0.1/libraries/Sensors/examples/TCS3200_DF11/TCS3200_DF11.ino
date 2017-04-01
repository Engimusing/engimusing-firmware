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
/* Example for how to print out readings from a TCS3200  DF11 board using the ZB USB Engimusing board
   There are 2 devices on this board. An LED and a TCS3200 color sensor.
   See https://www.engimusing.com/collections/sensors/products/tcs3200-3 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <TCS3200Device.h>


TCS3200Device TCS3200;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple TCS3200 example 0");

  
  //sets up the 5 pins needed to setup and communicate with the TCS3200
  TCS3200.begin(2,4,6,8,7);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;
  
  TCS3200.update();
  
  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();
    
    digitalWrite(LED_BUILTIN, on);   // toggle the LED (HIGH is the voltage level)
    
      float red = TCS3200.readColorHertz(TCS3200Device::RED);
      float green = TCS3200.readColorHertz(TCS3200Device::GREEN);
      float blue = TCS3200.readColorHertz(TCS3200Device::BLUE);
      float white = TCS3200.readColorHertz(TCS3200Device::WHITE);
      Serial.print("red = ");
      Serial.print(red);
      Serial.print(" green = ");
      Serial.print(green);
      Serial.print(" blue = ");
      Serial.print(blue);
      Serial.print(" white = ");
      Serial.println(white);
    
    on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  }
}


