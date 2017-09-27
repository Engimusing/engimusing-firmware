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
/* Example for how to setup the MQTT client for the SSCDNNN150PG2A3 DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and a SSCDNNN150PG2A3 SSCDNNN150PG2A3 150PSI (1MPa) Pressure Sensor.
    See pre-release for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <SSCDNNN150PG2A3Device.h>
#include <Wire.h>

/*
  EFM32ZGUSB Commands:
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFM32ZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFM32ZGUSB/BOARD/SSCDNNN150PG2A3/CTL","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM
// object when begin() is called so they can be updated
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

SSCDNNN150PG2A3Device SSCDNNN150PG2A3;
SimpleMqttModule SSCDNNN150PG2A3MqttMod;

void setup() 
{
  serialPort.begin(HUB, Serial);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, LED_BUILTIN, "EFM32ZGUSB/BOARD/LED", HIGH);

  
  SSCDNNN150PG2A3.begin(Wire0, 0);
  SSCDNNN150PG2A3MqttMod.begin(HUB, SSCDNNN150PG2A3, "EFM32ZGUSB/BOARD/SSCDNNN150PG2A3", 10000);
}

void loop() 
{

  //Update the MQTT communication so it can send status and receive requests
  HUB.update();

}