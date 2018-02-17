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

#include "MqttPort.h"
#include "efm_lib/analog.h"

#include <Arduino.h>
#include <Wire.h>

extern UARTClass Serial;
extern UARTClass Serial1;
extern INTRClass INTR;
extern AnalogLP  Analog;

// --------------------------------- Basic MQTT Port Base Class -------------------------

MqttPort::MqttPort()
{
   myTopic   = 0;
   myPayload = 0;

   myNextPort = 0;
  
}

void MqttPort::subscribe(const char* mod)
{
	//Implement in Derrived Class
}

void MqttPort::publishMessage(const char* topic, const char* payload)
{
   //Implement in Derrived Class
}

void MqttPort::forwardMessage(const char* topic, const char* payload)
{
   //Implement in Derrived Class
}

int8_t MqttPort::decode()
{
	//implement in derrived class.
}

// --------------------------------- Basic MQTT Serial Port Class -------------------------

MqttSerialPort::MqttSerialPort() : MqttPort()
{
  myIsCnt = 0;
  myState = Idle;
  mySerial = 0;
  myInputString[0]  = '\0';
  
   myTopicBuffer[0]= '\0';
   myPayloadBuffer[0]= '\0';
   myTopic   = &myTopicBuffer[0];
   myPayload = &myPayloadBuffer[0];

}

void MqttSerialPort::begin(MqttHub &hub, UARTClass &serial)
{
   
   hub.registerPort(this);
   mySerial = &serial;
   
}

void MqttSerialPort::subscribe(const char* mod)
{
	mySerial->print("{\"TOP\":\"");
	mySerial->print((const char*)mod);
	mySerial->print("/#\",\"PLD\":\"SUB\"}\r\n");
}


void MqttSerialPort::publishMessage(const char* topic, const char* payload)
{
	mySerial->print("{\"TOP\":\"");
	mySerial->print(topic);
	mySerial->print("\",\"PLD\":\"");
	mySerial->print(payload);
	mySerial->print("\"}\r\n");
}

void MqttSerialPort::forwardMessage(const char* topic, const char* payload)
{
   //Serial port doesn't need to handle subscriptions differently.
   publishMessage(topic, payload);
}

int8_t MqttSerialPort::decode(void)
{
  int remainingReads = 1000;
  while (mySerial->available() && remainingReads > 0) {
    char c = (char)mySerial->read(); // get the new byte:
    if(isgraph(c)) {
      uint8_t r = getInputString(c);
      if(r > 0)
      {
         return r;
      }
    } else {
      return 0;
    }
    remainingReads--;
  }
  return 0;
}

int8_t MqttSerialPort::getInputString(char c)
{
  if(c == '{') {
    myState = GettingLine;
    myIsCnt = 0;
    addCharToInputString(c);
    return 0;
  }
  else if(myState != Idle) {
    if(c == '}') {
      myState = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
	  
      int8_t r = parseLine();
      myInputString[0]  = '\0';
      myIsCnt = 0;
      return r;
    } 
    else {
      addCharToInputString(c);
      return 0;
    }
  }
  return 0;
}

void MqttSerialPort::addCharToInputString(char c)
{
  myInputString[myIsCnt++] = c;
  if(myIsCnt >= COMM_STRING_LENGTH) {
    myIsCnt = 0;
    myState = Idle;
    myInputString[0] = '\0';
  }
}

int8_t MqttSerialPort::parseLine(void)
{
  static uint8_t debug = 0;

  myTopicBuffer[0]   = '\0';
  myPayloadBuffer[0] = '\0';
  bool foundTop  = false;
  bool foundPld = false;
  int8_t r = 0;

  for(myIsCnt = 0; myInputString[myIsCnt] != '\0'; myIsCnt++) {
    char* c = &myInputString[myIsCnt];
    if( ((c[0] == '{') || (c[0] == ',')) && (c[1] == '\"')) {
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	r = getToken(&c[5], myTopicBuffer, MODULE_STRING_LENGTH);
   foundTop = true;
	   }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	r += getToken(&c[5], myPayloadBuffer, ITEM_PAYLOAD_LENGTH);
   foundPld = true;
	  }
    }
  }
  
  if(foundPld and foundTop)
  {
      return r;   
  }else
  {
     return 0;
  }
  
}

int8_t MqttSerialPort::getToken(char* str, char* item, char tok_length)
{
  uint8_t i;

  if((str[0] == '\"') && (str[1] == ':') && (str[2] == '\"')) {
    for(i = 3; (i < tok_length) && (str[i] != '\"') && (str[i] != '\0'); i++) {
      item[i-3] = str[i];
    }
    item[i-3] = '\0';
    return 1;
  } else {
    return 0;
  }
}



