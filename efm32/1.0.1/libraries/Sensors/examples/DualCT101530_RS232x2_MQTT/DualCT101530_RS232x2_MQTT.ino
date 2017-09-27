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
/* Example for how to setup the MQTT client for the DualCT101530 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a DualCT101530 Dual Reed Switches.
    See https://www.engimusing.com/products/reedsw-1 for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <CT101530Device.h>


/*
  EFM32ZG108 Commands:
  {"TOP":"EFM32ZG108/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32ZG108/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32ZG108/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZG108/BOARD/ReedSwitch0/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZG108/BOARD/ReedSwitch1/CTL","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

CT101530Device ReedSwitch0;
SimpleMqttModule ReedSwitch0MqttMod;
CT101530Device ReedSwitch1;
SimpleMqttModule ReedSwitch1MqttMod;


void setup() 
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, LED_BUILTIN, "EFM32ZG108/BOARD/LED", HIGH);

  
  ReedSwitch0.begin(6,-1,50);
  ReedSwitch0MqttMod.begin(HUB, ReedSwitch0, "EFM32ZG108/BOARD/ReedSwitch0", 10000);
  ReedSwitch1.begin(7,-1,50);
  ReedSwitch1MqttMod.begin(HUB, ReedSwitch1, "EFM32ZG108/BOARD/ReedSwitch1", 10000);
}

void loop()
{

  //Update the MQTT communication so it can send status and receive requests
  HUB.update();

}