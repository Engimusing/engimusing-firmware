///@file SSCDNNN150PG2A3Device.h
///@brief Contains SSCDNNN150PG2A3Device class which is a Device derived class for accessing an SSCDNNN150PG2A3 pressure sensor
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

///@brief Class for connecting to an SSCDNNN150PG2A3 pressure sensor.
class SSCDNNN150PG2A3Device : public Device
{

    public:
        
        ///@brief Initialization function for setting up a connection to an SSCDNNN150PG2A3
        ///@param [in] wire TwoWire object that is connected to an SSCDNNN150PG2A3
        ///@param [in] enablePin Pin that is connected to the enable pin on the SSCDNNN150PG2A3
        virtual void begin(TwoWire &wire, int32_t enablePin);

        ///@brief Get the current pressure reading in PSI from the SSCDNNN150PG2A3
        ///@return Current pressure reading in PSI
        virtual float readPressure();
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = PRESSURE (float) - current pressure reading in PSI
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 1 for this class.
        virtual uint32_t numValues();         
        
    protected:
    
        TwoWire *myWire; 

};
