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
  
  EFMBoolModule commands, 0 is false and 1 is true
  {"TOP":"INPUT/TEST/BOOL","PLD":"0"}
  {"TOP":"INPUT/TEST/BOOL","PLD":"1"} 
  
  EFMIntModule command
  {"TOP":"INPUT/TEST/INT","PLD":"0"}
  
  EFMFloatModule command
  {"TOP":"INPUT/TEST/FLOAT","PLD":"0.0"}
  
  EFMStringModule command
  {"TOP":"INPUT/TEST/STRING","PLD":"CHARACTERS"}
  
  MessageInputModule can also be used to listen to other devices. For example:
  EFMFloatModule.begin(HUB, "EFM32ZG108/BOARD/TMP102?", "DEG_C");
  would get the temperature from the RS232 TMP102 example.
  
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

MessageInputModule<bool> EFMBoolModule;
MessageInputModule<int32_t> EFMIntModule;
MessageInputModule<float> EFMFloatModule;
MessageInputStringModule EFMStringModule;

void setup()
{
  SerialPort.begin(HUB, Serial);

  EFMBoolModule.begin(HUB, "INPUT/TEST", "BOOL");
  EFMIntModule.begin(HUB, "INPUT/TEST", "INT");
  EFMFloatModule.begin(HUB, "INPUT/TEST", "FLOAT");
  EFMStringModule.begin(HUB, "INPUT/TEST", "STRING");
  
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

void loop()
{
  HUB.update();

  //hasNewData() returns true once the input module has recieved new data
  // it will return false again after getInput() is called.
  if(EFMBoolModule.hasNewData())
  {
    Serial.println(EFMBoolModule.getInput() ? "true" : "false");
  }
  
  if(EFMIntModule.hasNewData())
  {
    Serial.println(EFMIntModule.getInput());
  }
  
  if(EFMFloatModule.hasNewData())
  {
    Serial.println(EFMFloatModule.getInput());
  }
  
  if(EFMStringModule.hasNewData())
  {
    Serial.println(EFMStringModule.getInputString());
  }
  
}
