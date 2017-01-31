
#include <Wire.h>

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

/*
 * Serial port MQTT message switch. All MQTT messages are sent out
 *  on all the other 4 serial ports.
 */

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
