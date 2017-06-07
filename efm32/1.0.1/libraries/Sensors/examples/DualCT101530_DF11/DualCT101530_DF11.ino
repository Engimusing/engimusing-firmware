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
/* Example for how to print out readings from the DualCT101530  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a DualCT101530 Dual Reed Switches.
    See https://www.engimusing.com/products/reedsw-2 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <CT101530Device.h>

CT101530Device ReedSwitch0;
DevicePrinter ReedSwitch0Printer;
CT101530Device ReedSwitch1;
DevicePrinter ReedSwitch1Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  ReedSwitch0Printer.begin(Serial, ReedSwitch0, 5000, "ReedSwitch0");
  ReedSwitch1Printer.begin(Serial, ReedSwitch1, 5000, "ReedSwitch1");
  Serial.println("Simple DualCT101530 example 0");
  
  ReedSwitch0.begin(4,3,50);
  ReedSwitch1.begin(6,5,50);

}

void loop()
{
  ReedSwitch0.update();
  ReedSwitch1.update();
  ReedSwitch0Printer.update();
  ReedSwitch1Printer.update();
  led.update();
}