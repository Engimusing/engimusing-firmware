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
/* Example for how to print out readings from the RPI1031  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a RPI1031 Tilt sensor.
    See https://www.engimusing.com/products/rpi1031-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <RPI1031Device.h>

RPI1031Device RPI1031;
DevicePrinter RPI1031Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  RPI1031Printer.begin(Serial, RPI1031, 5000, "RPI1031");
  Serial.println("Simple RPI1031 example 0");
  
  //sets up the 5 pins needed to setup and communicate with the RPI1031
  RPI1031.begin(3,4,5,6,7,10);

}

void loop()
{
  RPI1031.update();
  RPI1031Printer.update();
  led.update();
}