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
/* Example for how to print out readings from the ADXL362 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a ADXL362 accelerometer.
    See http://www.engimusing.com/products/adxl-4 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

#include <ADXL362Device.h>
#include <SPI.h>

ADXL362Device ADXL362;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple ADXL362 example 0");
  Serial1.println("Simple ADXL362 example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  //Initialize the Accelerometer sensor
  //pins are:
  //  2 - VIO
  //  3 - VS
  //  4 - CS 
  ADXL362.begin(2, 3, 4, &SPI);
}

void loop()
{


  ADXL362.update();

  
  
  if(serialTimer.update())
  { 
    float xData;
    float yData;
    float zData;
    ADXL362.sampleXYZT();
    xData = ADXL362.getXGees();
    yData = ADXL362.getYGees();
    zData = ADXL362.getZGees();

    Serial.print("X = ");
    Serial.print(xData);
    Serial.print(" g Y = ");
    Serial.print(yData);
    Serial.print(" g Z = ");
    Serial.print(zData);
    Serial.println(" g");
  
    Serial1.print("X = ");
    Serial1.print(xData);
    Serial1.print(" g Y = ");
    Serial1.print(yData);
    Serial1.print(" g Z = ");
    Serial1.print(zData);
    Serial1.println(" g");
  
  }
  led.update();
}