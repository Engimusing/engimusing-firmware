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
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu. Or adjust the pins below to work with another DF11 engiumsing board.
#endif

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

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

  {"TOP":"EFMUSB/CPU/TMPC"}
  {"TOP":"EFMUSB/CPU/TMPF"}
  {"TOP":"EFMUSB/CPU/VDD"}

  HAB Commands:
  {"TOP":"HAB/LED/CTL","PLD":"ON"}
  {"TOP":"HAB/LED/CTL","PLD":"OFF"}
  {"TOP":"HAB/LED/CTL","PLD":"STATUS"}

  {"TOP":"HABTUTOR/SWITCH/RED"}

  {"TOP":"HABTUTOR/SWITCH/BLACK"}

  {"TOP":"HABTUTOR/SENSOR/QRE"}

  {"TOP":"HABTUTOR/SWITCH/REED"}

  {"TOP":"HAB/POT/ADC"}

  {"TOP":"HAB/BUZZER/TONE","PLD":"ON"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"OFF"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"STATUS"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"F500"} // freq in Hz
  {"TOP":"HAB/BUZZER/TONE","PLD":"D200"} // duration in seconds
*/

MqttHub HUB;
MqttSerialPort serialPort;

#define SW1_PIN       2
#define POT_PIN       3
#define REEDSW_PIN    4
#define HABLED_PIN    5
#define BUZZER_PIN    6
#define SWPULL_PIN    7
#define LTSENS_PIN    8
#define SW2_PIN      10
#define GREEN_LED    13
#define BLUE_LED     14
#define RED_LED      15

DigitalQre1113SwitchModule HABLTS;
MomentarySwitchModule HABS1;
MomentarySwitchModule HABS2;
DetectorSwitchModule HABREED;
OnOffCtlModule HABLED;
ToneCtlModule HABBUZZ;
AdcCtlModule HABPOT;
OnOffCtlModule EFMREDLED;
OnOffCtlModule EFMBLUELED;
OnOffCtlModule EFMGREENLED;
CpuVddModule EFMCPUVDD;
CpuTempModule EFMCPUTMP;


void setup()
{
  serialPort.begin(HUB, Serial);

  pinMode(SWPULL_PIN, OUTPUT);       // Switch pull up
  digitalWrite(SWPULL_PIN, HIGH);

  EFMREDLED.begin(HUB, RED_LED, "EFMUSB/RED/LED", LOW);
  EFMBLUELED.begin(HUB, BLUE_LED, "EFMUSB/BLUE/LED", LOW);
  EFMGREENLED.begin(HUB, GREEN_LED, "EFMUSB/GREEN/LED", LOW);
  EFMCPUVDD.begin(HUB, "EFMUSB/CPU/VDD", 50);
  EFMCPUTMP.begin(HUB, "EFMUSB/CPU/TEMP", 50, 50);

  HABLTS.begin(HUB, LTSENS_PIN, "HAB/LTSENSOR", 5, 400);
  HABS1.begin(HUB, SW1_PIN, "HAB/SW1", 20);
  HABS2.begin(HUB, SW2_PIN, "HAB/SW2", 20);
  HABREED.begin(HUB, REEDSW_PIN, "HAB/REED", 20);
  HABLED.begin(HUB, HABLED_PIN, "HAB/LED", HIGH);
  HABBUZZ.begin(HUB, BUZZER_PIN, "HAB/BUZZER");
  HABPOT.begin(HUB, POT_PIN, "HAB/POT", 50);
}

void loop()
{
  HUB.update();
}