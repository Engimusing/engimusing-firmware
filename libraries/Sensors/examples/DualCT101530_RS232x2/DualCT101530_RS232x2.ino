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
/* Example for how to print out readings from the DualCT101530 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualCT101530 Dual Reed Switches.
    See https://www.engimusing.com/products/reedsw-1 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <CT101530Device.h>


CT101530Device ReedSwitch0;
CT101530Device ReedSwitch1;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple DualCT101530 example 0");
  Serial1.println("Simple DualCT101530 example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
  ReedSwitch0.begin(6,-1,50);
  ReedSwitch1.begin(7,-1,50);
}

void loop()
{


  ReedSwitch0.update();
  ReedSwitch1.update();

  
  
  if(serialTimer.update())
  { 
    bool switchState[2];
    bool risingEdge[2];
    bool fallingEdge[2];
    
    switchState[0] = ReedSwitch0.switchState();
    risingEdge[0] = ReedSwitch0.risingEdge();
    fallingEdge[0] = ReedSwitch0.fallingEdge();
      
    switchState[1] = ReedSwitch1.switchState();
    risingEdge[1] = ReedSwitch1.risingEdge();
    fallingEdge[1] = ReedSwitch1.fallingEdge();
        
    for(int i = 0; i < 2; i++)
    {
      Serial.print("Switch ");
      Serial.print(i + 1);
        
      if(switchState[i])
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
  
    for(int i = 0; i < 2; i++)
    {
      Serial1.print("Switch ");
      Serial1.print(i + 1);
        
      if(switchState[i])
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