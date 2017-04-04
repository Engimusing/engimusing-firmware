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
/* Example for how to setup the MQTT client for the TMD26721 DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a TMD26721 proximity sensor.
    See https://www.engimusing.com/products/tmd2771-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <TMD26721Device.h>
#include <Wire.h>

/*
  EFM32ZGUSB Commands:
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZGUSB/BOARD/TMD26721/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

TMD26721Device TMD26721;
SimpleMqttModule TMD26721MqttMod;

void setup() 
{
  serialPort.begin(HUB, Serial);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFM32ZGUSB/BOARD/LED", HIGH);

  
  //Initialize the TMD26721 which will report the proximity every 10 seconds
  // The 4 parameter is the number of pulses. It can be anything between 0 and 255.
  // If it is 0 then it will act more like a light detector than a proximity detector.
  
  TMD26721.begin(Wire, 5, 4);
  TMD26721MqttMod.begin(HUB, TMD26721, "EFM32ZGUSB/BOARD/TMD26721", 10000);
}

void loop() 
{

  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

}