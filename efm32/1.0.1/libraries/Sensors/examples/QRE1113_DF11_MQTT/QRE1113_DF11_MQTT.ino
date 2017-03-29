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


#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu. 
#endif

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <CPUInfoDevice.h>

/*
  EFMUSB Commands:
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/CPU","PLD":"STATUS"}

  QRE Commands:
  {"TOP":"QRE1/SENSOR/QRE"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

#define LTSENS_PIN    2
#define GREEN_LED    13
#define BLUE_LED     14
#define RED_LED      15

OnOffCtlModule EFMREDLED;
OnOffCtlModule EFMBLUELED;
OnOffCtlModule EFMGREENLED;

CPUInfoDevice EFMCPU;
SimpleMqttModule EFMCPUMqttMod;

MomentarySwitchModule QRELTS;

void setup()
{
  serialPort.begin(HUB, Serial);

  EFMREDLED.begin(HUB, RED_LED, "EFMUSB/RED/LED", LOW);
  EFMBLUELED.begin(HUB, BLUE_LED, "EFMUSB/BLUE/LED", LOW);
  EFMGREENLED.begin(HUB, GREEN_LED, "EFMUSB/GREEN/LED", LOW);

  EFMCPU.begin();
  EFMCPUMqttMod.begin(HUB, EFMCPU, "EFMUSB/CPU", 5000);
  
  QRELTS.begin(HUB, LTSENS_PIN, "HAB/LTSENSOR", 2);
}

void loop()
{
  HUB.update();
}

