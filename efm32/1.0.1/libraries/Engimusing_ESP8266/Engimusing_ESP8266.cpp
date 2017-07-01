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

#include "Engimusing_ESP8266.h"

Engimusing_ESP8266::Engimusing_ESP8266(Esp8266Config &config, UARTClass *debugPrinter) 
    : myConfig(config)
    , mySerial(&config.serial)
    , myDebugPrinter(debugPrinter)
    , myConnectionCheckTimeout(600000) //check every 10 minutes if we are still connected to the AP
    , myLastConnectionCheck(0)
    , myConnectedToAp(false)
    , myTcpConnectionCheckTimeout(600000)
    , myLastTcpConnectionCheck(0)
    , myTcpConnected(false)
    , myPacketBuffer()
    , myIpdFoundChar(0)
    , myTcpServer(0)
    , myTcpPort(0)
{
}

bool Engimusing_ESP8266::begin()
{
    mySerial->begin(115200);
    
    pinMode(myConfig.resetPin, OUTPUT);
    digitalWrite(myConfig.resetPin, HIGH);   // get the rest pin ready for the board to turn on

    pinMode(myConfig.powerPin, OUTPUT);
    digitalWrite(myConfig.powerPin, LOW);   // start with the board turned off
    
    pinMode(myConfig.gpio0Pin, OUTPUT);
    digitalWrite(myConfig.gpio0Pin, HIGH);   // set the gpio0 pin so that the ESP8266 boots
    
    delay(100);
    pinMode(myConfig.powerPin, OUTPUT);
    digitalWrite(myConfig.powerPin, HIGH);   // turn on the ESP8266
    
    bool found = waitForStr("ready");
    if(myDebugPrinter)
    {
        if(found)
        {
            myDebugPrinter->println("Engimusing_ESP8266 Ready!");
        }
        else
        {
            myDebugPrinter->println("Engimusing_ESP8266 Ready String Timeout!!");
        }
    }
    return found;
}

bool Engimusing_ESP8266::waitForStr(const char *strToFind, int timeout, bool retIfPacketFound)
{
    int starttime = millis();
    int foundChar = 0;
    int strToFindLen = strlen(strToFind);
    
    const char *ipdFindString = "+IPD,";
    int ipdFindStringLen = 5;
    
    while(starttime + timeout > millis())
    {
        if(mySerial->available())
        {
            char readChar = mySerial->read();
            if(readChar == strToFind[foundChar])
            {
                foundChar++;
            }
            else
            {
                foundChar = 0;
            }              
            
            if(readChar == ipdFindString[myIpdFoundChar])
            {
                myIpdFoundChar++;
                if(myIpdFoundChar == ipdFindStringLen)
                {
                    int processPacketTimeout = timeout - (millis() - starttime);
                    if(processPacketTimeout < 10)
                    {
                        processPacketTimeout = 10;
                    }
                    processPacket(processPacketTimeout);
                    foundChar = 0;
                    myIpdFoundChar = 0;
                    if(retIfPacketFound)
                    {
                        return false;
                    }
                }
            }
            else
            {
                myIpdFoundChar = 0;
            }
            
            if(myDebugPrinter)
            {
                myDebugPrinter->print(readChar);
            }
            
            if(foundChar >= strToFindLen)
            {
                return true;
            }
        }
    }
    return false;
}

bool Engimusing_ESP8266::connectToAp(const char *ssid, const char *key)
{
    mySerial->println("AT+CWMODE=1"); // Change to regular connection mode
    if(!waitForStr("OK", 100)) 
    {
        if(myDebugPrinter)
        {
            myDebugPrinter->println("Conect to AP Failed changing modes!");
        }
        myConnectedToAp = false;
        return false;
    }
    
    mySerial->print("AT+CWJAP=\""); // Join access point
    mySerial->print(ssid);
    mySerial->print("\",\"");
    mySerial->print(key);
    mySerial->println('\"');
    
    if(!waitForStr("OK", 10000)) 
    {
        if(myDebugPrinter)
        {
            myDebugPrinter->println("Conect to AP Failed connecting to AP!");
        }
        myConnectedToAp = false;
        return false;
    }
       
    mySerial->println("AT+CIPMUX=0");// Set single-client mode
    
     if(!waitForStr("OK", 10000)) 
    {
        if(myDebugPrinter)
        {
            myDebugPrinter->println("Conect to AP Failed Changing to Single Client!");
        }
        myConnectedToAp = false;
        return false;
    }
    
    if(myDebugPrinter)
    {
        myDebugPrinter->print("Connected to AP:");
        myDebugPrinter->println(ssid);
    }
    myConnectedToAp = true;
    return true;
    
}

bool Engimusing_ESP8266::disconnectFromAp()
{
    mySerial->println("AT+CWQAP");
    if(!waitForStr("OK", 10000))
    {
        myDebugPrinter->println("Disconnecting from AP Failed!");
        return false;
    }
    myTcpConnected = false;
    myConnectedToAp = false;
    return true;
}

