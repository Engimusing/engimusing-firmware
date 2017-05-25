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

// --------------------------------- Basic JSON Communication Class -------------------------

#define MODULE_TABLE_ENTRIES    8
#define MODULE_STRING_LENGTH   64
#define COMM_STRING_LENGTH    253
#define ITEM_TOKEN_LENGTH      24
#define ITEM_PAYLOAD_LENGTH    32
#define NUMBER_ELEMENTS         3
#define ITEM_TYPE               0
#define ITEM_ID                 1
#define ITEM_ACTION             2

class MqttPort;
class MqttModule;

class MqttHub
{
 public:

	MqttHub();

	virtual void sendMessage(const char* mod, const char* subTop, int payload) { sendMessage(mod, subTop, (long) payload); } 
	virtual void sendMessage(const char* mod, const char* subTop, unsigned int payload) { sendMessage(mod, subTop, (unsigned long) payload); } 
	virtual void sendMessage(const char* mod, const char* subTop, unsigned long payload);
	virtual void sendMessage(const char* mod, const char* subTop, long payload);
	virtual void sendMessage(const char* mod, const char* subTop, float payload, int digits = 2);
	virtual void sendMessage(const char* mod, const char* subTop, const char* payload);

	virtual void  subscribe(const char* mod);
  
	virtual void registerModule(MqttModule *module);
	virtual void registerPort(MqttPort *port);
  
	virtual void update();
	
 protected:
 
    void processPortInput();
    
	uint32_t mySubscribeHeartbeat;
	uint32_t myHeatbeatTick;
	MqttModule *myRootModule;
	MqttPort *myRootPort;
	MqttModule *myNextSubscribeModule;
	
};

