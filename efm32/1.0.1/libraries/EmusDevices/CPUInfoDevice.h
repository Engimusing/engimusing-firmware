///@file CPUInfoDevice.h
///@brief Contains the CPUInfoDevice class which is a Device implementation for accessing the CPU information of an energy micro.
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


class CPUInfoDevice : public Device
{
 
   public:
        virtual void begin();
        virtual float getTemperatureC();
        virtual float getTemperatureF();
        virtual float voltage();
        
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
   protected:   

      
};
