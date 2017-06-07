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
/* Example for how to print out readings from the MPU9150 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MPU9150 9-axis Motion Tracker.
    See https://www.engimusing.com for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <MPU9150Device.h>
#include <Wire.h>

MPU9150Device MPU9150;
DevicePrinter MPU9150Printer0;
DevicePrinter MPU9150Printer1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple MPU9150 example 0");
  Serial1.println("Simple MPU9150 example 1");
  led.begin(1000);
 
  MPU9150Printer0.begin(Serial, MPU9150, 5000, "MPU9150");
  MPU9150Printer1.begin(Serial1, MPU9150, 5000, "MPU9150");
  
  MPU9150.begin(Wire0, 3, 6);
}

void loop()
{


  MPU9150.update();

  MPU9150Printer0.update();
  MPU9150Printer1.update();
  led.update();
}