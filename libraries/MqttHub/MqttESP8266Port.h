///
///@file MqttESP8266Port.h
///@brief Contains the MqttESP8266Port class which creates a MQTT port over a WiFi connection.
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///

#pragma once

#include "MqttPort.h"

#if SPI_INTERFACES_COUNT > 0 && ESP8266_INTERFACES_COUNT > 0

#include "Adafruit_MQTT_ESP8266.h"
#include <Engimusing_ESP8266.h>
#include "Adafruit_MQTT.h"

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

///@brief Class for connecting an MqttHub to an Mqtt server over WiFi using an ESP8266
class MqttESP8266Port : public MqttPort
{
   
    public:
 
        ///@brief Constructor which takes in the CC3000 and MQTT server configuration.
        ///@param [in] pinConfig ESP8266 pin configuration 
        ///@param [in] wlanConfig Wlan access point configuration
        ///@param [in] mqttServerConfig MQTT server configuration including TCP connection settings and username/password for server
        ///@param [in] serial Serial port to use for debug/log printouts.
        ///@return MqttESP8266Port object that is configured
        MqttESP8266Port(Esp8266Config &pinConfig, WlanConfig &wlanConfig, MqttServerConfig &mqttServerConfig, UARTClass &serial = Serial1);
  
        ///@brief Initialize the port and connect the object to an MqttHub
        ///@param [in] hub MqttHub to connect the port to.
        virtual void begin(MqttHub &hub);

        ///@brief Check for available packets and process any input packets. Run by the MQTTHub::update() function.
        ///@return 1 if there was a packet decoded. 0 if there were no packets decoded.
        virtual int8_t decode(void);

        ///@brief Send a subscribe message to the MQTT server for the given module.
        ///@param [in] mod Name of the module to subscribe to messages for.
        virtual void subscribe(const char* mod);

        ///@brief Connect to the MQTT server or reconnect if the connection is lost. This is called by begin() and any other message sending/receiving functions
        virtual void MQTT_connect();

        ///@brief Send a message over the Mqtt protocol 
        ///@param [in] topic Topic to use for the Mqtt message
        ///@param [in] payload Payload for the Mqtt message
        virtual void publishMessage(const char* topic, const char* payload);

        ///@brief Forward a received message to the Mqtt Server. If it is a subscription then it turns it into a subscription message instead of a regular message
        ///@param [in] topic Topic to use for the Mqtt message
        ///@param [in] payload Payload for the Mqtt message
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