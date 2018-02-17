///@file TMD26721Device.h
///@brief Contains TMD26721Device class which is a Device derived class used to access a TMD26721 digital proximity sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TMD2672_Datasheet.pdf
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

class TwoWire;

///@brief Class for connecting to a TMD26721 digital proximity sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TMD2672_Datasheet.pdf
class TMD26721Device : public Device
{
 
   public:
        ///@brief Initializer function for setting up a connection to TMD26721
        ///@param [in] wire TwoWire object that is connected to the TMD26721
        ///@param [in] enablePin Pin connected to the enable pin on the TMD26721
        ///@param [in] pulseCount Number of pulses for the TMD26721 to send when sensing proximity
        virtual void begin(TwoWire &wire, int32_t enablePin, uint8_t pulseCount);
        
        ///@brief Read the current proximity data from the TMD26721
        ///@return Current raw proximity data
        virtual int proximityData();
        
         ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = PROXIMITY (int) - Raw value for the proximity
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 1 for this class.
        virtual uint32_t numValues();   
        
   protected:   
        TwoWire *myWire; 
        uint8_t myPulseCount;
          
};