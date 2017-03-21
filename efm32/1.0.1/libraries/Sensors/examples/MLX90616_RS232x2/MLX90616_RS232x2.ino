/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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
/* Example for how to setup the MQTT client for the MLX90616 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MLX90616 IR temperature sensor.
    See http://www.engimusing.com/products/tmp-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <MLX90616Device.h>
#include <Wire.h>

MLX90616Device MLX90616;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple HTU21D example 0");
  Serial1.println("Simple HTU21D example 1");

  MLX90616.begin(Wire0, -1);
}

void loop()
{

  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  
  
  float temp = MLX90616.temperature();
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.println(" C");
  
  Serial1.print("temperature = ");
  Serial1.print(temp);
  Serial1.println(" C");

  delay(1000);                       // wait for a second
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH

}