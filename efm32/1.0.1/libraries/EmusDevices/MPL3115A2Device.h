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

class MPL3115A2Device : public Device
{
 
    public:
        virtual void begin(TwoWire &wire, int32_t enablePin);
         
        virtual float readTemp();
        virtual float readTempF();
        virtual float readAltitude();
        virtual float readPressure();
        virtual float readAltitudeFt();

         
        virtual Device::ValueStruct readValue(int index);
        virtual float numValues(); 
        
    protected:   
    
        virtual void setModeBarometer();
  
        virtual void setModeAltimeter();
        virtual void setModeStandby();
        virtual void setModeActive();
        virtual void setFIFOMode(byte f_Mode);
        virtual void setOversampleRate(byte sampleRate);
        virtual void toggleOneShot();
        virtual void enableEventFlags();
        virtual byte i2cRead(byte regAddr);
        virtual void i2cWrite(byte regAddr, byte value);
        
    protected:
    
        TwoWire *myWire; 

};