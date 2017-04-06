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

class TwoWire;

class HTU21DDevice : public Device
{
 
   public:
        virtual void begin(TwoWire &wire, int32_t enablePin);
        
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
        virtual unsigned int readTemp();
        virtual unsigned int readHumidity();
        virtual float calcTemp(int SigTemp);
        virtual float calcHumidity(int SigRH);
        
   protected:   
        TwoWire *myWire;
      
};
