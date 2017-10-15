///@file MLX90614Device.h
///@brief Contains MLX90614Device class which is a Device derived class for accessing an MLX90614 IR thermometer  
///Datasheet link https://www.sparkfun.com/datasheets/Sensors/Temperature/MLX90614_rev001.pdf
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

class MLX90614Device : public Device
{
 
   public:
        virtual void begin(TwoWire &wire, int32_t enablePin);
        virtual float temperature();
         
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
   protected:   
        TwoWire *myWire;
        uint8_t myAddress; 
        uint8_t myDataSize; 
        uint8_t myReadRegister;
      
};
