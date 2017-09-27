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
/* Example for how to print out readings from the MPL115A1  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a MPL115A1 pressure/temperature sensor.
    See https://www.engimusing.com/products/m115a1-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <MPL115A1Device.h>
#include <SPI.h>
MPL115A1Device MPL115A1;
DevicePrinter MPL115A1Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  MPL115A1Printer.begin(Serial, MPL115A1, 5000, "MPL115A1");
  Serial.println("Simple MPL115A1 example 0");
  
  MPL115A1.begin(10, 6, 4, SPI);

}

void loop()
{
  MPL115A1.update();
  MPL115A1Printer.update();
  
  led.update();
}