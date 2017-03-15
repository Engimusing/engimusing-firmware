/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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

  Example for how to setup the MQTT client for the TMP102 DF11 board using the ZB USB Engimusing board
  There are 2 devices using these combinations of boards. An LED and a TMP102 temperature sensor. 
  See http://www.engimusing.com/products/tmp-1 for more information about the board.

  EFMZGUSB Commands:
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMZGUSB/BOARD/TMP102/DEC_C","PLD":"STATUS"}
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif
 
//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <TMP102Device.h>
#include <Wire.h>

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;
TMP102Device TMP102;
SimpleMqttModule TMP102MqttMod;

void setup()
{
  serialPort.begin(HUB, Serial);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFMZGUSB/BOARD/LED", LOW);

  //Initialize the tmp control class which will send the 
  // temperature over MQTT every 10 seconds
  TMP102.begin(Wire0, 5, true);
  TMP102MqttMod.begin(HUB, TMP102, "EFMZGUSB/BOARD/TMP102", 5000);
}

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();
}
