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
/* Example for how to setup the MQTT client for the Garage Door Controller Engimusing board
 *  This board is intended to be connected up to a garage door opener to allow for remote
 *  control of the garage door. Also provides temperature and CO2 detector for the garage.
 *  See http://www.engimusing.com/collections/project-kits/products/garage-1 for more 
 *  information about the board.
 */

//Include the EFM32COMM to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <Mq7Module.h>
#include <Noa1212Module.h>

#include <Wire.h>
/*
  EFMZG108 Commands:
  {"TOP":"GDOOR/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"GDOOR/BOARD/TMP102/DEC_C","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The EFM32COMM classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever COMM.update() is called.
OnOffCtlModule LEDCtrl_RED;
OnOffCtlModule LEDCtrl_GREEN;
OnOffCtlModule LEDCtrl_BLUE;

Tmp102Module TMP102;

DigitalQre1113SwitchModule ReflectiveSensorSwitch0;
DigitalQre1113SwitchModule ReflectiveSensorSwitch1;
DigitalQre1113SwitchModule ReflectiveSensorSwitch2;

Mq7Module Mq7;

Noa1212Module Noa1212;

OnOffCtlModule DcRelay1;
OnOffCtlModule DcRelay2;

//monitor the monitor lines to know the state of sensors attached to the MON wires
DetectorSwitchModule Monitor1;
DetectorSwitchModule Monitor2;
DetectorSwitchModule Monitor3;
DetectorSwitchModule Monitor4;
DetectorSwitchModule Monitor5;
DetectorSwitchModule Monitor6;


void setup()
{
  serialPort.begin(HUB, Serial1);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl_RED.begin(HUB, ledId[0], "GDOOR/BOARD/LED_RED", LOW);
  LEDCtrl_GREEN.begin(HUB, ledId[1], "GDOOR/BOARD/LED_GREEN", LOW);
  LEDCtrl_BLUE.begin(HUB, ledId[2], "GDOOR/BOARD/LED_BLUE", LOW);

  //Initialize the tmp control class which will send the 
  // temperature over MQTT every 10 seconds
  TMP102.begin(HUB, "GDOOR/BOARD/TMP102", &Wire0, -1, 10000);

  //On the side of the garage door board with less on it there are
  // three QRE1113 reflectivity sensors. These work well as proximity sensor
  // buttons.
  ReflectiveSensorSwitch0.begin(HUB, 30, "GDOOR/BOARD/QRE0", 10, 1);
  ReflectiveSensorSwitch1.begin(HUB, 31, "GDOOR/BOARD/QRE1", 10, 3);
  ReflectiveSensorSwitch2.begin(HUB, 15, "GDOOR/BOARD/QRE2", 10, 45);

  //The large round orange object on the side of the garage door board with more on it
  // is the MQ7 CO2 detector.
  Mq7.begin(HUB, "GDOOR/BOARD/MQ7", 48, 33, 10000);
  
  //Light sensor that is on the front of the board.
  Noa1212.begin(HUB, "GDOOR/BOARD/NOA1212", 16, 25, 24, 32, Noa1212Module::MEDIUM_GAIN, 10000);
  
  //onoff controls for the dcrelays. These are auto turned off in the loop() after a set amount of time
  DcRelay1.begin(HUB, 5, "GDOOR/BOARD/DCRELAY1", LOW);
  DcRelay2.begin(HUB, 6, "GDOOR/BOARD/DCRELAY2", LOW);

  //Connects up the 6 monitor wires to the MQTTHub
  Monitor1.begin(HUB, 42, "GDOOR/BOARD/MON1", 10);
  Monitor2.begin(HUB, 41, "GDOOR/BOARD/MON2", 10);
  Monitor3.begin(HUB, 14, "GDOOR/BOARD/MON3", 10);
  Monitor4.begin(HUB, 43, "GDOOR/BOARD/MON4", 10);
  Monitor5.begin(HUB, 47, "GDOOR/BOARD/MON5", 10);
  Monitor6.begin(HUB, 13, "GDOOR/BOARD/MON6", 10);
    
}

int dcRelay1TurnOnTime = -1;
int dcRelay2TurnOnTime = -1;
int dcRelayOnTime = 1000;

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

  //Turn dcrelay off after a set amount of time so that the garage door is opened/closed
  if(DcRelay1.pinState() > 0)
  {
        if(dcRelay1TurnOnTime == -1)
        {
            dcRelay1TurnOnTime = millis();
        }
        if(dcRelay1TurnOnTime + dcRelayOnTime < millis())
        {
            dcRelay1TurnOnTime = -1;
            DcRelay1.setPinState(LOW);
        }
  }
  
  //Turn dcrelay off after a set amount of time so that the garage door is opened/closed
  if(DcRelay2.pinState() > 0)
  {
        if(dcRelay2TurnOnTime == -1)
        {
            dcRelay2TurnOnTime = millis();
        }
        if(dcRelay2TurnOnTime + dcRelayOnTime < millis())
        {
            dcRelay2TurnOnTime = -1;
            DcRelay2.setPinState(LOW);
        }
  }
  
1
  
}