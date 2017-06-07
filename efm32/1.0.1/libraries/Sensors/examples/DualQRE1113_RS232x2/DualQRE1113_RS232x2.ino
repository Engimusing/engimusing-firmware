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
/* Example for how to print out readings from the DualQRE1113 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualQRE1113 dual reflective sensors.
    See https://www.engimusing.com/products/qre2-1 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <QRE1113Device.h>


QRE1113Device ReflectiveSensor0;
DevicePrinter ReflectiveSensor0Printer0;
DevicePrinter ReflectiveSensor0Printer1;
QRE1113Device ReflectiveSensor1;
DevicePrinter ReflectiveSensor1Printer0;
DevicePrinter ReflectiveSensor1Printer1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple DualQRE1113 example 0");
  Serial1.println("Simple DualQRE1113 example 1");
  led.begin(1000);
 
  ReflectiveSensor0Printer0.begin(Serial, ReflectiveSensor0, 5000, "ReflectiveSensor0");
  ReflectiveSensor0Printer1.begin(Serial1, ReflectiveSensor0, 5000, "ReflectiveSensor0");
  ReflectiveSensor1Printer0.begin(Serial, ReflectiveSensor1, 5000, "ReflectiveSensor1");
  ReflectiveSensor1Printer1.begin(Serial1, ReflectiveSensor1, 5000, "ReflectiveSensor1");
  
  ReflectiveSensor0.begin(7,12,10);
  ReflectiveSensor1.begin(4,11,10);
}

void loop()
{


  ReflectiveSensor0.update();
  ReflectiveSensor1.update();

  ReflectiveSensor0Printer0.update();
  ReflectiveSensor0Printer1.update();
  ReflectiveSensor1Printer0.update();
  ReflectiveSensor1Printer1.update();
  led.update();
}