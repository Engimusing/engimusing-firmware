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
 *  with the optional CC3000 DF11 board connected.
 *  This board is intended to be connected up to a garage door opener to allow for remote
 *  control of the garage door. Also provides temperature and CO detector for the garage.
 *  See http://www.engimusing.com/collections/project-kits/products/garage-1 for more 
 *  information about the board.
 */
 
#if !defined(EFM32WG842)
#error Incorrect Board Selected! Please select Engimusing EFM32WG842 from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttCC3000Port.h>
#include <MqttModule.h>

#include <MQ7Device.h>
#include <NOA1212Device.h>

#include <TMP102Device.h>

#include <QRE1113Device.h>

#include <Wire.h>
/*
  GDOOR Commands:
  {"TOP":"GDOOR/BOARD/LED_RED/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/LED_RED/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/LED_RED/CTL","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/LED_GREEN/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/LED_GREEN/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/LED_GREEN/CTL","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/LED_BLUE/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/LED_BLUE/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/LED_BLUE/CTL","PLD":"STATUS"}

  {"TOP":"GDOOR/BOARD/TMP102","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/MQ7","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/NOA1212","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/DCRELAY1/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/DCRELAY1/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/DCRELAY1/CTL","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/DCRELAY2/CTL","PLD":"ON"}
  {"TOP":"GDOOR/BOARD/DCRELAY2/CTL","PLD":"OFF"}
  {"TOP":"GDOOR/BOARD/DCRELAY2/CTL","PLD":"STATUS"}
  
  {"TOP":"GDOOR/BOARD/MON1","PLD":"STATUS"}
  {"TOP":"GDOOR/BOARD/MON2","PLD":"STATUS"}
  {"TOP":"GDOOR/BOARD/MON3","PLD":"STATUS"}
  {"TOP":"GDOOR/BOARD/MON4","PLD":"STATUS"}
  {"TOP":"GDOOR/BOARD/MON5","PLD":"STATUS"}
  {"TOP":"GDOOR/BOARD/MON6","PLD":"STATUS"}
  
*/

MqttHub HUB;

Cc3000WlanConfig wlanConfig = {
  "SSID", //ssid to connect to
  "password", // passcode for the wlan
  WLAN_SEC_WPA2 //security type for the wlan
};

MqttServerConfig mqttServerConfig = {
  "192.168.1.20", //mqtt server address to connect to
  1883, //mqtt port to connect to 
  "EFM32WG842", //name for this device to send to the server
  "username", // username to access the mqtt server
  "password" // password to access the mqtt server
};

// pass the three configuration structs 
//to the wifi port in order to configure it.
MqttCC3000Port wifiPort(
  cc3000_0_pinConfig, //Configuration defined based on the device
  wlanConfig, //defined above
  mqttServerConfig //defined above
  );


//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl_RED;
OnOffCtlModule LEDCtrl_GREEN;
OnOffCtlModule LEDCtrl_BLUE;

TMP102Device TMP102;
SimpleMqttModule TMP102MqttMod;

QRE1113Device ReflectiveSensorSwitch0;
SimpleMqttModule ReflectiveSensorSwitch0_MqttMod;
QRE1113Device ReflectiveSensorSwitch1;
SimpleMqttModule ReflectiveSensorSwitch1_MqttMod;
QRE1113Device ReflectiveSensorSwitch2;
SimpleMqttModule ReflectiveSensorSwitch2_MqttMod;


MQ7Device Mq7;
SimpleMqttModule Mq7MqttMod;

NOA1212Device Noa1212;
SimpleMqttModule Noa1212MqttMod;

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
  //connect the wifi port up to the mqtt hub
  wifiPort.begin(HUB);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl_RED.begin(HUB, ledId[0], "GDOOR/BOARD/LED_RED", LOW);
  LEDCtrl_GREEN.begin(HUB, ledId[1], "GDOOR/BOARD/LED_GREEN", LOW);
  LEDCtrl_BLUE.begin(HUB, ledId[2], "GDOOR/BOARD/LED_BLUE", LOW);

  //Initialize the tmp control class which will send the 
  // temperature over MQTT every 10 seconds
  TMP102.begin(Wire0, -1, true);
  TMP102MqttMod.begin(HUB, TMP102, "EFMZG108/BOARD/TMP102", 10000);
  
  //On the side of the garage door board with less on it there are
  // three QRE1113 reflectivity sensors. These work well as proximity sensor
  // buttons.
  // WIFI loops slower so we need to have a lower bounce value
  ReflectiveSensorSwitch0.begin(1, 30, 3);
  ReflectiveSensorSwitch0_MqttMod.begin(HUB, ReflectiveSensorSwitch0, "GDOOR/BOARD/QRE0", 10000);
  ReflectiveSensorSwitch1.begin(3, 31, 3);
  ReflectiveSensorSwitch1_MqttMod.begin(HUB, ReflectiveSensorSwitch1, "GDOOR/BOARD/QRE1", 10000);
  ReflectiveSensorSwitch2.begin(45, 15, 3);
  ReflectiveSensorSwitch2_MqttMod.begin(HUB, ReflectiveSensorSwitch2, "GDOOR/BOARD/QRE2", 10000);

  //The large round orange object on the side of the garage door board with more on it
  // is the MQ7 CO detector.
  Mq7.begin(48, 33);
  Mq7MqttMod.begin(HUB, Mq7, "GDOOR/BOARD/MQ7", 10000);
  
  //Light sensor that is on the front of the board.
  Noa1212.begin(16, 25, 24, 32, NOA1212Device::MEDIUM_GAIN, 100);
  Noa1212MqttMod.begin(HUB, Noa1212, "GDOOR/BOARD/NOA1212", 10000);
  
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
}


