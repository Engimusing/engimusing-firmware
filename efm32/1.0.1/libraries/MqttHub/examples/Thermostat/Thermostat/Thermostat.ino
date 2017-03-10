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
/* Example for how to setup the MQTT client for the Thermastat Controller Engimusing board.
 *  This board is intended to replace a thermostat to allow for remote
 *  control of the AC and/or furnace. Also provides a temperature sensor.
 *  See https://www.engimusing.com/collections/project-kits/products/thermostat-2 for more 
 *  information about the board.
 */

#if !defined(EFM32WG842)
#error Incorrect Board Selected! Please select Engimusing EFM32WG842 from the Tools->Board: menu.
#endif
// Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttCC3000Port.h>
#include <MqttModule.h>

#include <Noa1212Module.h>

#include <TMP102Device.h>

#include <Wire.h>
/*
  THERM Commands:
  {"TOP":"THERM/BOARD/LED_RED/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_RED/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_RED/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/LED_GREEN/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_GREEN/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_GREEN/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/LED_BLUE/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_BLUE/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_BLUE/CTL","PLD":"STATUS"}

  {"TOP":"THERM/BOARD/LED_COOL/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_COOL/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_COOL/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/LED_HEAT/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_HEAT/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_HEAT/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/LED_FAN/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/LED_FAN/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/LED_FAN/CTL","PLD":"STATUS"}

  {"TOP":"THERM/BOARD/AQH3213_COOL/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/AQH3213_COOL/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/AQH3213_COOL/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/AQH3213_HEAT/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/AQH3213_HEAT/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/AQH3213_HEAT/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/AQH3213_FAN/CTL","PLD":"ON"}
  {"TOP":"THERM/BOARD/AQH3213_FAN/CTL","PLD":"OFF"}
  {"TOP":"THERM/BOARD/AQH3213_FAN/CTL","PLD":"STATUS"}
  
  {"TOP":"THERM/BOARD/TMP102","PLD":"STATUS"}
  
*/

MqttHub HUB;

MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl_RED;
OnOffCtlModule LEDCtrl_GREEN;
OnOffCtlModule LEDCtrl_BLUE;

OnOffCtlModule LEDCtrl_COOL;
OnOffCtlModule LEDCtrl_HEAT;
OnOffCtlModule LEDCtrl_FAN;

OnOffCtlModule AQH3213_COOL;
OnOffCtlModule AQH3213_HEAT;
OnOffCtlModule AQH3213_FAN;

TMP102Device TMP102;
SimpleMqttModule TMP102MqttMod;

DigitalQre1113SwitchModule ReflectiveSensorSwitch0;
DigitalQre1113SwitchModule ReflectiveSensorSwitch1;
DigitalQre1113SwitchModule ReflectiveSensorSwitch2;


void setup()
{
  //connect the Serial port up to the mqtt hub
  serialPort.begin(HUB, Serial2);
  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl_RED.begin(HUB, ledId[0], "THERM/BOARD/LED_RED", LOW);
  LEDCtrl_GREEN.begin(HUB, ledId[1], "THERM/BOARD/LED_GREEN", LOW);
  LEDCtrl_BLUE.begin(HUB, ledId[2], "THERM/BOARD/LED_BLUE", LOW);

  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl_COOL.begin(HUB, 13, "THERM/BOARD/LED_COOL", HIGH);
  LEDCtrl_HEAT.begin(HUB, 33, "THERM/BOARD/LED_HEAT", HIGH);
  LEDCtrl_FAN.begin(HUB, 16, "THERM/BOARD/LED_FAN", HIGH);

  //Initialize the on off control to connect it to
  // the LED that is on the board
  AQH3213_COOL.begin(HUB, 36, "THERM/BOARD/AQH3213_COOL", LOW);
  AQH3213_HEAT.begin(HUB, 32, "THERM/BOARD/AQH3213_HEAT", LOW);
  AQH3213_FAN.begin(HUB, 41, "THERM/BOARD/AQH3213_FAN", LOW);
  
  //Initialize the tmp control class which will send the 
  // temperature over MQTT every 10 seconds
  TMP102.begin(&Wire0, -1, true);
  TMP102MqttMod.begin(HUB, &TMP102, "THERM/BOARD/TMP102", 10000);

  //On the side of the garage door board with less on it there are
  // three QRE1113 reflectivity sensors. These work well as proximity sensor
  // buttons.
  // WIFI loops slower so we need to have a lower bounce value
  ReflectiveSensorSwitch0.begin(HUB, 30, "THERM/BOARD/QRE0", 3, 1); 
  ReflectiveSensorSwitch1.begin(HUB, 31, "THERM/BOARD/QRE1", 3, 3);
  ReflectiveSensorSwitch2.begin(HUB, 15, "THERM/BOARD/QRE2", 3, 45);
    
}

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

  
}



