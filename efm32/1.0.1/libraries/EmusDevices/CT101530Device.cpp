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

#include <CT101530Device.h>
#include <Arduino.h>

void CT101530Device::begin(int32_t switchPin, int32_t gndPin, uint32_t debounceCount)
{        
    if(gndPin > 0)
    {
        pinMode(gndPin, OUTPUT);
        digitalWrite(gndPin, LOW);
    }
    
    pinMode(switchPin, INPUT_PULLUP);   
     
    mySwitchPin = switchPin;
    
    myDebounceCount = debounceCount;

    //give the slave a slight delay so it can turn on.
    delay(50);
    
    myLastState = switchState();
    
    myRisingEdge = false;
    myFallingEdge = false;
    myCurStateCount = 0;//used to keep track of how many checks it has stayed the same
}

bool CT101530Device::switchState()
{
    return (bool)digitalRead(mySwitchPin);
}

bool CT101530Device::risingEdge()
{
    bool temp = myRisingEdge;
    myRisingEdge = false;
    return temp;
}

bool CT101530Device::fallingEdge()
{
    bool temp = myFallingEdge;
    myFallingEdge = false;
    return temp;
}


void CT101530Device::update()
{
    bool currentState = switchState();
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
    
    delay(1);
}

Device::ValueStruct CT101530Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeCharArray;
        if(switchState())
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

uint32_t CT101530Device::numValues()
{
    return 3; 
}


