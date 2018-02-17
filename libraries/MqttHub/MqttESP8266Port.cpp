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


#include "MqttESP8266Port.h"

#if SPI_INTERFACES_COUNT > 0 && ESP8266_INTERFACES_COUNT > 0

#include <Engimusing_ESP8266.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_ESP8266.h"

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MqttESP8266Port::MQTT_connect() {
  int8_t ret;
 bool connectedToAp = true;
 if(!myMqttEsp8266.connectedToAp())
 {
    connectedToAp = myMqttEsp8266.connectToAp(myWlanConfig.ssid, myWlanConfig.pass); 
 }

 bool connectedToServer = true;
 if(connectedToAp && !myMqttEsp8266.connected())
 {
     connectedToServer = myMqttEsp8266.connect();
 }
    
#if 0 //CC3000 multiple retry to connect code.
  // Stop if already connected.
  if (myMqttEsp8266.connected()) {
    return;
  }

  //Serial.println("Connecting to MQTT... ");

  while ((ret = myMqttEsp8266.connectToAp(myWlanConfig.ssid, myWlanConfig.pass)) != 0) { // connect will return 0 for connected
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
       //Serial.println(myMqttEsp8266.connectErrorString(ret));
       if (ret < 0)
            myMqttEsp8266.connectToAp(myWlanConfig.ssid, myWlanConfig.pass);  // y0w, lets connect to wifi again
       //myDebugSerial->println("Retrying MQTT connection in 5 seconds...");
       myMqttEsp8266.disconnect();
       delay(5000);  // wait 5 seconds
  }
   myConnectFails = 0;
#endif
}


MqttESP8266Port::MqttESP8266Port(Esp8266Config &pinConfig, 
                                                 WlanConfig &wlanConfig,
                                                 MqttServerConfig &mqttServerConfig,
                                                 UARTClass &serial
                                                 ) 
   : MqttPort()
   , myPinConfig(pinConfig)
   , myWlanConfig(wlanConfig)
   , myMqttServerConfig(mqttServerConfig)
   , myEsp8266(pinConfig, &serial)
   , myMqttEsp8266(myEsp8266, mqttServerConfig.server, mqttServerConfig.port, mqttServerConfig.cid, mqttServerConfig.user, mqttServerConfig.pass)
   , myPingTime(0)
   , myConnectFails(0)
   , myMaxConnectFails(3)
   , myDebugSerial(serial)
{
	
}

void MqttESP8266Port::begin(MqttHub &hub)
{
   hub.registerPort(this);
   
   // Initialise the CC3000 module
   myEsp8266.begin();
  
   MQTT_connect();
}

void MqttESP8266Port::subscribe(const char* mod)
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
	
	myMqttEsp8266.subscribe(&buf[0], 0);
	
}

int8_t MqttESP8266Port::decode(void)
{
   
  //Serial.println("DECODE");
   
  MQTT_connect();

  myMqttEsp8266.processPackets(1);

  if(millis() > myPingTime + 10000)
  {
      //Serial.println("Ping");
      myPingTime = millis();
      if(!myMqttEsp8266.ping())
      {
         //Ping failed so we are no longer connected to the 
         // MQTT server. We should attempt a reconnect.
         //Serial.println("Ping Failed!!!");
         myMqttEsp8266.disconnectServer();
         return 0;
      }
  }

  
  Adafruit_MQTT_Subscribe *subscription;
  if((subscription = myMqttEsp8266.readSubscription()))
  {
	  myTopic = subscription->lastTopic;
	  myPayload = (char*)subscription->lastread;
	  return 1;
  }
  //Serial.println("DECODE END");
  return 0;
}

void MqttESP8266Port::publishMessage(const char* topic, const char* payload)
{
	myMqttEsp8266.publish(topic, payload, 0);
}

void MqttESP8266Port::forwardMessage(const char* topic, const char* payload)
{
   if(payload[0] == 'S' &&
      payload[1] == 'U' &&
      payload[2] == 'B' &&
      payload[3] == '\0')
   {
      myMqttEsp8266.subscribe(topic, 0);
   }else
   {
      myMqttEsp8266.publish(topic, payload, 0);      
   }   
}

#endif