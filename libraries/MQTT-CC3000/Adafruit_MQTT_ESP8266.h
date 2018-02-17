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
// Written based on the Adafruit_MQTT_ESP8266

#pragma once

#include <Engimusing_ESP8266.h>
#include "Adafruit_MQTT.h"

// delay in ms between calls of available()
#define MQTT_ESP8266_INTERAVAILDELAY 10

//#define DEBUG_PRINT(x) Serial.println(x);
//#define DEBUG_PRINTLN(x) Serial.println(x);

// CC3000-specific version of the Adafruit_MQTT class.
// Note that this is defined as a header-only class to prevent issues with using
// the library on non-CC3000 platforms (since Arduino will include all .cpp files
// in the compilation of the library).
class Adafruit_MQTT_ESP8266 : public Adafruit_MQTT {
 public:
  Adafruit_MQTT_ESP8266(Engimusing_ESP8266 &esp8266, const char *server, uint16_t port,
                       const char *cid, const char *user, const char *pass):
    Adafruit_MQTT(server, port, cid, user, pass),
    myEsp8266(&esp8266)
  {}

  Adafruit_MQTT_ESP8266(Engimusing_ESP8266 &esp8266, const char *server, uint16_t port,
                       const char *user = "", const char *pass = ""):
    Adafruit_MQTT(server, port, user, pass),
    myEsp8266(&esp8266)
  {}

  //virtual ~Adafruit_MQTT_ESP8266() {}
  
  bool connectServer() {
    // connect to server
    DEBUG_PRINTLN(F("Connecting to TCP"));
    return myEsp8266->connectTcp(servername, portnum);
  }

  bool disconnectServer() {
    if (myEsp8266->tcpConnected()) {
      return myEsp8266->disconnectTcp();
    }
    else {
      return true;
    }
  }

  bool connected() {
    return myEsp8266->tcpConnected();
  }

  uint16_t readPacket(uint8_t *buffer, uint16_t maxlen, int16_t timeout) {
    //Serial.println("reading packet!");
    if (myEsp8266->tcpConnected()) {
        return myEsp8266->read(buffer, maxlen, timeout);
    }
    /* Read data until either the connection is closed, or the idle timeout is reached. */
   return 0;
   
   #if 0 //need to implement this
    
   uint16_t len = 0;
    int16_t t = timeout;

    spiFinishRead();
    while (myEsp8266->tcpConnected() && (timeout >= 0)) {
      //DEBUG_PRINT('.');
      while (mqttclient.available()) {
        //DEBUG_PRINT('!');
        char c = mqttclient.read();
        timeout = t;  // reset the timeout
        buffer[len] = c;
        //DEBUG_PRINTLN(c);
        len++;
        if (len == maxlen) {  // we read all we want, bail
          DEBUG_PRINT(F("Read packet:\t"));
          DEBUG_PRINTBUFFER(buffer, len);
          return len;
        }
      }
      //Watchdog.reset();
      timeout -= MQTT_CC3000_INTERAVAILDELAY;
      delay(MQTT_CC3000_INTERAVAILDELAY);
    }
	//Serial.println(":");
    return len;
    #endif
  }

  bool sendPacket(uint8_t *buffer, uint16_t len) {
    if (myEsp8266->tcpConnected()) {
      uint16_t ret = myEsp8266->write(buffer, (size_t)len);
      DEBUG_PRINT(F("sendPacket returned: ")); DEBUG_PRINTLN(ret);
      if (ret != len) {
        DEBUG_PRINTLN("Failed to send complete packet.")
        return false;
      }
    } else {
      DEBUG_PRINTLN(F("Connection failed!"));
      return false;
    }
    return true;
  }
  
  bool connectToAp(const char *ssid, const char *key)
  {
      myEsp8266->connectToAp(ssid, key);
  }
  
  bool connectedToAp()
  {
      return myEsp8266->checkConnected();
  }
 private:
  Engimusing_ESP8266 *myEsp8266;
};


