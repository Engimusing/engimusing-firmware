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

#if SPI_INTERFACES_COUNT > 0 && CC3000_INTERFACES_COUNT > 0

#include "Adafruit_MQTT_CC3000.h"
#include <Adafruit_CC3000.h>
#include "Adafruit_MQTT.h"

#if CC3000_INTERFACES_COUNT > 0
extern Cc3000PinConfig cc3000_0_pinConfig;
#endif
#if CC3000_INTERFACES_COUNT > 1
extern Cc3000PinConfig cc3000_1_pinConfig;
#endif
#if CC3000_INTERFACES_COUNT > 2
extern Cc3000PinConfig cc3000_2_pinConfig;
#endif
#if CC3000_INTERFACES_COUNT > 3
extern Cc3000PinConfig cc3000_3_pinConfig;
#endif

struct Cc3000WlanConfig
{
   const char* ssid;
   const char* pass; 
   uint8_t security;
};

struct MqttServerConfig
{
     const char *server;
     uint16_t port;
     const char *cid;
     const char *user;
     const char *pass;
};

class MqttCC3000Port : public MqttPort
{
   
 public:
 
  MqttCC3000Port(Cc3000PinConfig &pinConfig, Cc3000WlanConfig &wlanConfig, MqttServerConfig &mqttServerConfig, UARTClass &serial = Serial1);
  
  virtual int8_t decode(void);

  virtual void subscribe(const char* mod);
  
  virtual void begin(MqttHub &hub);
  
  virtual void MQTT_connect();
  
  virtual void publishMessage(const char* topic, const char* payload);
  
  virtual void forwardMessage(const char* topic, const char* payload);
  
 protected:
  
  Adafruit_CC3000 myCc3000;
  Adafruit_MQTT_CC3000 myMqttCc3000;
  
  int myPingTime;
  
  Cc3000PinConfig &myPinConfig;
  Cc3000WlanConfig &myWlanConfig;
  MqttServerConfig &myMqttServerConfig;
  
  uint8_t myConnectFails;
  uint8_t myMaxConnectFails;
 
  UARTClass &mySerial;
};

#endif