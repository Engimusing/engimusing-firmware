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
/* Example for how to print out readings from the MLX92212  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a MLX92212 3-Wire Hall Effect Latch / Switch.
    See https://www.engimusing.com/products/m92212-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <MLX92212Device.h>

MLX92212Device MLX92212;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  led.begin(1000);
  serialTimer.begin(1000,true);
  Serial.println("Simple MLX92212 example 0");
  
  MLX92212.begin(7, 10, 20);
  
}

void loop()
{
  MLX92212.update();

  if(serialTimer.update())
  { 
    bool switchState = MLX92212.switchState();
    bool risingEdge = MLX92212.risingEdge();
    bool fallingEdge = MLX92212.fallingEdge();

    if(switchState)
    {
      Serial.println("state = on");
    }
    else
    {
      Serial.println("state = off");
    }

    if(risingEdge)
    {
      Serial.println("Rising Edge");
    }

    if(fallingEdge)
    {
      Serial.println("Falling Edge");
    }
  }
  led.update();
}