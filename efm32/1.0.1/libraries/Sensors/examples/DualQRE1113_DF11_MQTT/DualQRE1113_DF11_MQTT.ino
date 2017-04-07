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
/* Example for how to setup the MQTT client for the DualQRE1113 DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a DualQRE1113 dual reflective sensors.
    See https://www.engimusing.com/products/qre1113-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <QRE1113Device.h>


/*
  EFM32ZGUSB Commands:
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZGUSB/BOARD/ReflectiveSensor0/","PLD":"STATUS"}
  {"TOP":"EFM32ZGUSB/BOARD/ReflectiveSensor1/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

QRE1113Device ReflectiveSensor0;
SimpleMqttModule ReflectiveSensor0MqttMod;
QRE1113Device ReflectiveSensor1;
SimpleMqttModule ReflectiveSensor1MqttMod;

void setup() 
{
  serialPort.begin(HUB, Serial);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFM32ZGUSB/BOARD/LED", HIGH);

  
  ReflectiveSensor0.begin(7,2,10);
  ReflectiveSensor0MqttMod.begin(HUB, ReflectiveSensor0, "EFM32ZGUSB/BOARD/ReflectiveSensor0", 10000);
  ReflectiveSensor1.begin(4,3,10);
  ReflectiveSensor1MqttMod.begin(HUB, ReflectiveSensor1, "EFM32ZGUSB/BOARD/ReflectiveSensor1", 10000);
}

void loop() 
{

  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

}