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
/* Example for how to print out readings from the ADXL362 RS232x2 Engimusing board
 *  There are 2 devices on this board. An LED and an ADXL362 Accelerometer. 
 *  See http://www.engimusing.com/products/adxl-4 for more information about the board.
 */

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif
 
#include "Arduino.h"

#include <ADXL362Device.h>

#include <SPI.h>


ADXL362Device ADXL362;


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple ADXL362 example 0");
  Serial1.println("Simple ADXL362 example 1");

  int accel_VIO = 2;
  int accel_VS = 3;
  int accel_CS = 4;
  
  //Initialize the Accelerometer sensor
  ADXL362.begin(accel_VIO, accel_VS, accel_CS, &SPI);
}

void loop()
{
  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)

  float xData;
  float yData;
  float zData;
  float temperature;
  ADXL362.sampleXYZT();
  xData = ADXL362.getXGees();
  yData = ADXL362.getYGees();
  zData = ADXL362.getZGees();
  temperature = ADXL362.getTCelsius();
  
  Serial.print("X = ");
  Serial.print(xData);
  Serial.print(" g Y = ");
  Serial.print(yData);
  Serial.print(" g Z = ");
  Serial.print(zData);
  Serial.print(" g temperature = ");
  Serial.print(temperature);
  Serial.println(" C");
  
  Serial1.print("X = ");
  Serial1.print(xData);
  Serial1.print(" g Y = ");
  Serial1.print(yData);
  Serial1.print(" g Z = ");
  Serial1.print(zData);
  Serial1.print(" g temperature = ");
  Serial1.print(temperature);
  Serial1.println(" C");
  
  delay(1000);
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}