/*
  Copyright (c) 2016-2018 Engimusing LLC.  All right reserved.
  
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
/* Example for how to print out readings from the ACS716  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a ACS716 current sensor.
    See http://www.engimusing.com/products/ACS716-2 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <ACS716Device.h>

ACS716Device ACS716;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  led.begin(1000);
  serialTimer.begin(1000,true);
  Serial.println("Simple ACS716 example 0");
  
  //Initialize the ACS716 which will report the current every 10 seconds
  // The two parameters A1 are the power pin and power feedback pin which in this case are the same
  // other implementations they may not be the same and can both be -1 which means neither is connected
  // The A0 parameter is the ADC pin that is connected to the ACS716 output pin.
  ACS716.begin(ACS716Device::ACS716_6BB, A1, A1, A0, 100);
  
}

void loop()
{
  ACS716.update();

  if(serialTimer.update())
  { 
    float current = ACS716.instantCurrent();
    Serial.print("Current Amperage = ");
    Serial.println(current);
  }
  led.update();
}