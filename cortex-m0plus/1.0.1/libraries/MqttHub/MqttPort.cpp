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

#include <Adafruit_CC3000.h>
#include "Adafruit_MQTT.h"

#include "CC3000Helper.h"

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

//define up to 4 default cc3000 pin configurations
#if CC3000_INTERFACES_COUNT > 0
Cc3000PinConfig cc3000_0_pinConfig = {
   PIN_CC3000_0_CS,
   PIN_CC3000_0_IRQ,
   PIN_CC3000_0_VBAT,
   CC3000_0_SPI
};
#endif

#if CC3000_INTERFACES_COUNT > 1
Cc3000PinConfig cc3000_1_pinConfig = {
   PIN_CC3000_1_CS,
   PIN_CC3000_1_IRQ,
   PIN_CC3000_1_VBAT,
   CC3000_1_SPI
};
#endif

#if CC3000_INTERFACES_COUNT > 2
Cc3000PinConfig cc3000_2_pinConfig = {
   PIN_CC3000_2_CS,
   PIN_CC3000_2_IRQ,
   PIN_CC3000_2_VBAT,
   CC3000_2_SPI
};
#endif

#if CC3000_INTERFACES_COUNT > 3
Cc3000PinConfig cc3000_3_pinConfig = {
   PIN_CC3000_3_CS,
   PIN_CC3000_3_IRQ,
   PIN_CC3000_3_VBAT,
   CC3000_3_SPI
};
#endif

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MqttCC3000Port::MQTT_connect() {
  int8_t ret;
  
  // Stop if already connected.
  if (myMqttCc3000.connected()) {
    return;
  }

  //Serial.println("Connecting to MQTT... ");

  while ((ret = myMqttCc3000.connect()) != 0) { // connect will return 0 for connected
       myConnectFails++;
       
       //too many failures lets reboot the EFM
       //probably worth tracking down why the connection cannot
       // reconnect but for now this is probably good enough.
       if(myConnectFails >= myMaxConnectFails)
       {
          /* Write to the Application Interrupt/Reset Command Register to reset
         * the EFM32. See section 9.3.7 in the reference manual. */
         SCB->AIRCR = 0x05FA0004;
       }
       //Serial.println(myMqttCc3000.connectErrorString(ret));
       if (ret < 0)
            CC3000connect(myCc3000, myWlanConfig.ssid, myWlanConfig.pass, myWlanConfig.security);  // y0w, lets connect to wifi again
       //mySerial->println("Retrying MQTT connection in 5 seconds...");
       myMqttCc3000.disconnect();
       delay(5000);  // wait 5 seconds
  }
   myConnectFails = 0;
}


MqttCC3000Port::MqttCC3000Port(Cc3000PinConfig &pinConfig, 
                                                 Cc3000WlanConfig &wlanConfig,
                                                 MqttServerConfig &mqttServerConfig) 
   : MqttPort()
   , myPinConfig(pinConfig)
   , myWlanConfig(wlanConfig)
   , myMqttServerConfig(mqttServerConfig)
   , myCc3000(pinConfig.csPin, pinConfig.irqPin, pinConfig.vbatPin, pinConfig.spi)
   , myMqttCc3000(&myCc3000, mqttServerConfig.server, mqttServerConfig.port, mqttServerConfig.cid, mqttServerConfig.user, mqttServerConfig.pass)
   , myPingTime(0)
   , myConnectFails(0)
   , myMaxConnectFails(3)
{
	
}

void MqttCC3000Port::begin(MqttHub &hub)
{
   hub.registerPort(this);
   
   // Initialise the CC3000 module
   myCc3000.begin();
  
   while (! CC3000connect(myCc3000, myWlanConfig.ssid, myWlanConfig.pass, myWlanConfig.security)) {
      delay(1000);
   }

   MQTT_connect();
}

void MqttCC3000Port::subscribe(const char* mod)
{
	char buf[MODULE_STRING_LENGTH];
	int len = strlen(mod) ;
	if(len > MODULE_STRING_LENGTH - 1)
	{
		len = MODULE_STRING_LENGTH - 1;
	}
	
	memmove(&buf[0], mod, len);
	
	if(len < MODULE_STRING_LENGTH - 3)
	{
		memmove(&buf[len], "/#", 2);
		len += 2;
	}
	
	buf[len] = '\0';
	
	myMqttCc3000.subscribe(&buf[0], 0);
	
}

int8_t MqttCC3000Port::decode(void)
{
   
  //Serial.println("DECODE");
   
  MQTT_connect();

  myMqttCc3000.processPackets(1);

  if(millis() > myPingTime + 10000)
  {
      //Serial.println("Ping");
      myPingTime = millis();
      if(!myMqttCc3000.ping())
      {
         //Ping failed so we are no longer connected to the 
         // MQTT server. We should attempt a reconnect.
         //Serial.println("Ping Failed!!!");
         myMqttCc3000.disconnectServer();
         return 0;
      }
  }

  
  Adafruit_MQTT_Subscribe *subscription;
  if((subscription = myMqttCc3000.readSubscription()))
  {
	  myTopic = subscription->lastTopic;
	  myPayload = (char*)subscription->lastread;
	  return 1;
  }
  //Serial.println("DECODE END");
  return 0;
}

void MqttCC3000Port::publishMessage(const char* topic, const char* payload)
{
	myMqttCc3000.publish(topic, payload, 0);
}

void MqttCC3000Port::forwardMessage(const char* topic, const char* payload)
{
   if(payload[0] == 'S' &&
      payload[1] == 'U' &&
      payload[2] == 'B' &&
      payload[3] == '\0')
   {
      myMqttCc3000.subscribe(topic, 0);
   }else
   {
      myMqttCc3000.publish(topic, payload, 0);      
   }   
}




