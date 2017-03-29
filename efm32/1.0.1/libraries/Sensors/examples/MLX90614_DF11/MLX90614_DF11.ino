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
/* Example for how to print out readings from the MLX90614 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MLX90614 IR temperature sensor.
    See http://www.engimusing.com/products/tmp-3 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <MLX90614Device.h>
#include <Wire.h>

MLX90614Device MLX90614;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple MLX90614 example 0");

  MLX90614.begin(Wire0, 10);
}

void loop()
{

  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  
  
  float temp = MLX90614.temperature();
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.println(" C");
  
  delay(1000);                       // wait for a second
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH

}
