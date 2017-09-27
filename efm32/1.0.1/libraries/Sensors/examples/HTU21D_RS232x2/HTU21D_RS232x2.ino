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
/* Example for how to print out readings from the HTU21D RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a HTU21D humidity and temperature sensor.
    See https://www.engimusing.com/products/htu-3 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <HTU21DDevice.h>
#include <Wire.h>

HTU21DDevice HTU21D;
DevicePrinter HTU21DPrinter0;
DevicePrinter HTU21DPrinter1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple HTU21D example 0");
  Serial1.println("Simple HTU21D example 1");
  led.begin(1000);
 
  HTU21DPrinter0.begin(Serial, HTU21D, 5000, "HTU21D");
  HTU21DPrinter1.begin(Serial1, HTU21D, 5000, "HTU21D");
  
  HTU21D.begin(Wire0, 2);
}

void loop()
{


  HTU21D.update();

  HTU21DPrinter0.update();
  HTU21DPrinter1.update();
  
  
  led.update();
}