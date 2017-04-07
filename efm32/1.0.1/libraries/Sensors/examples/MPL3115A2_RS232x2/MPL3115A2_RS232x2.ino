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
/* Example for how to print out readings from the MPL3115A2 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MPL3115A2 temperature and altitude sensor.
    See https://www.engimusing.com/products/mql3-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <MPL3115A2Device.h>
#include <Wire.h>

MPL3115A2Device MPL3115A2;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.println("Simple MPL3115A2 example 0");
  Serial1.println("Simple MPL3115A2 example 1");

  
  MPL3115A2.begin(Wire0, 3);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;

  MPL3115A2.update();

  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();

    digitalWrite(LED_BUILTIN, on); // toggle the LED (HIGH is the voltage level)
    
    float pressue = MPL3115A2.readPressure();
    float altitude = MPL3115A2.readAltitude();
    float temp = MPL3115A2.readTemp();
    Serial.print("Pressure = ");
    Serial.print(pressue);
    Serial.print(" Pa Altitude = ");
    Serial.print(altitude);
    Serial.print(" M temperature = ");
    Serial.print(temp);
    Serial.println(" C");
    
    Serial1.print("Pressure = ");
    Serial1.print(pressue);
    Serial1.print(" Pa Altitude = ");
    Serial1.print(altitude);
    Serial1.print(" M temperature = ");
    Serial1.print(temp);
    Serial1.println(" C");

    on = (on) ? LOW : HIGH; // on alternates between LOW and HIGH
  }
}