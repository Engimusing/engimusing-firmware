///
///@file MqttTimeModule.h
///@brief Contains the MqttTimeModule class which handles date time requests from MQTT 
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
#include "MqttHub.h"

#include "DateTime.h"
#include "MqttModule.h"

///@brief Class for handling date time requests and responses.
/// Handles requests to send the current date and time and also synchronization requests to set the date/time 
class MqttTimeModule : public MqttModule
{
    public:
       
        ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub object to connect the module to.
        ///@param [in] mod Name of the Date Time messages to listen to.
        virtual void begin(MqttHub &hub, const char* mod);
       
        ///@brief Called by the MqttHub update() and currently does nothing
        virtual void update(void); 
        
        ///@brief Attempt to decode an MQTT Date Time Message message. 
        ///@param [in] topic Topic from the MQTT message
        ///@param [in] payload Payload from the MQTT message
        ///@return 1 if the message was decoded and 0 if not.
        virtual uint8_t decode(const char* topic, const char* payload);
    
        
        ///@brief Get the DateTime object for this instance
        ///@return The DateTime for this class
        virtual DateTime &dateTime();
        
        ///@brief Helper function which converts an unsigned integer into a character array
        ///@param [in] value Integer to convert to a char array
        ///@param [in] output Char array to put the output into. Needs to be at least numDigits in length.
        ///@param [in] numDigits Number of digits of the value to convert to the char array
        static void uintToCharArray(uint32_t value, char *output, uint32_t numDigits);

        ///@brief Send the current date and time over MQTT 
        ///@param [in] module module/topic to use for this send of the date/time
        void sendCurrentDateTime(const char* module);
        
    protected:
        
        ///@brief Parse the current string from the date input string module
        ///@param [in] date string from the input string module for the date
        ///@details Date should be in the format YYYY:MM:DD where : can be any character   
        void parseDate(const char *date);
        
        ///@brief Parse the current string from the time input string module
        ///@param [in] time string from the input string module for the time
        ///@details Time should be in the format HH:MM where : can be any character and it is in 24 hour format   
        void parseTime(const char *time);
        
        ///@brief Parse the current string from the day input string module
        ///@param [in] day string from the input string module for the day
        ///@details day should be 3 character all capitalized abbreviation for the day
        ///MON, TUE, WED, THU, FRI, SAT, SUN        
        void parseDay(const char *day);

    protected:
        
        DateTime myDateTime;
        MessageInputStringModule myDateInputModule;       
        MessageInputStringModule myTimeInputModule;
        MessageInputStringModule myDayInputModule;
};