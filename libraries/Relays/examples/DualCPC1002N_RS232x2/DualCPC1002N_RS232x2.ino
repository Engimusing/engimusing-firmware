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
/* Example for how to print out readings from the DualCPC1002N RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualCPC1002N Dual DC Switches.
    See https://www.engimusing.com/collections/relays/products/ssr_dc-5 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <OnOffCtrlDevice.h>


OnOffCtrlDevice CPC1002N_0;
OnOffCtrlDevice CPC1002N_1;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple DualCPC1002N example 0");
  Serial1.println("Simple DualCPC1002N example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
  CPC1002N_0.begin(7, false, HIGH);
  CPC1002N_1.begin(8, false, LOW);
}

void loop()
{


  CPC1002N_0.update();
  CPC1002N_1.update();

  
  static char buffer[4];
  //Parse Serial port and if 0:ON, 0:OF, 1:ON, or 1:OF are sent  then turn on or of the DC relays
  if(Serial.available())
  {
      for(int i = 0; i < 3; i++)
      {
        buffer[i] = buffer[i+1];
      }
      
      buffer[3] = Serial.read();
  }
  
  if(buffer[0] == '0')
  {
    if(buffer[2] == 'O' && buffer[3] == 'N')
    {
      CPC1002N_0.setState(true);
    }
    else if(buffer[2] == 'O' && buffer[3] == 'F')
    {
      CPC1002N_0.setState(false);
    }
  }
  if(buffer[0] == '1')
  {
    if(buffer[2] == 'O' && buffer[3] == 'N')
    {
      CPC1002N_1.setState(true);
    }
    else if(buffer[2] == 'O' && buffer[3] == 'F')
    {
      CPC1002N_1.setState(false);
    }
  }
  
  static char buffer1[4];
  
  //Parse Serial1 port and if 0:ON, 0:OF, 1:ON, or 1:OF are sent  then turn on or of the DC relays
  if(Serial1.available())
  {
    for(int i = 0; i < 3; i++)
    {
      buffer1[i] = buffer1[i+1];
    }
    
    buffer1[3] = Serial1.read();
  }
  
  if(buffer1[0] == '0')
  {
    if(buffer1[2] == 'O' && buffer1[3] == 'N')
    {
      CPC1002N_0.setState(true);
    }
    else if(buffer1[2] == 'O' && buffer1[3] == 'F')
    {
      CPC1002N_0.setState(false);
    }
  }
  if(buffer1[0] == '1')
  {
    if(buffer1[2] == 'O' && buffer1[3] == 'N')
    {
      CPC1002N_1.setState(true);
    }
    else if(buffer1[2] == 'O' && buffer1[3] == 'F')
    {
      CPC1002N_1.setState(false);
    }
  }
  
  led.update();
}