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

        ///@brief Constructor that initializes a few internal variables.
        ///@return MqttPort object
        MqttPort();

        ///@brief No-op function that is implemented by the derived class. 
        ///Derived class should handle receiving data from it's external communication method
        ///@return Should return 1 if a message was received, else 0 
        virtual int8_t decode(void);   

        ///@brief No-op function that is implemented by the derived class.
        ///Derived class should handle sending the subscription for the module to the other end of it's port.
        ///@param [in] mod Name of the module to subscribe to messages for.
        virtual void  subscribe(const char* mod);

        ///@brief No-op function that is implemented by the derived class.
        ///Derived class should send a normal MQTT message to the other end of it's port.
        ///@param [in] topic Topic to include in the MQTT message.
        ///@param [in] payload Payload to include in the MQTT message.
        virtual void publishMessage(const char* topic, const char* payload);

        ///@brief No-op function that is implemented by the derived class.
        ///Slightly different than publish since it needs to handle subscriptions correctly as well.
        ///@param [in] topic Topic to include in the MQTT message.
        ///@param [in] payload Payload to include in the MQTT message.
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
  
  ///@brief Constructor that initializes some internal variables
  ///@return MqttSerialPort object
  MqttSerialPort();
  
  ///@brief Connect to the MqttHub and setup which Serial port to use with this object.
  ///@param [in] hub MqttHub to connect to
  ///@param [in] serial Serial port to use as the port
  virtual void begin(MqttHub &hub, UARTClass &serial);
  
  ///@brief Process input from the serial port
  ///@return Returns 2 if it found a valid packet, else return 0.
  virtual int8_t decode(void);
  
  ///@brief Send a subscribe method over the serial port.
  ///@param [in] mod Module to subscribe to updates from.
  virtual void  subscribe(const char* mod);
  
   ///@brief Send an Mqtt message that is formatted as {"TOP":"topic","PLD":"payload"}
   ///@param [in] topic Topic to use for the message
   ///@param [in] payload Payload to use for the message
   virtual void publishMessage(const char* topic, const char* payload);
   
   ///@brief Forward an Mqtt message. In the case of a Serial port this is the same as publishMessage()
   ///@param [in] topic Topic to use for the message 
   ///@param [in] payload Payload to use for the message
   virtual void forwardMessage(const char* topic, const char* payload);
   
  protected:
  
     ///@brief Adds a character to the line buffer and checks to see if it is a full packet yet.
     ///@param [in] c Character to add.
     ///@return 2 if it found a packet else 0
     int8_t getInputString(char c);
     
     ///@brief Once a full packet has been found parse out the topic and payload into separate buffers.
     ///@return 2 if it found a valid packet else 0
     int8_t parseLine(void);
     
     ///@brief Adds the character to the line buffer.
     ///@param [in] c character to add
      void addCharToInputString(char c);
     
     ///@brief Parses a quote wrapped string out of a string. Only gets the first Quote wrapped string.
     ///@param [in] str String to parse
     ///@param [in] item Buffer to return the parsed out string into.
     ///@param [in] tok_length length of the string that was parsed out
     ///@return 1 if a valid Quoted string was found and 0 if not. 
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



