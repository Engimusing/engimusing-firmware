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


#include "MqttCC3000Port.h"

#if SPI_INTERFACES_COUNT > 0 && CC3000_INTERFACES_COUNT > 0

#include <Adafruit_CC3000.h>
#include "Adafruit_MQTT.h"

#include "CC3000helper.h"

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
            CC3000connect(myCc3000, myWlanConfig.ssid, myWlanConfig.pass, myWlanConfig.security, mySerial);  // y0w, lets connect to wifi again
       //mySerial->println("Retrying MQTT connection in 5 seconds...");
       myMqttCc3000.disconnect();
       delay(5000);  // wait 5 seconds
  }
   myConnectFails = 0;
}


MqttCC3000Port::MqttCC3000Port(Cc3000PinConfig &pinConfig, 
                                                 Cc3000WlanConfig &wlanConfig,
                                                 MqttServerConfig &mqttServerConfig,
                                                 UARTClass &serial
                                                 ) 
   : MqttPort()
   , myPinConfig(pinConfig)
   , myWlanConfig(wlanConfig)
   , myMqttServerConfig(mqttServerConfig)
   , myCc3000(pinConfig.csPin, pinConfig.irqPin, pinConfig.vbatPin, pinConfig.spi, SPI_CLOCK_DIVIDER, &serial)
   , myMqttCc3000(&myCc3000, mqttServerConfig.server, mqttServerConfig.port, mqttServerConfig.cid, mqttServerConfig.user, mqttServerConfig.pass)
   , myPingTime(0)
   , myConnectFails(0)
   , myMaxConnectFails(3)
   , mySerial(serial)
{
	
}

void MqttCC3000Port::begin(MqttHub &hub)
{
   hub.registerPort(this);
   
   // Initialise the CC3000 module
   myCc3000.begin();
  
   while (! CC3000connect(myCc3000, myWlanConfig.ssid, myWlanConfig.pass, myWlanConfig.security, mySerial)) {
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

#endif