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
*/

//This sketch will work on any Engimusing device with a Serial port so there is not a device check.

#include <Wire.h>

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <CPUInfoDevice.h>

/*
  EFMUSB Commands:
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"STATUS"}

  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"STATUS"}

  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"STATUS"}

  {"TOP":"EFM/CPU","PLD":"STATUS"}
*/

MqttHub HUB;

MqttSerialPort SerialPort;

// Instantiate classes for each the LEDs on the EFMUSB CPU board
// The onOffCtlClass allows for turning the LEDs on and off and
// requesting their status

OnOffCtlModule LEDCtrl0;
OnOffCtlModule LEDCtrl1;
OnOffCtlModule LEDCtrl2;

// Instantiate classes for the CPU temperature and supply voltage
// The device can be used to read the values and the SimpleMqttModule can be set up
// to periodically report the values to an MQTT server

CPUInfoDevice EFMCPU;
SimpleMqttModule EFMCPUMqttMod;

void setup()
{
  SerialPort.begin(HUB, Serial);

  // Start each of the LED services
  // The first parameter is the LED pin
  // The second parameter is the module name
  // The third parameter is the on state for the LEDs
  LEDCtrl0.begin(HUB, ledId[0], "EFM/BOARD/LED0", LOW);
  LEDCtrl1.begin(HUB, ledId[1], "EFM/BOARD/LED1", LOW);
  LEDCtrl2.begin(HUB, ledId[2], "EFM/BOARD/LED2", LOW);

  // Start the CPU services
  EFMCPU.begin();
  EFMCPUMqttMod.begin(HUB, EFMCPU, "EFM/CPU", 5000);
  
}
//int lastMillisOn = 0;
//int lastMillisOff = 1000;

void loop()
{
  HUB.update();
}
