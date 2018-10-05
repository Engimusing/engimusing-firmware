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
/* Example for how to print out readings from the CapSense RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a CapSense Capacitance Sensors.
    See https://www.engimusing.com/products/ for more information about the board.
*/

#if !defined(EFM32TG222)
#error Incorrect Board Selected! Please select Engimusing EFM32TG222 from the Tools->Board: menu.
#endif

#include <CapSenseDevice.h>


CapSenseDevice CapSense0;
CapSenseDevice CapSense1;
CapSenseDevice CapSense2;
CapSenseDevice CapSense3;
CapSenseDevice CapSense4;
CapSenseDevice CapSense5;
CapSenseDevice CapSense6;
CapSenseDevice CapSense7;
CapSenseDevice CapSense8;
CapSenseDevice CapSense9;
CapSenseDevice CapSense_Star;
CapSenseDevice CapSense_Hash;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple CapSense example 0");
  Serial1.println("Simple CapSense example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
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

  
  
  if(serialTimer.update())
  { 
    bool state[12];
    bool risingEdge[12];
    bool fallingEdge[12];

    state[0] = CapSense0.state();
    risingEdge[0] = CapSense0.risingEdge();
    fallingEdge[0] = CapSense0.fallingEdge();

    state[1] = CapSense1.state();
    risingEdge[1] = CapSense1.risingEdge();
    fallingEdge[1] = CapSense1.fallingEdge();

    state[2] = CapSense2.state();
    risingEdge[2] = CapSense2.risingEdge();
    fallingEdge[2] = CapSense2.fallingEdge();

    state[3] = CapSense3.state();
    risingEdge[3] = CapSense3.risingEdge();
    fallingEdge[3] = CapSense3.fallingEdge();

    state[4] = CapSense4.state();
    risingEdge[4] = CapSense4.risingEdge();
    fallingEdge[4] = CapSense4.fallingEdge();

    state[5] = CapSense5.state();
    risingEdge[5] = CapSense5.risingEdge();
    fallingEdge[5] = CapSense5.fallingEdge();

    state[6] = CapSense6.state();
    risingEdge[6] = CapSense6.risingEdge();
    fallingEdge[6] = CapSense6.fallingEdge();

    state[7] = CapSense7.state();
    risingEdge[7] = CapSense7.risingEdge();
    fallingEdge[7] = CapSense7.fallingEdge();

    state[8] = CapSense8.state();
    risingEdge[8] = CapSense8.risingEdge();
    fallingEdge[8] = CapSense8.fallingEdge();

    state[9] = CapSense9.state();
    risingEdge[9] = CapSense9.risingEdge();
    fallingEdge[9] = CapSense9.fallingEdge();

    state[10] = CapSense_Star.state();
    risingEdge[10] = CapSense_Star.risingEdge();
    fallingEdge[10] = CapSense_Star.fallingEdge();

    state[11] = CapSense_Hash.state();
    risingEdge[11] = CapSense_Hash.risingEdge();
    fallingEdge[11] = CapSense_Hash.fallingEdge();


    for(int i = 0; i < 12; i++)
    {
      Serial.print("Sensor ");

      if(i < 10)
      {
        Serial.print(i);
      }
      else if(i == 10)
      {
        Serial.print("Star");
      }
      else if(i == 11)
      {
        Serial.print("Hash");
      }
      Serial.println(":");

      if(state[i])
      {

        Serial.println(" state = on");
      }
      else
      {
        Serial.println(" state = off");
      }

      if(risingEdge[i])
      {
        Serial.println("Rising Edge");
      }

      if(fallingEdge[i])
      {
        Serial.println("Falling Edge");
      }
    }
  
    for(int i = 0; i < 12; i++)
    {
      Serial1.print("Sensor ");

      if(i < 10)
      {
        Serial1.print(i);
      }
      else if(i == 10)
      {
        Serial1.print("Star");
      }
      else if(i == 11)
      {
        Serial1.print("Hash");
      }

      Serial1.println(":");

      if(state[i])
      {
        Serial1.println(" state = on");
      }
      else      
      {
        Serial1.println(" state = off");
      }

      if(risingEdge[i])
      {
        Serial1.println("Rising Edge");
      }

      if(fallingEdge[i])
      {
        Serial1.println("Falling Edge");
      }
    }
  
  }
  led.update();
}