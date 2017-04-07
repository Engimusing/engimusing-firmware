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

#include <DualCT101530Device.h>
#include <Arduino.h>

void DualCT101530Device::begin(int32_t switchPin1, int32_t switchPin2, int32_t gndPin1, int32_t gndPin2, uint32_t debounceCount)
{        
    if(gndPin1 > 0)
    {
        pinMode(gndPin1, OUTPUT);
        digitalWrite(gndPin1, LOW);
    }
    
    if(gndPin2 > 0)
    {
        pinMode(gndPin2, OUTPUT);
        digitalWrite(gndPin2, LOW);
    }
    
    pinMode(switchPin1, INPUT_PULLUP);   
    pinMode(switchPin2, INPUT_PULLUP);   
     
    mySwitchPin[0] = switchPin1;
    mySwitchPin[1] = switchPin2;
    
    myDebounceCount = debounceCount;

    //give the slave a slight delay so it can turn on.
    delay(50);
    
    myLastState[0] = switchState(0);
    myLastState[1] = switchState(1);
    
    myRisingEdge[0] = false;
    myRisingEdge[1] = false;
    myFallingEdge[0] = false;
    myFallingEdge[1] = false;
    myCurStateCount[0] = 0;//used to keep track of how many checks it has stayed the same
    myCurStateCount[1] = 0;//used to keep track of how many checks it has stayed the same
}

bool DualCT101530Device::switchState(uint8_t id)
{
    return (bool)digitalRead(mySwitchPin[id]);
}

bool DualCT101530Device::risingEdge(uint8_t id)
{
    bool temp = myRisingEdge[id];
    myRisingEdge[id] = false;
    return temp;
}

bool DualCT101530Device::fallingEdge(uint8_t id)
{
    bool temp = myFallingEdge[id];
    myFallingEdge[id] = false;
    return temp;
}


void DualCT101530Device::update()
{
    for(int i = 0; i < 2; i++)
    {
        bool currentState = switchState(i);
        if(myLastState[i] != currentState)
        {
            myCurStateCount[i]++;
            if(myCurStateCount[i] > myDebounceCount)
            {
                if(myLastState[i] == HIGH)
                {
                    myFallingEdge[i] = true;
                }
                else
                {
                    myRisingEdge[i] = true;
                }
                myLastState[i] = currentState;
            }
        }
        else
        {
            myCurStateCount[i] = 0;
        }
    }
    delay(1);
}

Device::ValueStruct DualCT101530Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeCharArray;
        if(switchState(0))
        {
            output.value.charArray = "CLOSED";
        }
        else
        {
            output.value.charArray = "OPEN";
        }
        output.name = "CURRENT_STATE_0";
    }
    else if(index == 1)
    {
        output.type = Device::TypeBool;
        output.value.boolean = risingEdge(0);
        output.name = "RISING_EDGE_0";
    }
    else if(index == 2)
    {
        output.type = Device::TypeBool;
        output.value.boolean = fallingEdge(0);
        output.name = "FALLING_EDGE_0";
    }
    else if(index == 3)
    {
        output.type = Device::TypeCharArray;
        if(switchState(1))
        {
            output.value.charArray = "CLOSED";
        }
        else
        {
            output.value.charArray = "OPEN";
        }
        output.name = "CURRENT_STATE_1";
    }
    else if(index == 4)
    {
        output.type = Device::TypeBool;
        output.value.boolean = risingEdge(1);
        output.name = "RISING_EDGE_1";
    }
    else if(index == 5)
    {
        output.type = Device::TypeBool;
        output.value.boolean = fallingEdge(1);
        output.name = "FALLING_EDGE_1";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t DualCT101530Device::numValues()
{
    return 3; 
}


