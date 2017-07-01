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
#include "RingBuffer.h"

#define WLAN_CONNECT_TIMEOUT 10000  // how long to wait, in milliseconds
#define RXBUFFERSIZE  256 // how much to buffer on the incoming side
#define TXBUFFERSIZE  32 // how much to buffer on the outgoing side


class UARTClass;

struct Esp8266Config
{
   uint8_t powerPin;
   uint8_t resetPin; 
   uint8_t gpio0Pin;
   UARTClass& serial;
};

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

class Engimusing_ESP8266 {
    
  public:
    Engimusing_ESP8266(Esp8266Config &config, UARTClass *debugPrinter = NULL);
    
    //Not robust function. It will only work with relatively simple cases (specifically will have problems with mutliple of the same letter in the strToFine)
    //Written to be fast and not require a buffer
    bool waitForStr(const char *strToFind, int timeout = 10000, bool retIfPacketFound = false);
    
    bool begin();
    
    bool connectToAp(const char *ssid, const char *key);
    bool disconnectFromAp();
    
    bool connectTcp(const char *destServer, uint16_t destPort);
    bool disconnectTcp();
    bool tcpConnected();
    
    bool     checkConnected(void);
    
    int16_t write(const void *buf, uint16_t len, uint32_t flags = 0);
    int16_t read(void *buf, uint16_t len, uint16_t timeout);
  
    void processPacket(int timeout);
  private:

    Esp8266Config &myConfig;
    UARTClass* mySerial;
    UARTClass* myDebugPrinter;
    int myConnectionCheckTimeout;
    int myLastConnectionCheck;
    bool myConnectedToAp;
    
    int myTcpConnectionCheckTimeout;
    int myLastTcpConnectionCheck;
    bool myTcpConnected;
    
    RingBuffer myPacketBuffer;
    int myIpdFoundChar;
    const char *myTcpServer;
    uint16_t myTcpPort;
};


