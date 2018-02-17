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
/* Example for how to print out readings from the TCS3200 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a TCS3200 color sensor.
    See https://www.engimusing.com/collections/sensors/products/tcs3200-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <TCS3200Device.h>


TCS3200Device TCS3200;
DevicePrinter TCS3200Printer0;
DevicePrinter TCS3200Printer1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple TCS3200 example 0");
  Serial1.println("Simple TCS3200 example 1");
  led.begin(1000);
 
  TCS3200Printer0.begin(Serial, TCS3200, 5000, "TCS3200");
  TCS3200Printer1.begin(Serial1, TCS3200, 5000, "TCS3200");
  
  //sets up the 5 pins needed to setup and communicate with the TCS3200
  TCS3200.begin(3,2,6,7,8);
}

void loop()
{


  TCS3200.update();

  TCS3200Printer0.update();
  TCS3200Printer1.update();
  
  
  led.update();
}