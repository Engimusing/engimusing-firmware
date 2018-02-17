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

#include <CapSenseDevice.h>

#if NUM_LESENSE_CHANNELS > 0

void CapSenseDevice::begin(uint8_t channel, float sensitivity, uint32_t debounceCount)
{    
    
    myChannel = channel;
    
    myDebounceCount = debounceCount;

    mySenstivity = sensitivity;
    
    CapSense.begin();
    CapSense.initChannel(channel, sensitivity);
    
    myLastState = 0;
    myRisingEdge = false;
    myFallingEdge = false;
    myCurStateCount = 0;//used to keep track of how many checks it has stayed the same
}

bool CapSenseDevice::state()
{
    uint16_t channelState = CapSense.channelsState() & (1 << myChannel) ;
    if(channelState != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CapSenseDevice::risingEdge()
{
    bool temp = myRisingEdge;
    myRisingEdge = false;
    return temp;
}

bool CapSenseDevice::fallingEdge()
{
    bool temp = myFallingEdge;
    myFallingEdge = false;
    return temp;
}


void CapSenseDevice::update()
{
    CapSense.update();
    
    bool currentState = state();
    if(myLastState != currentState)
    {
        myCurStateCount++;
        if(myCurStateCount > myDebounceCount)
        {
            if(myLastState == HIGH)
            {
                myFallingEdge = true;
            }
            else
            {
                myRisingEdge = true;
            }
            myLastState = currentState;
        }
    }
    else
    {
        myCurStateCount = 0;
    }
}

Device::ValueStruct CapSenseDevice::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeCharArray;
        if(state())
        {
            output.value.charArray = "CLOSED";
        }
        else
        {
            output.value.charArray = "OPEN";
        }
        output.name = "CURRENT_STATE";
    }
    else if(index == 1)
    {
        output.type = Device::TypeBool;
        output.value.boolean = risingEdge();
        output.name = "RISING_EDGE";
    }
    else if(index == 2)
    {
        output.type = Device::TypeBool;
        output.value.boolean = fallingEdge();
        output.name = "FALLING_EDGE";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t CapSenseDevice::numValues()
{
    return 3; 
}

#endif
