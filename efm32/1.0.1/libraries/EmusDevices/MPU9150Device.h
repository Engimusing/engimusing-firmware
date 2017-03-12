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

class MPU9150Device : public Device
{
 
    public:
        virtual void begin(TwoWire &wire, int32_t standbyPin, int32_t frameSyncPin);
         
        virtual void getTemp(float& temp);
        virtual void getCompassData(int& x, int& y, int& z);
        virtual void getGyroData(int& x, int& y, int& z);
        virtual void getAccelData(int& x, int& y, int& z);

        virtual Device::ValueStruct readValue(int index);
        virtual float numValues(); 
        
    protected:   

        virtual void setupCompass();
        
        virtual int readCompassX();
        virtual int readCompassY();
        virtual int readCompassZ();
                
        virtual int readGyroX();
        virtual int readGyroY();
        virtual int readGyroZ();
        
        virtual int readAccelX();
        virtual int readAccelY();
        virtual int readAccelZ();
        
        virtual int readSensor(int addrL, int addrH);
        virtual int readSensor(int addr);
        virtual int writeSensor(int addr,int data);

    protected:
    
        TwoWire *myWire; 
        int myCurrentI2CAddress;

};