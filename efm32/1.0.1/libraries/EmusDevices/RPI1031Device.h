///@file RPI1031Device.h
///@brief Contains RPI1031Device class which is a Device derived class for accessing an RPI1031 tilt detector
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/RPI-1031_tilt_sensor.pdf
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

#pragma once

#include "Arduino.h"

#include "Device.h"

class RPI1031Device : public Device
{
 
   public:
        virtual void begin(int32_t switchPin1, int32_t switchPin2, int32_t gndPin1, int32_t gndPin2, int32_t gndPin3, uint32_t debounceCount);
        virtual bool switchState(uint8_t id);
         
        virtual bool risingEdge(uint8_t id);
        virtual bool fallingEdge(uint8_t id);
         
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
        virtual void update();
        
   protected:   
        
        bool myFallingEdge[2];
        bool myRisingEdge[2];
        uint32_t mySwitchPin[2];
        uint32_t myDebounceCount;
        bool myLastState[2];
        uint32_t myCurStateCount[2];
      
};