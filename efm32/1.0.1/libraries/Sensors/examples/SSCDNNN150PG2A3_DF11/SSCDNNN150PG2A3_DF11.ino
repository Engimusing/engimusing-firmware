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
/* Example for how to print out readings from the SSCDNNN150PG2A3  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a SSCDNNN150PG2A3 SSCDNNN150PG2A3 150PSI (1MPa) Pressure Sensor.
    See pre-release for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <SSCDNNN150PG2A3Device.h>
#include <Wire.h>
SSCDNNN150PG2A3Device SSCDNNN150PG2A3;
DevicePrinter SSCDNNN150PG2A3Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  SSCDNNN150PG2A3Printer.begin(Serial, SSCDNNN150PG2A3, 5000, "SSCDNNN150PG2A3");
  Serial.println("Simple SSCDNNN150PG2A3 example 0");
  
  SSCDNNN150PG2A3.begin(Wire0, 0);

}

void loop()
{
  SSCDNNN150PG2A3.update();
  SSCDNNN150PG2A3Printer.update();
  led.update();
}