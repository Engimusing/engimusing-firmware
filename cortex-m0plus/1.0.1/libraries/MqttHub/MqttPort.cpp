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

int8_t MqttSerialPort::decode(void)
{
  if (mySerial->available()) {
    char c = (char)mySerial->read(); // get the new byte:
    if(isgraph(c)) {
      return getInputString(c);
    } else {
      return 0;
    }
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
  } else if(myState != Idle) {
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
    } else {
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
  }
}

int8_t MqttSerialPort::parseLine(void)
{
  static uint8_t debug = 0;

  myTopicBuffer[0]   = '\0';
  myPayloadBuffer[0] = '\0';

  int8_t r = 0;

  for(myIsCnt = 0; myInputString[myIsCnt] != '\0'; myIsCnt++) {
    char* c = &myInputString[myIsCnt];
    if( ((c[0] == '{') || (c[0] == ',')) && (c[1] == '\"')) {
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	r = getToken(&c[5], myTopicBuffer, MODULE_STRING_LENGTH);
	   }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	r += getToken(&c[5], myPayloadBuffer, ITEM_PAYLOAD_LENGTH);
	  }
    }
  }
  return r;
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


#if 0
/*************************** CC3000 Pins ***********************************/

//PINS FOR WG840
//#define ADAFRUIT_CC3000_IRQ   33  // MUST be an interrupt pin!
//#define ADAFRUIT_CC3000_VBAT  46  // VBAT & CS can be any digital pins.
//#define ADAFRUIT_CC3000_CS    12

// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
///


//PINS for WG842
#define ADAFRUIT_CC3000_IRQ   60  // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT  52  // VBAT & CS can be any digital pins.
#define ADAFRUIT_CC3000_CS    12
///

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SSID"        // cannot be longer than 32 characters!
#define WLAN_PASS       "PASSWORD"
#define WLAN_SECURITY   WLAN_SEC_WPA2  // Can be: WLAN_SEC_UNSEC, WLAN_SEC_WEP,
                                       //         WLAN_SEC_WPA or WLAN_SEC_WPA2

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.1.14"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "username"
#define AIO_KEY         "username"

/************ Global State (you don't need to change this!) ******************/

// Setup the main CC3000 class, just like a normal CC3000 sketch.
//Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT);

// Setup the CC3000 MQTT class by passing in the CC3000 class and MQTT server and login details.
//Adafruit_MQTT_CC3000 mqtt(&cc3000, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

#endif

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MqttCC3000Port::MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (myMqttCc3000.connected()) {
    return;
  }

  //mySerial->print("Connecting to MQTT... ");

  while ((ret = myMqttCc3000.connect()) != 0) { // connect will return 0 for connected
       //mySerial->println(mqtt.connectErrorString(ret));
       if (ret < 0)
            CC3000connect(myCc3000, myWlanConfig.ssid, myWlanConfig.pass, myWlanConfig.security);  // y0w, lets connect to wifi again
       //mySerial->println("Retrying MQTT connection in 5 seconds...");
       myMqttCc3000.disconnect();
       delay(5000);  // wait 5 seconds
  }

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
  MQTT_connect();

  myMqttCc3000.processPackets(10);

  if(millis() > myPingTime + 10000)
  {
      myPingTime = millis();
      myMqttCc3000.ping();
  }

  
  Adafruit_MQTT_Subscribe *subscription;
  if((subscription = myMqttCc3000.readSubscription()))
  {
	  myTopic = subscription->lastTopic;
	  myPayload = (char*)subscription->lastread;
	  return 1;
  }
  
  return 0;
}

void MqttCC3000Port::publishMessage(const char* topic, const char* payload)
{
	myMqttCc3000.publish(topic, payload, 0);
}





