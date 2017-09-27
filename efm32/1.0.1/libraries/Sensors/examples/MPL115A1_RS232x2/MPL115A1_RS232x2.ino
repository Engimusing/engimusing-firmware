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
/* Example for how to print out readings from the MPL115A1 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MPL115A1 pressure/temperature sensor.
    See https://www.engimusing.com/products/mpl115-3 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <MPL115A1Device.h>
#include <SPI.h>

MPL115A1Device MPL115A1;
DevicePrinter MPL115A1Printer0;
DevicePrinter MPL115A1Printer1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple MPL115A1 example 0");
  Serial1.println("Simple MPL115A1 example 1");
  led.begin(1000);
 
  MPL115A1Printer0.begin(Serial, MPL115A1, 5000, "MPL115A1");
  MPL115A1Printer1.begin(Serial1, MPL115A1, 5000, "MPL115A1");
  
  MPL115A1.begin(3, -1, 4, SPI);
}

void loop()
{


  MPL115A1.update();

  MPL115A1Printer0.update();
  MPL115A1Printer1.update();
  
  
  led.update();
}