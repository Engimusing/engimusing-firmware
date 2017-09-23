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

#include "Device.h"


class OnOffCtrlDevice : public Device
{
   public:
        virtual void begin(int32_t pin, bool defaultState, int32_t onLevel);

        virtual bool writeValue(const char *valueName, const char *value);
        virtual void setState(bool state);
        
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
   protected:   
        int32_t myPin;
        int32_t myOnLevel; 
        bool myState; 
      
};