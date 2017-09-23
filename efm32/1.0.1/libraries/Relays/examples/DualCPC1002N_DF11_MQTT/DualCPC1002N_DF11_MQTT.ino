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
/* Example for how to setup the MQTT client for the DualCPC1002N DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a DualCPC1002N Dual DC Switches.
    See https://www.engimusing.com/collections/relays/products/ssr_dc-2 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <OnOffCtrlDevice.h>


/*
  EFM32ZGUSB Commands:
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZGUSB/BOARD/CPC1002N_0/","PLD":"STATUS"}
  {"TOP":"EFM32ZGUSB/BOARD/CPC1002N_1/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

OnOffCtrlDevice CPC1002N_0;
SimpleMqttModule CPC1002N_0MqttMod;
OnOffCtrlDevice CPC1002N_1;
SimpleMqttModule CPC1002N_1MqttMod;

void setup() 
{
  serialPort.begin(HUB, Serial);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, LED_BUILTIN, "EFM32ZGUSB/BOARD/LED", HIGH);

  
  CPC1002N_0.begin(6, false, HIGH);
  CPC1002N_0MqttMod.begin(HUB, CPC1002N_0, "EFM32ZGUSB/BOARD/CPC1002N_0", 10000);
  CPC1002N_1.begin(10, false, HIGH);
  CPC1002N_1MqttMod.begin(HUB, CPC1002N_1, "EFM32ZGUSB/BOARD/CPC1002N_1", 10000);
}

void loop() 
{

  //Update the MQTT communication so it can send status and receive requests
  HUB.update();

}