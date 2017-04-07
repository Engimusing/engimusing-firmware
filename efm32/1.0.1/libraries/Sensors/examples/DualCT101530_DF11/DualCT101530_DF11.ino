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
/* Example for how to print out readings from the DualCT101530  DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a DualCT101530 Dual Reed Switches.
    See https://www.engimusing.com/products/reedsw-2 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <DualCT101530Device.h>

DualCT101530Device DualCT101530;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple DualCT101530 example 0");

  
  DualCT101530.begin(4, 6, 3, 5, 50);

}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;

  DualCT101530.update();
  

  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();

    digitalWrite(LED_BUILTIN, on);   // toggle the LED (HIGH is the voltage level)
    
    bool switchState[2];
    bool risingEdge[2];
    bool fallingEdge[2];
      
    for(int i = 0; i < 2; i++)
    {
      switchState[i] = DualCT101530.switchState(i);
      risingEdge[i] = DualCT101530.risingEdge(i);
      fallingEdge[i] = DualCT101530.fallingEdge(i);
      
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

    on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  }
}