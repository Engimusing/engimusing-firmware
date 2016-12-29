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

#pragma once

#include "Arduino.h"

#include "MqttHub.h"

class MqttPort
{
   friend class MqttHub;
 public:
  char* myTopic;
  char* myPayload;
  MqttPort();
  
  virtual int8_t decode(void);   

  virtual void  subscribe(const char* mod);
  
  virtual void publishMessage(const char* topic, const char* payload);
  
  //slightly different than publish since it needs to handle subscriptions correctly as well.
  virtual void forwardMessage(const char* topic, const char* payload);
  
 protected: 
  
  MqttPort* myNextPort;
  
};

class MqttSerialPort : public MqttPort
{
 public:
 
 enum giState {
  Idle,  
  GettingLine,
};
  
  MqttSerialPort();
  
  virtual void begin(MqttHub &hub, UARTClass &serial);
  
  virtual int8_t decode(void);
  
  virtual void  subscribe(const char* mod);
  
  virtual void publishMessage(const char* topic, const char* payload);
   
  virtual void forwardMessage(const char* topic, const char* payload);
   
  protected:
  
     int8_t getInputString(char);
     int8_t parseLine(void);
     void addCharToInputString(char c);
     int8_t getToken(char* str, char* item, char tok_length);
     
  protected:
  
     char myTopicBuffer[MODULE_STRING_LENGTH];
     char myPayloadBuffer[ITEM_PAYLOAD_LENGTH];
  
     char myInputString[COMM_STRING_LENGTH+3];
     
     uint8_t myIsCnt;
     uint8_t myCharCnt;
     giState myState;
     
     UARTClass *mySerial;
     
};

class SPIClass;

struct Cc3000PinConfig
{
   uint8_t csPin;
   uint8_t irqPin; 
   uint8_t vbatPin;
   SPIClass& spi;
};



