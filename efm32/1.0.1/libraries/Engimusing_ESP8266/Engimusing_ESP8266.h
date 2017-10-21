///
///@file Engimusing_ESP8266.h
///@brief Contains the Engimusing_ESP8266 class which is used to connect and communicate over WiFi using an ESP8266
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/ESP8266-ESP-12E_Radio.pdf
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

///@brief Class for connecting to and communicating over WiFi using the ESP8266 WiFi module.
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/ESP8266-ESP-12E_Radio.pdf
class Engimusing_ESP8266 {
    
  public:
  
    ///@brief Constructor which sets up the configuration for connecting to an ESP8266
    ///@param [in] config Esp8266Config structure which contains the settings required to connect to an ESP8266
    ///@param [in] debugPrinter Optional parameter which specifies where to send debug printouts
    ///@return A configured Engimusing_ESP8266 object
    Engimusing_ESP8266(Esp8266Config &config, UARTClass *debugPrinter = NULL);
    
    
    ///@brief Find a string in the input packets from the WIFI connection
    ///@param [in] strToFind String to look for in the packets
    ///@param [in] timeout Time in milliseconds to look for the string before giving up
    ///@param [in] retIfPacketFound If true and the stream contains +IPD, then it will return false instead of continuing until the timeout is reached.
    ///@return True if the string was found in the stream.
    ///@details Not robust function. It will only work with relatively simple cases (specifically will have problems with multiple of the same letter in the strToFind)
    ///Written to be fast and not require a buffer
    bool waitForStr(const char *strToFind, int timeout = 10000, bool retIfPacketFound = false);
    
    ///@brief Turn on the ESP8266 and wait for the ready string.
    ///@return If the ready string is found then it returns true else returns false.
    bool begin();
    
    ///@brief Connect to a wifi access point. Blocks until the connection is connected or ~21 second timeout is reached
    ///@param [in] ssid ssid to connect to
    ///@param [in] key passcode to use to connect to the wifi ssid
    ///@return True if the ESP8266 is connected to the access point, else false.
    ///@details Will print out to the debug printer if there are any errors. 
    bool connectToAp(const char *ssid, const char *key);
    
    ///@brief Attempts to disconnect from the access point. 
    ///@return True if the connection was successfully disconnected, else false.
    bool disconnectFromAp();
    
    ///@brief Connect to a server over TCP. Must already be connected to an AP. Blocks until the connection is connected or 10 second timeout is reached.
    ///@param [in] destServer IP of server to connect to in the format x.x.x.x
    ///@param [in] destPort Port on the server to connect to.
    ///@return True if the TCP connection was successfull else false.
    bool connectTcp(const char *destServer, uint16_t destPort);
    
    ///@brief Attempt to disconnect from the TCP server. Blocks until disconnected or the 10 second timeout is reached.
    ///@return True if the disconnect was sucessfull, else false.
    bool disconnectTcp();
    
    ///@brief Check to see if the TCP connection is still connected. This only checks the device every 10 Minutes and saves the current state between checks.
    ///@return True if the TCP connection is still connected.   
    bool tcpConnected();
    
    ///@brief Check to see if the WiFi is still connected to the Access point. This only checks the device every 10 minutes and saves the current state between checks.
    ///@return True if the device is still connected to the access point.
    bool checkConnected(void);
    
    ///@brief Write the buffer to the TCP server.
    ///@param [in] buf Buffer of data to send to the TCP server.
    ///@param [in] len Number of bytes to send to the tcp server.
    ///@param [in] flags Unused parameter
    ///@return Number of bytes that were actually sent.
    int16_t write(const void *buf, uint16_t len, uint32_t flags = 0);
    
    ///@brief Read data from the TCP server.
    ///@param [in] buf Buffer to store the data read from the server in.
    ///@param [in] len Number of bytes to read from the server.
    ///@param [in] timeout Time in milliseconds to wait for a packet to show up before giving up.
    ///@return Number of bytes actually read from the server.
    int16_t read(void *buf, uint16_t len, uint16_t timeout);
  
    ///@brief Read data from the server into a buffer for later processing.
    ///@param [in] timeout Time to wait for data from the server.
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


