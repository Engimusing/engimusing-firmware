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
/* Example for how to print out readings from the CapSense RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a CapSense Capacitance Sensors.
    See https://www.engimusing.com/products/ for more information about the board.
*/

#if !defined(EFM32TG222)
#error Incorrect Board Selected! Please select Engimusing EFM32TG222 from the Tools->Board: menu.
#endif

#include <DevicePrinter.h>

#include <CapSenseDevice.h>


CapSenseDevice CapSense0;
DevicePrinter CapSense0Printer0;
DevicePrinter CapSense0Printer1;
CapSenseDevice CapSense1;
DevicePrinter CapSense1Printer0;
DevicePrinter CapSense1Printer1;
CapSenseDevice CapSense2;
DevicePrinter CapSense2Printer0;
DevicePrinter CapSense2Printer1;
CapSenseDevice CapSense3;
DevicePrinter CapSense3Printer0;
DevicePrinter CapSense3Printer1;
CapSenseDevice CapSense4;
DevicePrinter CapSense4Printer0;
DevicePrinter CapSense4Printer1;
CapSenseDevice CapSense5;
DevicePrinter CapSense5Printer0;
DevicePrinter CapSense5Printer1;
CapSenseDevice CapSense6;
DevicePrinter CapSense6Printer0;
DevicePrinter CapSense6Printer1;
CapSenseDevice CapSense7;
DevicePrinter CapSense7Printer0;
DevicePrinter CapSense7Printer1;
CapSenseDevice CapSense8;
DevicePrinter CapSense8Printer0;
DevicePrinter CapSense8Printer1;
CapSenseDevice CapSense9;
DevicePrinter CapSense9Printer0;
DevicePrinter CapSense9Printer1;
CapSenseDevice CapSense_Star;
DevicePrinter CapSense_StarPrinter0;
DevicePrinter CapSense_StarPrinter1;
CapSenseDevice CapSense_Hash;
DevicePrinter CapSense_HashPrinter0;
DevicePrinter CapSense_HashPrinter1;
TogglePin led;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple CapSense example 0");
  Serial1.println("Simple CapSense example 1");
  led.begin(1000);
 
  CapSense0Printer0.begin(Serial, CapSense0, 5000, "CapSense0");
  CapSense0Printer1.begin(Serial1, CapSense0, 5000, "CapSense0");
  CapSense1Printer0.begin(Serial, CapSense1, 5000, "CapSense1");
  CapSense1Printer1.begin(Serial1, CapSense1, 5000, "CapSense1");
  CapSense2Printer0.begin(Serial, CapSense2, 5000, "CapSense2");
  CapSense2Printer1.begin(Serial1, CapSense2, 5000, "CapSense2");
  CapSense3Printer0.begin(Serial, CapSense3, 5000, "CapSense3");
  CapSense3Printer1.begin(Serial1, CapSense3, 5000, "CapSense3");
  CapSense4Printer0.begin(Serial, CapSense4, 5000, "CapSense4");
  CapSense4Printer1.begin(Serial1, CapSense4, 5000, "CapSense4");
  CapSense5Printer0.begin(Serial, CapSense5, 5000, "CapSense5");
  CapSense5Printer1.begin(Serial1, CapSense5, 5000, "CapSense5");
  CapSense6Printer0.begin(Serial, CapSense6, 5000, "CapSense6");
  CapSense6Printer1.begin(Serial1, CapSense6, 5000, "CapSense6");
  CapSense7Printer0.begin(Serial, CapSense7, 5000, "CapSense7");
  CapSense7Printer1.begin(Serial1, CapSense7, 5000, "CapSense7");
  CapSense8Printer0.begin(Serial, CapSense8, 5000, "CapSense8");
  CapSense8Printer1.begin(Serial1, CapSense8, 5000, "CapSense8");
  CapSense9Printer0.begin(Serial, CapSense9, 5000, "CapSense9");
  CapSense9Printer1.begin(Serial1, CapSense9, 5000, "CapSense9");
  CapSense_StarPrinter0.begin(Serial, CapSense_Star, 5000, "CapSense_Star");
  CapSense_StarPrinter1.begin(Serial1, CapSense_Star, 5000, "CapSense_Star");
  CapSense_HashPrinter0.begin(Serial, CapSense_Hash, 5000, "CapSense_Hash");
  CapSense_HashPrinter1.begin(Serial1, CapSense_Hash, 5000, "CapSense_Hash");
  
  CapSense0.begin(15,50.0);
  CapSense1.begin(8,50.0);
  CapSense2.begin(4,50.0);
  CapSense3.begin(3,50.0);
  CapSense4.begin(9,50.0);
  CapSense5.begin(13,50.0);
  CapSense6.begin(2,50.0);
  CapSense7.begin(10,50.0);
  CapSense8.begin(14,50.0);
  CapSense9.begin(1,50.0);
  CapSense_Star.begin(11,50.0);
  CapSense_Hash.begin(0,50.0);
}

void loop()
{


  CapSense0.update();
  CapSense1.update();
  CapSense2.update();
  CapSense3.update();
  CapSense4.update();
  CapSense5.update();
  CapSense6.update();
  CapSense7.update();
  CapSense8.update();
  CapSense9.update();
  CapSense_Star.update();
  CapSense_Hash.update();

  CapSense0Printer0.update();
  CapSense0Printer1.update();
  CapSense1Printer0.update();
  CapSense1Printer1.update();
  CapSense2Printer0.update();
  CapSense2Printer1.update();
  CapSense3Printer0.update();
  CapSense3Printer1.update();
  CapSense4Printer0.update();
  CapSense4Printer1.update();
  CapSense5Printer0.update();
  CapSense5Printer1.update();
  CapSense6Printer0.update();
  CapSense6Printer1.update();
  CapSense7Printer0.update();
  CapSense7Printer1.update();
  CapSense8Printer0.update();
  CapSense8Printer1.update();
  CapSense9Printer0.update();
  CapSense9Printer1.update();
  CapSense_StarPrinter0.update();
  CapSense_StarPrinter1.update();
  CapSense_HashPrinter0.update();
  CapSense_HashPrinter1.update();
  led.update();
}