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
/* Example for how to print out readings from the DualCT101530 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualCT101530 Dual Reed Switches.
    See https://www.engimusing.com/products/reedsw-1 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <CT101530Device.h>


CT101530Device ReedSwitch0;
DevicePrinter ReedSwitch0Printer0;
DevicePrinter ReedSwitch0Printer1;
CT101530Device ReedSwitch1;
DevicePrinter ReedSwitch1Printer0;
DevicePrinter ReedSwitch1Printer1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple DualCT101530 example 0");
  Serial1.println("Simple DualCT101530 example 1");
  led.begin(1000);
 
  ReedSwitch0Printer0.begin(Serial, ReedSwitch0, 5000, "ReedSwitch0");
  ReedSwitch0Printer1.begin(Serial1, ReedSwitch0, 5000, "ReedSwitch0");
  ReedSwitch1Printer0.begin(Serial, ReedSwitch1, 5000, "ReedSwitch1");
  ReedSwitch1Printer1.begin(Serial1, ReedSwitch1, 5000, "ReedSwitch1");
  
  ReedSwitch0.begin(6,-1,50);
  ReedSwitch1.begin(7,-1,50);
}

void loop()
{


  ReedSwitch0.update();
  ReedSwitch1.update();

  ReedSwitch0Printer0.update();
  ReedSwitch0Printer1.update();
  ReedSwitch1Printer0.update();
  ReedSwitch1Printer1.update();
  
  
  led.update();
}