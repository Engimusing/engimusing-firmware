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
/* Example for how to print out readings from the MPL115A1 DF11 board using the ZB USB Engimusing board
 *  There are 2 devices using these combinations of boards. An LED and a MPL115A1 pressure/temperature sensor. 
 *  See http://www.engimusing.com/products/tmp-1 for more information about the board.
 */


#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif
 
#include <MPL115A1Device.h>
#include <SPI.h>

MPL115A1Device MPL115A1;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple MPL115A1 example 0");
  Serial1.println("Simple MPL115A1 example 1");

  MPL115A1.begin(10, 6, 4, SPI);
}


void loop()
{

  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  
  
  float temp = MPL115A1.calculateTemperatureC();
  float pressure = MPL115A1.calculatePressurekPa();
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.print(" C    Pressure = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial1.print("temperature = ");
  Serial1.print(temp);
  Serial1.print(" C    Pressure = ");
  Serial1.print(pressure);
  Serial1.println(" kPa");

  delay(1000);                       // wait for a second
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  
}
