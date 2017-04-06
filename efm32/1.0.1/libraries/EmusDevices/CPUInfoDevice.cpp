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

#include <Arduino.h>

#include <CPUInfoDevice.h>

#include "efm_lib/analog.h"

extern AnalogLP  Analog;
	
void CPUInfoDevice::begin()
{    
 
}

float CPUInfoDevice::getTemperatureC()
{
   temperature tempval = Analog.analogReadTemp();
   return ((float)tempval.tenthsC / 10.0f);
}

float CPUInfoDevice::getTemperatureF()
{
   temperature tempval = Analog.analogReadTemp();
   return ((float)tempval.tenthsF / 10.0f);
}

float CPUInfoDevice::voltage()
{
   uPvdd vddval = Analog.analogReadVDD();
   return ((float)vddval.mVolts / 1000.0f);
}


Device::ValueStruct CPUInfoDevice::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = getTemperatureC();
        output.name = "DEG_C";
    }
    else if(index == 1)
    {
        output.type = Device::TypeFloat;  
        output.value.decimal = voltage();
          
        output.name = "ADC";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t CPUInfoDevice::numValues()
{
    return 2; 
}



