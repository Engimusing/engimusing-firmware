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
#include "timeout.h"

Timeout::Timeout() 
    : myLoop(true)
    , myTimeoutTime(1000)
    , myLastUpdateTime(0)
{
}

void Timeout::begin(int timeoutRateMs, bool loop)
{
   myTimeoutTime = timeoutRateMs;
   myLoop = loop;
   myLastUpdateTime = millis();
}

void Timeout::reset()
{
  myLastUpdateTime = millis();
}

void Timeout::setTimeoutTime(int timeoutRateMs)
{
    myTimeoutTime = timeoutRateMs;
}

int Timeout::timeoutTime()
{
    return myTimeoutTime;
}

void Timeout::setShouldLoop(bool loop)
{
    myLoop = loop;
}

bool Timeout::update()
{
    if(myLastUpdateTime + myTimeoutTime < millis())
    {
        if(myLoop)
        {
            myLastUpdateTime = millis();
        }
        return true;
    }
    return false;
}
