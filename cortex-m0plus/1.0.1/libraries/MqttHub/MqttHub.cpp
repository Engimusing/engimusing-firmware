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

//MQTT hub is the main center of the mqtt communication classes
// It connects to all the modules (devices) and the ports (external IO) for a particular processor

#include "MqttHub.h"
#include "MqttPort.h"
#include "MqttModule.h"

MqttHub::MqttHub()
{
  mySubscribeHeartbeat = 30000; //30 second heartbeat
  
  myHeatbeatTick = 0;
  myRootModule = 0;
  myRootPort = 0;
}

void MqttHub::subscribe(const char* mod)
{
	//send the subscription to all ports
	MqttPort *curPort = myRootPort;
	while(curPort)
	{
		curPort->subscribe(mod);
		curPort = curPort->myNextPort;
	}
}

void MqttHub::registerModule(MqttModule *module)
{
	module->myNextModule = myRootModule;
	myRootModule = module;
}

void MqttHub::registerPort(MqttPort *port)
{
	port->myNextPort = myRootPort;
	myRootPort = port;
}

void MqttHub::processPortInput()
{
    MqttModule *curModule = myRootModule;
	MqttPort *curPort = myRootPort;
   
   bool processed = false;
   
	while(curPort)
	{
		if(curPort->decode())
		{
			curModule = myRootModule;
			while(curModule)
			{
				if(curModule->decode(curPort->myTopic, curPort->myPayload))
				{
					curModule = 0;
               processed = true;
				}else
				{
					curModule = curModule->myNextModule;
				}
			}
         
         //check to see if this hub handled the message. If not send it to all the other ports.
         if(!processed)
         {
            MqttPort *curSendPort = myRootPort;
            while(curSendPort)
            {
               if(curSendPort != curPort)
               {
                  curSendPort->forwardMessage(curPort->myTopic, curPort->myPayload);
               }
               curSendPort = curSendPort->myNextPort;
            }
          }         
		}
		curPort = curPort->myNextPort;
	}
    
    curModule = myRootModule;
	while(curModule)
	{
		curModule->update();
		
		curModule = curModule->myNextModule;
	}
}



void MqttHub::update()
{
	
    processPortInput();
		
	if(millis() > myHeatbeatTick + mySubscribeHeartbeat)
	{
		myHeatbeatTick = millis();
		MqttModule *curModule = myRootModule;
		while(curModule)
		{
            if(curModule->mySubOnHeartbeat)
			{
				subscribe(curModule->myModule);	
			}
            //Process prot input after every subscription to clear out subacks
            processPortInput();
            
			curModule = curModule->myNextModule;
		}
	}
}

void MqttHub::sendMessage(const char* mod, const char* subTop, unsigned long payload)
{
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	do {
		unsigned long m = payload;
		payload /= 10;
		char c = m - 10 * payload;
		*--str = c + '0';
	} while(payload);
	
	sendMessage(mod, subTop, str);
}

void MqttHub::sendMessage(const char* mod, const char* subTop, long payload)
{
	char buf[8 * sizeof(long) + 2]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	bool negative = payload < 0;
	
	if(negative)
	{
		payload = -payload;
	}
	
	do {
		unsigned long m = payload;
		payload /= 10;
		char c = m - 10 * payload;
		*--str = c + '0';
	} while(payload);
	
	if(negative)
	{
		*--str = '-';
	}
	
	sendMessage(mod, subTop, str);
}

void MqttHub::sendMessage(const char* mod, const char* subTop, float payload, int digits)
{
  size_t n = 0;
  float number = payload;
  if (isnan(number)) { sendMessage(mod, subTop, "nan"); return; }
  if (isinf(number)) { sendMessage(mod, subTop, "inf"); return; }
  if (number > 4294967040.0) { sendMessage (mod, subTop, "ovf"); return; }  // constant determined empirically
  if (number <-4294967040.0) { sendMessage (mod, subTop, "ovf"); return; } // constant determined empirically
  
  bool negative = false;
  bool hasDigits = digits > 0;
  // Handle negative numbers
  if (number < 0.0)
  {
     negative = true;
     number = -number;
  }
  
  
  // Round correctly so that print(1.999, 2) prints as "2.00"
  float rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  float remainder = number - (float)int_part;
  
  char buf[41]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1 - digits];
  char *decimalStr = str;
  
  
  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    char toPrint = char(remainder);
	*++decimalStr = toPrint + '0';
    remainder -= toPrint;
  }
  
  *++decimalStr = '\0';

  // Print the decimal point, but only if there are digits beyond
  if (hasDigits) {
    *str = '.';
  }
  
  do {
		unsigned long m = int_part;
		int_part /= 10;
		char c = m - 10 * int_part;
		*--str = c + '0';
	} while(int_part);
  
  // Handle negative numbers
  if (negative)
  {
     *--str = '-';
  }
  
  sendMessage(mod, subTop, str);
}


void MqttHub::sendMessage(const char* mod, const char* subTop, const char* payload)
{
	char buf[MODULE_STRING_LENGTH];
	int len = strlen(mod);
	if(len > MODULE_STRING_LENGTH - 1)
	{
		len = MODULE_STRING_LENGTH - 1;
	}
	
	memmove(&buf[0], mod, len);
	
	if(len < MODULE_STRING_LENGTH - 3)
	{
		memmove(&buf[len], "?/", 2);
		len += 2;
	}
	
	int subTopLen = strlen(subTop);
	if(len + subTopLen < MODULE_STRING_LENGTH - 1)
	{
		memmove(&buf[len], subTop, subTopLen);
		len += subTopLen;
		buf[len] = '\0';
	}
	
	//send the message to all ports
	MqttPort *curPort = myRootPort;
	while(curPort)
	{
		curPort->publishMessage(buf, payload);
		curPort = curPort->myNextPort;
	}
	
}


