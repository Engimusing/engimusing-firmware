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

#include "MqttPort.h"

#if SPI_INTERFACES_COUNT > 0 && ESP8266_INTERFACES_COUNT > 0

#include "Adafruit_MQTT_ESP8266.h"
#include <Engimusing_ESP8266.h>
#include "Adafruit_MQTT.h"

#if ESP8266_INTERFACES_COUNT > 0
extern Esp8266Config esp8266_0_pinConfig;
#endif
#if ESP8266_INTERFACES_COUNT > 1
extern Esp8266Config esp8266_1_pinConfig;
#endif
#if ESP8266_INTERFACES_COUNT > 2
extern Esp8266Config esp8266_2_pinConfig;
#endif
#if ESP8266_INTERFACES_COUNT > 3
extern Esp8266Config esp8266_3_pinConfig;
#endif

struct WlanConfig
{
   const char* ssid;
   const char* pass; 
};

struct MqttServerConfig
{
     const char *server;
     uint16_t port;
     const char *cid;
     const char *user;
     const char *pass;
};

class MqttESP8266Port : public MqttPort
{
   
 public:
 
  MqttESP8266Port(Esp8266Config &pinConfig, WlanConfig &wlanConfig, MqttServerConfig &mqttServerConfig, UARTClass &serial = Serial1);
  
  virtual int8_t decode(void);

  virtual void subscribe(const char* mod);
  
  virtual void begin(MqttHub &hub);
  
  virtual void MQTT_connect();
  
  virtual void publishMessage(const char* topic, const char* payload);
  
  virtual void forwardMessage(const char* topic, const char* payload);
  
 protected:
  
  Engimusing_ESP8266 myEsp8266;
  Adafruit_MQTT_ESP8266 myMqttEsp8266;
  
  int myPingTime;
  
  Esp8266Config &myPinConfig;
  WlanConfig &myWlanConfig;
  MqttServerConfig &myMqttServerConfig;
  
  uint8_t myConnectFails;
  uint8_t myMaxConnectFails;
 
  UARTClass &myDebugSerial;
};

#endif