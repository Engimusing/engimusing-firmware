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

  Example for how to setup the MQTT client for the HTU21D RS232x2 Engimusing board
   There are 3 devices on this board. An LED and an HTU21D temperature and humidity sensor. 
   See http://www.engimusing.com/products/reedsw-1 for more information about the board.

  EFMZG108 Commands:
    {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"ON"}
    {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"OFF"}
    {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"STATUS"}

    {"TOP":"EFMZG108/BOARD/HTU21D/DEC_C","PLD":"STATUS"}
    {"TOP":"EFMZG108/BOARD/HTU21D/HUM","PLD":"STATUS"}
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <Wire.h>

#include "Arduino.h"

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <HTU21DDevice.h>

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;
HTU21DDevice HTU21D;
SimpleMqttModule HTU21DMqttMod;

void setup()
{
  serialPort1.begin(HUB, Serial);  
  serialPort2.begin(HUB, Serial1);
  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFMZG108/BOARD/LED", HIGH);

  //Initialize the Humidity sensor
  HTU21D.begin(Wire0, 2);
  HTU21DMqttMod.begin(HUB, HTU21D, "EFMZG108/BOARD/HTU21D", 5000);
}

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();
}