///
///@file MqttHub.h
///@brief Contains the MqttHub class which is used to connect the modules to the ports.
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

#include "Arduino.h"

#define MODULE_TABLE_ENTRIES    8
#define MODULE_STRING_LENGTH   64
#define ITEM_TOKEN_LENGTH      24
#define ITEM_PAYLOAD_LENGTH    32
#define COMM_STRING_LENGTH    26 + MODULE_STRING_LENGTH + ITEM_PAYLOAD_LENGTH
#define NUMBER_ELEMENTS         3
#define ITEM_TYPE               0
#define ITEM_ID                 1
#define ITEM_ACTION             2

class MqttPort;
class MqttModule;

///@brief Class for connecting MqttModules and MqttPorts. Pass this class to the begin functions for the modules and ports 
/// and they will be connected. Then call update() to keep them up to date.
class MqttHub
{
    public:

        ///@brief Constructor that initializes a few internal variables.
        ///@return MqttHub object that is ready to connect to modules and ports by passing this to their begin() functions.
        MqttHub();

        ///@name sendMessage
        ///@brief Functions for sending messages out the MqttPorts. There are overloads to handle multiple different input payload types.
        ///@details the non char * input functions just convert to a char * and then call the char * version.
        ///The float overload can also have the number of digits after the decimal specified and defaults to 2.
        ///@{
        virtual void sendMessage(const char* mod, const char* subTop, int payload) { sendMessage(mod, subTop, (long) payload); } 
        virtual void sendMessage(const char* mod, const char* subTop, unsigned int payload) { sendMessage(mod, subTop, (unsigned long) payload); } 
        virtual void sendMessage(const char* mod, const char* subTop, unsigned long payload);
        virtual void sendMessage(const char* mod, const char* subTop, long payload);
        virtual void sendMessage(const char* mod, const char* subTop, float payload, int digits = 2);
        virtual void sendMessage(const char* mod, const char* subTop, const char* payload);
        ///@}
        
        ///@brief Send a subscribe message for a particular module to all the ports.
        ///@param [in] mod Module name to subscribe to.
        virtual void  subscribe(const char* mod);
      
        ///@brief Register a module with the Hub.
        ///@param [in] module Module to register with this hub.
        ///@details A module can only be registered with a single MqttHub. This is because the modules are linked together 
        /// as a singlely linked list using a member variable in the module itself. By using a linked list the structure does not require any memory to function. 
        virtual void registerModule(MqttModule *module);
        
        ///@brief Register a port with the Hub.
        ///@param [in] port Port to register with this hub.
        ///@details A port can only be registered with a single MqttHub. This is because the ports are linked together 
        /// as a singlely linked list using a member variable in the module itself. By using a linked list the structure does not require any memory to function. 
        virtual void registerPort(MqttPort *port);
      
        ///@brief Function that performs all the communication between the modules and ports. Should be run periodically as often as possible.
        ///@details Main function for using the MqttHub. Once the hub is setup with it's modules and ports this is really the only thing
        /// that needs to be called. The main loop for a sketch can be as simple as calling this function and all connected ports and modules will be handled.
        virtual void update();
        
     protected:
 
        ///@brief Unused noop function??
        void processPortInput();
    
        uint32_t mySubscribeHeartbeat;
        uint32_t myHeatbeatTick;
        MqttModule *myRootModule;
        MqttPort *myRootPort;
        MqttModule *myNextSubscribeModule;
};

