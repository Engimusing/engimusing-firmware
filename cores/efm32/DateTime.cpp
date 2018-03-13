///
///@file DateTime.cpp
///@brief Contains DateTime which is an class which provides the current date and time
///
///@section License
///Copyright (c) 2018 Engimusing LLC.  All right reserved.
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///

#include <DateTime.h>

#ifdef TESTING
unsigned int myMillis = 0;
void setMillis(unsigned int millis) { myMillis = millis; }
unsigned long millis() {return myMillis;}
#else
#include "Arduino.h"
#endif

DateTime::DateTime()
    : myYear(2018)
    ,  myMonth(2)
    ,  myDay(4)
    ,  myHour(6)
    ,  myMinute(24)
    ,  mySecond(0)
    ,  myDayOfWeek(6)
    ,  myLastUpdateTime(millis())
{
}

DateTime::~DateTime()
{
}

void DateTime::setYear(unsigned int year)
{
    myYear = year;
    myLastUpdateTime = millis();
}

unsigned int DateTime::year()
{
    updateCurrentTime();
    return myYear;
}

void DateTime::setMonth(unsigned int month)
{
    myMonth = month;
    myLastUpdateTime = millis();
}

unsigned int DateTime::month()
{
    updateCurrentTime();
    return myMonth;
}

void DateTime::setDay(unsigned int day)
{
    myDay = day;
    myLastUpdateTime = millis();
}

unsigned int DateTime::day()
{
    updateCurrentTime();
    return myDay;
}

void DateTime::setHour(unsigned int hour)
{
    myHour = hour;
    myLastUpdateTime = millis();
}

unsigned int DateTime::hour()
{
    updateCurrentTime();
    return myHour;
}

void DateTime::setMinute(unsigned int minute)
{
    myMinute = minute;
    myLastUpdateTime = millis();
}

unsigned int DateTime::minute()
{
    updateCurrentTime();
    return myMinute;
}

void DateTime::setSecond(unsigned int second)
{
    mySecond = second;
    myLastUpdateTime = millis();
}

unsigned int DateTime::second()
{
    updateCurrentTime();
    return mySecond;
}

void DateTime::setDayOfWeek(unsigned int dayOfWeek)
{
    myDayOfWeek = dayOfWeek;
    myLastUpdateTime = millis();
}

unsigned int DateTime::dayOfWeek()
{
    updateCurrentTime();
    return myDayOfWeek;
}

unsigned int DateTime::daysInFeburary()
{
    //Leap year check
    //The year can be evenly divided by 4;
    //If the year can be evenly divided by 100, it is NOT a leap year, unless;
    //The year is also evenly divisible by 400. Then it is a leap year.
    if(myYear % 4 == 0)
    {
        if(myYear % 100 == 0)
        {
            if(myYear % 400 == 0)
            {
                return 29;
            }
            else
            {
                return 28;
            }
        }
        else
        {
            return 29;
        }
    }
    else
    {
        return 28;
    }
}


void DateTime::updateCurrentTime()
{
    unsigned int deltaTime = millis() - myLastUpdateTime;
    if(deltaTime > 1000)
    {
        unsigned int deltaSeconds = deltaTime / 1000;
        
        //add in the time that we are accounting for here.
        myLastUpdateTime += (deltaSeconds * 1000);
        
        mySecond += deltaSeconds;
    }
    
    if(mySecond >= 60)
    {
        myMinute +=  mySecond / 60;
        mySecond = mySecond % 60;
    }
    
    if(myMinute >= 60)
    {
        myHour +=  myMinute / 60;
        myMinute = myMinute % 60;
    }
    
    if(myHour >= 24)
    {
        myDay +=  myHour / 24;
        myDayOfWeek += myHour / 24;
        myDayOfWeek = myDayOfWeek % 7;
        myHour = myHour % 24;
    }
    
    bool isDone = false;
    while(myDay >= 28 && !isDone)
    {
        switch(myMonth)
        {
            //31 day months
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
            case 11:
                if(myDay >= 31)
                {
                    myMonth++;
                    myDay -= 31;
                }
                else
                {
                    isDone = true;
                }
                break;
            //30 day months
            case 3:
            case 5:
            case 8:
            case 10:
                if(myDay >= 30)
                {
                    myMonth++;
                    myDay -= 30;
                }
                else
                {
                    isDone = true;
                }
                break;
            //Feburary
            case 1:
            { 
                unsigned int days = daysInFeburary();
                if(myDay >= days)
                {
                    myMonth++;
                    myDay -= days;
                }
                else
                {
                    isDone = true;
                }
                break;
            }
            default:
                isDone = true;
                break;
        }
        
        if(myMonth >= 12)
        {
            myYear++;
            myMonth -= 12;
        }
    }
}
