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
/* Example for how to setup the MQTT client for the MPL115A1 RS232x2 Engimusing board
    There are 2 devices on this board. An LED and a MPL115A1 pressure/temperature sensor.
    See https://www.engimusing.com/products/mpl115-3 for more information about the board.
*/

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <MPL115A1Device.h>
#include <SPI.h>

/*
  EFM32TG110 Commands:
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32TG110/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32TG110/BOARD/MPL115A1/","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

MPL115A1Device MPL115A1;
SimpleMqttModule MPL115A1MqttMod;


void setup() 
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFM32TG110/BOARD/LED", HIGH);


  
  MPL115A1.begin(3, -1, 4, SPI);
  MPL115A1MqttMod.begin(HUB, MPL115A1, "EFM32TG110/BOARD/MPL115A1", 10000);
}

void loop() {

  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

}