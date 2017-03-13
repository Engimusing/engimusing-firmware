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
/*
 * Serial port MQTT message switch. All MQTT messages are sent out
 *  on all the other 4 serial ports.
 */

#if !defined(EFM32G232)
#error Incorrect Board Selected! Please select Engimusing EFM32G232 from the Tools->Board: menu.
#endif

#include <Wire.h>

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>


MqttHub HUB;

MqttSerialPort SerialPort;
MqttSerialPort Serial1Port;
MqttSerialPort Serial2Port;
MqttSerialPort Serial3Port;
MqttSerialPort Serial4Port;

void setup()
{
  //initialize the 5 ports on the HUB
  SerialPort.begin(HUB, Serial);
  Serial1Port.begin(HUB, Serial1);
  Serial2Port.begin(HUB, Serial2);
  Serial3Port.begin(HUB, Serial3);
  Serial4Port.begin(HUB, Serial4);
}

void loop()
{
  HUB.update();
}
