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
/* Example for how to setup the MQTT client for the CPC1002N DC SSR DF 11 board connected to the ZGUSB Engimusing board
 *  There are is two CPC1002N devices on the DF 11 board and a 3 color LED on the ZGUSB 
 *  See https://www.engimusing.com/products/ssr_dc-2 for more information about the board.
 */

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

/*
  EFMZG108 Commands:
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMZGUSB/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMZGUSB/BOARD/DC0/CTL","PLD":"ON"}
  {"TOP":"EFMZGUSB/BOARD/DC0/CTL","PLD":"OFF"}
  {"TOP":"EFMZGUSB/BOARD/DC0/CTL","PLD":"STATUS"}

  {"TOP":"EFMZGUSB/BOARD/DC1/CTL","PLD":"ON"}
  {"TOP":"EFMZGUSB/BOARD/DC1/CTL","PLD":"OFF"}
  {"TOP":"EFMZGUSB/BOARD/DC1/CTL","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

OnOffCtlModule DC0Ctrl;
OnOffCtlModule DC1Ctrl;

void setup()
{
  serialPort.begin(HUB, Serial);
  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFMZG108/BOARD/LED", HIGH);

  //Initialize the on off controllers for the DC relays
  DC0Ctrl.begin(HUB, 10, "EFMZG108/BOARD/DC0", LOW);
  DC1Ctrl.begin(HUB, 6, "EFMZG108/BOARD/DC1", LOW);

  //set the default state for the DC relays to be off/open.
  DC0Ctrl.setPinState(LOW);
  DC1Ctrl.setPinState(LOW);
}

//Part of light on off example
//int lastMillisOn = 0;
//int lastMillisOff = 1000;

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

  /*
  //example of how to turn on and off a light using the OnOffCtlModule
  //status of the pin will be sent to the MQTT broker.
  if(millis() > lastMillisOff + 2000)
  {
    LEDCtrl.setPinState(LOW);
    lastMillisOff = millis();
  }
  if(millis() > lastMillisOn + 2000)
  {
    LEDCtrl.setPinState(HIGH);
    lastMillisOn = millis();
  }
  */

  /*
   * example of how to control the LED using one of the reed switches
   */
   /*
   //If the led is not in the same state as the swich then 
   // set it to the same as the swich. This check avoids
   // setting the led state every time through the loop
   if(LEDCtrl.pinState() != ReedSwitch0.switchState())
   {
      LEDCtrl.setPinState(ReedSwitch0.switchState());
   }*/
  
  
}
