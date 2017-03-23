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
/* Example for how to setup the MQTT client for the MPLA3115A RS232x2 Engimusing board
 *  There are 3 devices on this board. An LED and an MPLA3115A temperature and altitude sensor. 
 *  See http://www.engimusing.com/products/reedsw-1 for more information about the board.
 */

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include "Arduino.h"

#include <MPLA3115A2Device.h>
#include <Wire.h>

MPLA3115A2Device MPLA3115A2;

void setup()
{

  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple HTU21D example 0");
  Serial1.println("Simple HTU21D example 1");

  //Initialize the Humidity sensor
  MPLA3115A2.begin(Wire0, 3);
}


void loop()
{
  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  
  float pressue = MPLA3115A2.readPressure();
  float altitude = MPLA3115A2.readAltitude();
  float temp = MPLA3115A2.readTemp();
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
  

  delay(1000);                       // wait for a second
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  
}
