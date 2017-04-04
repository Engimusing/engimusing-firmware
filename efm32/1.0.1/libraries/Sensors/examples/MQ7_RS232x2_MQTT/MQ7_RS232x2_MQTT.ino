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
/* Example for how to setup the MQTT client for the MQ7 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MQ7 CO detector.
    See https://www.engimusing.com/products/gas-4 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <MQ7Device.h>


/*
  EFM32TG110 Commands:
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32TG110/BOARD/MQ7/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

MQ7Device MQ7;
SimpleMqttModule MQ7MqttMod;


void setup() 
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFM32TG110/BOARD/LED", HIGH);


  
  //Initialize the MQ7 CO Sensor
  //Pins:
  // PWM Controller - 7
  // Analog Sensor Input - A0
  
  MQ7.begin(7, A0);
  MQ7MqttMod.begin(HUB, MQ7, "EFM32TG110/BOARD/MQ7", 10000);
}

void loop() {

  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

}