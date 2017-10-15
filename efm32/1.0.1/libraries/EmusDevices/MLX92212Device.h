///@file MLX92212Device.h
///@brief Contains the MLX92212Device class which is a Device derived class for accessing the MLX92212 3-wire hall effect switch 
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MLX92212LSE.pdf
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

class MLX92212Device : public Device
{
 
   public:
        virtual void begin(int32_t enablePin, int32_t switchPin, uint32_t debounceCount);
        virtual bool switchState();
         
        virtual bool risingEdge();
        virtual bool fallingEdge();
         
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
        virtual void update();
        
   protected:   
        
        bool myFallingEdge;
        bool myRisingEdge;
        uint32_t mySwitchPin;
        uint32_t myDebounceCount;
        bool myLastState;
        uint32_t myCurStateCount;
      
};
