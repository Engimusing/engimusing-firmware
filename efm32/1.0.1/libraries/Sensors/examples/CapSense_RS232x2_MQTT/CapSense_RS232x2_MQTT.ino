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
/* Example for how to setup the MQTT client for the CapSense RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a CapSense Capacitance Sensors.
    See https://www.engimusing.com/products/ for more information about the board.
*/

#if !defined(EFM32TG222)
#error Incorrect Board Selected! Please select Engimusing EFM32TG222 from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <CapSenseDevice.h>


/*
  EFM32TG222 Commands:
  {"TOP":"EFM32TG222/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32TG222/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32TG222/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32TG222/BOARD/CapSense0/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense1/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense2/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense3/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense4/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense5/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense6/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense7/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense8/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense9/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense_Star/","PLD":"STATUS"}
  {"TOP":"EFM32TG222/BOARD/CapSense_Hash/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

CapSenseDevice CapSense0;
SimpleMqttModule CapSense0MqttMod;
CapSenseDevice CapSense1;
SimpleMqttModule CapSense1MqttMod;
CapSenseDevice CapSense2;
SimpleMqttModule CapSense2MqttMod;
CapSenseDevice CapSense3;
SimpleMqttModule CapSense3MqttMod;
CapSenseDevice CapSense4;
SimpleMqttModule CapSense4MqttMod;
CapSenseDevice CapSense5;
SimpleMqttModule CapSense5MqttMod;
CapSenseDevice CapSense6;
SimpleMqttModule CapSense6MqttMod;
CapSenseDevice CapSense7;
SimpleMqttModule CapSense7MqttMod;
CapSenseDevice CapSense8;
SimpleMqttModule CapSense8MqttMod;
CapSenseDevice CapSense9;
SimpleMqttModule CapSense9MqttMod;
CapSenseDevice CapSense_Star;
SimpleMqttModule CapSense_StarMqttMod;
CapSenseDevice CapSense_Hash;
SimpleMqttModule CapSense_HashMqttMod;


void setup() 
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFM32TG222/BOARD/LED", HIGH);


  
  CapSense0.begin(15,50.0);
  CapSense0MqttMod.begin(HUB, CapSense0, "EFM32TG222/BOARD/CapSense0", 10000);
  CapSense1.begin(8,50.0);
  CapSense1MqttMod.begin(HUB, CapSense1, "EFM32TG222/BOARD/CapSense1", 10000);
  CapSense2.begin(4,50.0);
  CapSense2MqttMod.begin(HUB, CapSense2, "EFM32TG222/BOARD/CapSense2", 10000);
  CapSense3.begin(3,50.0);
  CapSense3MqttMod.begin(HUB, CapSense3, "EFM32TG222/BOARD/CapSense3", 10000);
  CapSense4.begin(9,50.0);
  CapSense4MqttMod.begin(HUB, CapSense4, "EFM32TG222/BOARD/CapSense4", 10000);
  CapSense5.begin(13,50.0);
  CapSense5MqttMod.begin(HUB, CapSense5, "EFM32TG222/BOARD/CapSense5", 10000);
  CapSense6.begin(2,50.0);
  CapSense6MqttMod.begin(HUB, CapSense6, "EFM32TG222/BOARD/CapSense6", 10000);
  CapSense7.begin(10,50.0);
  CapSense7MqttMod.begin(HUB, CapSense7, "EFM32TG222/BOARD/CapSense7", 10000);
  CapSense8.begin(14,50.0);
  CapSense8MqttMod.begin(HUB, CapSense8, "EFM32TG222/BOARD/CapSense8", 10000);
  CapSense9.begin(1,50.0);
  CapSense9MqttMod.begin(HUB, CapSense9, "EFM32TG222/BOARD/CapSense9", 10000);
  CapSense_Star.begin(11,50.0);
  CapSense_StarMqttMod.begin(HUB, CapSense_Star, "EFM32TG222/BOARD/CapSense_Star", 10000);
  CapSense_Hash.begin(0,50.0);
  CapSense_HashMqttMod.begin(HUB, CapSense_Hash, "EFM32TG222/BOARD/CapSense_Hash", 10000);
}

void loop()
{

  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

}