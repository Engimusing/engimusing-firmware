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
/* Example for how to print out readings from the DualQRE1113 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualQRE1113 dual reflective sensors.
    See https://www.engimusing.com/products/qre2-1 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

#include <QRE1113Device.h>


QRE1113Device ReflectiveSensor0;
QRE1113Device ReflectiveSensor1;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple DualQRE1113 example 0");
  Serial1.println("Simple DualQRE1113 example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
  ReflectiveSensor0.begin(7,12,10);
  ReflectiveSensor1.begin(4,11,10);
}

void loop()
{


  ReflectiveSensor0.update();
  ReflectiveSensor1.update();

  
  
  if(serialTimer.update())
  { 
    bool switchState[2];
    bool risingEdge[2];
    bool fallingEdge[2];
    switchState[0] = ReflectiveSensor0.switchState();
    risingEdge[0] = ReflectiveSensor0.risingEdge();
    fallingEdge[0] = ReflectiveSensor0.fallingEdge();
    switchState[1] = ReflectiveSensor1.switchState();
    risingEdge[1] = ReflectiveSensor1.risingEdge();
    fallingEdge[1] = ReflectiveSensor1.fallingEdge();
    
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