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

#include <OnOffCtrlDevice.h>
#include <Arduino.h>

void OnOffCtrlDevice::begin(int32_t pin, bool defaultState, int32_t onLevel)
{    
    myPin = pin;
    myOnLevel = onLevel;
    
    pinMode(myPin, OUTPUT);
    setState(defaultState);    
}

bool OnOffCtrlDevice::writeValue(const char *valueName, const char *value)
{
    bool processed = false;
    if(compare_string(valueName, "CTL")) //check for the CTL topic
    {
        if(compare_string(value, "ON")) //If payload is ON then turn on the pin this device controls.
        {
            setState(true);
            processed = true;
        }  
        else if(compare_string(value, "OFF")) //If payload is OFF then turn on the pin this device controls.
        {
            setState(false);
            processed = true;
        }
    }
    return processed;
}

void OnOffCtrlDevice::setState(bool state)
{
    myState = state;
    if(myOnLevel == HIGH)
    {
        digitalWrite(myPin, state ? HIGH : LOW);
    }
    else
    {
        digitalWrite(myPin, state ? LOW : HIGH);  
    }
}

Device::ValueStruct OnOffCtrlDevice::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        if(myState)
        {
            output.type = Device::TypeCharArray;
            output.value.charArray = "ON";
        }
        else
        {
            output.type = Device::TypeCharArray;
            output.value.charArray = "OFF";
        }    
        output.name = "SWITCH";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t OnOffCtrlDevice::numValues()
{
    return 1; 
}



