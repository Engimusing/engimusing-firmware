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
/* Example for how to print out readings from the TMD26721  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a TMD26721 proximity sensor.
    See https://www.engimusing.com/products/tmd2771-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <TMD26721Device.h>
#include <Wire.h>
TMD26721Device TMD26721;
DevicePrinter TMD26721Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  TMD26721Printer.begin(Serial, TMD26721, 5000, "TMD26721");
  Serial.println("Simple TMD26721 example 0");
  
  //Initialize the TMD26721 which will report the proximity every 10 seconds
  // The 4 parameter is the number of pulses. It can be anything between 0 and 255.
  // If it is 0 then it will act more like a light detector than a proximity detector.
  
  TMD26721.begin(Wire, 5, 4);

}

void loop()
{
  TMD26721.update();
  TMD26721Printer.update();
  
  led.update();
}