bool Engimusing_ESP8266::connectTcp(const char *destServer, uint16_t destPort)
{
    myTcpServer = destServer;
    myTcpPort = destPort;
    mySerial->print("AT+CIPSTART=\"TCP\",\"");
    mySerial->print(destServer);
    mySerial->print("\",");
    mySerial->println(destPort);
    if(!waitForStr("OK", 10000))
    {
        myDebugPrinter->println("Conect to TCP Server Failed!");
        myTcpConnected = false;
        return false;
    }
   
    myTcpConnected = true;
    return myTcpConnected;
}

bool Engimusing_ESP8266::disconnectTcp()
{
    mySerial->println("AT+CIPCLOSE");
    if(!waitForStr("OK", 10000))
    {
        myDebugPrinter->println("Disconnecting from TCP Server Failed!");
        return false;
    }
    myTcpConnected = false;
    return true;
}

bool Engimusing_ESP8266::tcpConnected()
{
    if(myLastTcpConnectionCheck + myTcpConnectionCheckTimeout < millis())
    {
        myLastTcpConnectionCheck = millis();
        mySerial->println("AT+CIPSTATUS"); // Change to regular connection mode
        if(!waitForStr("STATUS:3", 100)) 
        {
            if(myDebugPrinter)
            {
                myDebugPrinter->println("Not connected to TCP Server");
            }
            myTcpConnected = false;
            return false;
        }
        waitForStr("OK", 100);
        myTcpConnected = true;
    }
    return myTcpConnected;
}

bool Engimusing_ESP8266::checkConnected(void)
{
    if(tcpConnected())
    {
        myConnectedToAp = true;
        return true;
    }
    if(myLastConnectionCheck + myConnectionCheckTimeout < millis())
    {
        myLastConnectionCheck = millis();
        mySerial->println("AT+CIPSTATUS"); // Change to regular connection mode
        if(!waitForStr("STATUS:2", 100)) 
        {
            if(myDebugPrinter)
            {
                myDebugPrinter->println("Not connected to AP");
            }
            myConnectedToAp = false;
            return false;
        }
        waitForStr("OK", 100);
        myConnectedToAp = true;
    }
    return myConnectedToAp;
}

int16_t Engimusing_ESP8266::write(const void *buf, uint16_t len, uint32_t flags)
{
    mySerial->print("AT+CIPSEND=");
    mySerial->println(len);
    if(!waitForStr(">", 1000))
    {
        myTcpConnected = false;
        return 0;
    }
    char *charBuf = (char*)buf;
    while(len--)
    {
        mySerial->print(*charBuf);
        charBuf++;
    }
    mySerial->print("\r\n\r\n"); // 4
    waitForStr("OK", 1000);
    return (charBuf - (char*)buf);
}

void Engimusing_ESP8266::processPacket(int timeout)
{
    int receivedLen = 0;
    char nextChar = 0;
    int starttime = millis();
    
    while((starttime + timeout > millis()) && nextChar != ':' && receivedLen < 64000)
    {
        if(mySerial->available())
        {
            nextChar = mySerial->read();
            if(myDebugPrinter)
            {
                myDebugPrinter->print(nextChar);
            }
            if(nextChar <= '9' && nextChar >= '0')
            {
                receivedLen *= 10;
                receivedLen += nextChar - '0';
            }
            else if(nextChar != ':')
            {
                return;
            }
        }
    }
    while((starttime + timeout > millis()) && receivedLen > 0)            
    {
        if(mySerial->available())
        {
            myPacketBuffer.store_char(mySerial->read());
            receivedLen--;
        }
    }   
    
}

int16_t Engimusing_ESP8266::read(void *buf, uint16_t len, uint16_t timeout)
{
    
    if(myPacketBuffer.empty())
    {
        if(waitForStr("ERROR,", timeout, true))
        {
            myPacketBuffer.flush();
            if(!myTcpConnected)
            {
                return 0;
            }
        }
    }
    
    if(!myPacketBuffer.empty())
    {
        int charIdx = 0;
         char *charBuf = (char*)buf;
        while(charIdx < len && !myPacketBuffer.empty())            
        {
            charBuf[charIdx] = myPacketBuffer.read();
            charIdx++;
        }  
        return charIdx;
    }
    return 0;
}

//define up to 4 default cc3000 pin configurations
#if ESP8266_INTERFACES_COUNT > 0
Esp8266Config esp8266_0_pinConfig = {
   PIN_ESP8266_0_POWER,
   PIN_ESP8266_0_RESET,
   PIN_ESP8266_0_GPIO0,
   SERIAL_ESP8266_0
};
#endif

#if ESP8266_INTERFACES_COUNT > 1
Esp8266Config esp8266_1_pinConfig = {
   PIN_ESP8266_1_POWER,
   PIN_ESP8266_1_RESET,
   PIN_ESP8266_1_GPIO0,
   SERIAL_ESP8266_1
};
#endif

#if ESP8266_INTERFACES_COUNT > 2
Esp8266Config esp8266_2_pinConfig = {
   PIN_ESP8266_2_POWER,
   PIN_ESP8266_2_RESET,
   PIN_ESP8266_2_GPIO0,
   SERIAL_ESP8266_2
};
#endif

#if ESP8266_INTERFACES_COUNT > 3
Esp8266Config esp8266_3_pinConfig = {
   PIN_ESP8266_3_POWER,
   PIN_ESP8266_3_RESET,
   PIN_ESP8266_3_GPIO0,
   SERIAL_ESP8266_3
};
#endif
  