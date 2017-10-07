/*
  Copyright (c) 2017 Engimusing LLC.  All right reserved.
  
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
#include "togglePin.h"

TogglePin::TogglePin() 
    : myPin(-1)
{
}

void TogglePin::begin(int toggleTime, uint8_t activeLevel)
{
  TogglePin::begin(LED_BUILTIN, OUTPUT, toggleTime, toggleTime, activeLevel);
}

void TogglePin::begin(uint32_t dwPin, int offTime, int onTime, uint8_t activeLevel)
{
  TogglePin::begin(dwPin, OUTPUT, offTime, onTime, activeLevel);
}

void TogglePin::begin(uint32_t dwPin, WiringModeTypeDef dwMode, int offTime, int onTime, uint8_t activeLevel)
{
  myPin = dwPin;
  pinMode(myPin, dwMode);
  myOnTimeout.begin(onTime);
  myOffTimeout.begin(offTime);
  myOn = HIGH;
  myActiveLevel = activeLevel;
}

void TogglePin::update(void)
{
    if(myPin >= 0) // make sure begin has been called with a reasonable pin
    {
        if(myOn == HIGH) {
            if(myOnTimeout.update()) {
                if(myActiveLevel == HIGH)
                {
                    digitalWrite(myPin, LOW);
                }
                else
                {
                    digitalWrite(myPin, HIGH);
                }
                myOn = LOW;
                myOffTimeout.reset();
            }
        }
        if(myOn == LOW) {
            if (myOffTimeout.update()) {
                digitalWrite(myPin, myActiveLevel);
                myOn = HIGH;
                myOnTimeout.reset();
            }
        }
    }
}

void TogglePin::setToggleTime(int time) 
{ 
    setOffOnTimes(time, time);
}

void TogglePin::setOffOnTimes(int offTime, int onTime)
{
    myOffTimeout.setTimeoutTime(offTime);
    myOnTimeout.setTimeoutTime(onTime);
}

int TogglePin::offTime()
{
    return myOffTimeout.timeoutTime();
}

int TogglePin::onTime()
{
    return myOnTimeout.timeoutTime();
}
  

