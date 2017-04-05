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
    See https://www.engimusing.com/products/irtemp-1 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <MLX90614Device.h>
#include <Wire.h>

MLX90614Device MLX90614;

void setup()
{
Serial.begin(115200);
Serial1.begin(115200);

pinMode(LED_BUILTIN, OUTPUT);
Serial.println("Simple MLX90614 example 0");
Serial1.println("Simple MLX90614 example 1");


MLX90614.begin(Wire0, -1);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

static int on = HIGH;

MLX90614.update();

if(millis() - lastMillis > printDelay)
{
lastMillis = millis();

digitalWrite(LED_BUILTIN, on); // toggle the LED (HIGH is the voltage level)

  float temp = MLX90614.temperature();
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.println(" C");
  

  Serial1.print("temperature = ");
  Serial1.print(temp);
  Serial1.println(" C");

on = (on) ? LOW : HIGH; // on alternates between LOW and HIGH
}
}