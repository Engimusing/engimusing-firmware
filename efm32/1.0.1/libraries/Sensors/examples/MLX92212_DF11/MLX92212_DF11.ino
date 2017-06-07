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
/* Example for how to print out readings from the MLX92212  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a MLX92212 3-Wire Hall Effect Latch / Switch.
    See https://www.engimusing.com/products/m92212-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <MLX92212Device.h>

MLX92212Device MLX92212;
DevicePrinter MLX92212Printer;
TogglePin led;


void setup()
{
  Serial.begin(115200);
  led.begin(1000);

  MLX92212Printer.begin(Serial, MLX92212, 5000, "MLX92212");
  Serial.println("Simple MLX92212 example 0");
  
  MLX92212.begin(7, 10, 20);

}

void loop()
{
  MLX92212.update();
  MLX92212Printer.update();
  led.update();
}