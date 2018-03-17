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

#include "MqttTimeModule.h"

#include "MqttModule.h"

#include <Arduino.h>


// ------------------------------- Simple Module Class ------------------------
void MqttTimeModule::begin(MqttHub &hub, const char* mod)
{    
    MqttModule::begin(hub, mod, true);
    myDateInputModule.begin(hub, mod, "DATE");       
    myTimeInputModule.begin(hub, mod, "TIME");
    myDayInputModule.begin(hub, mod, "DAY");
}

void MqttTimeModule::update(void)
{
    if(myDateInputModule.hasNewData())
    {
        parseDate(myDateInputModule.getInputString());
    }
    
    if(myTimeInputModule.hasNewData())
    {
        parseTime(myTimeInputModule.getInputString());
    }
    
    if(myDayInputModule.hasNewData())
    {
        parseDay(myDayInputModule.getInputString());
    }
}

void MqttTimeModule::uintToCharArray(uint32_t value, char *output, uint32_t numDigits)
{
    int curCharIdx = numDigits - 1;
    for(int i = 0; i < numDigits; i++)
    {
       
        int flooredValue = value / 10;
        flooredValue *= 10;
        output[curCharIdx] = '0' + (value - flooredValue);
        value /= 10;
        
        curCharIdx--;
    }
}

uint8_t MqttTimeModule::decode(const char* topic, const char* payload)
{
    int8_t j = isTopicThisModule(topic);
    if(j == 0)
    {
        return 0;
    }
    
    if(compare_token(payload,"STATUS"))
    {
        char date[11] = {'Y','Y','Y','Y',':','M','M',':','D','D','\0'};
        uintToCharArray(myDateTime.year(), &(date[0]), 4);
        uintToCharArray(myDateTime.month(), &(date[5]), 2);
        uintToCharArray(myDateTime.day(), &(date[8]), 2);
        myHub->sendMessage((const char*)myModule, "DATE", date);
        
        char time[6] = {'H','H',':','M','M','\0'};
        uintToCharArray(myDateTime.hour(), &(time[0]), 2);
        uintToCharArray(myDateTime.minute(), &(time[3]), 2);
        myHub->sendMessage((const char*)myModule, "TIME", time);
        
        switch(myDateTime.dayOfWeek())
        {
            case 0:
                myHub->sendMessage((const char*)myModule, "DAY", "MON");
                break;
            case 1:
                myHub->sendMessage((const char*)myModule, "DAY", "TUE");
                break;
            case 2:
                myHub->sendMessage((const char*)myModule, "DAY", "WED");
                break;
            case 3:
                myHub->sendMessage((const char*)myModule, "DAY", "THU");
                break;
            case 4:
                myHub->sendMessage((const char*)myModule, "DAY", "FRI");
                break;
            case 5:
                myHub->sendMessage((const char*)myModule, "DAY", "SAT");
                break;
            case 6:
                myHub->sendMessage((const char*)myModule, "DAY", "SUN");
                break;
            default:
                //If the day of the week is invalid then noop
                break;
        }
    }
}

DateTime &MqttTimeModule::dateTime()
{
    return myDateTime;
}

void MqttTimeModule::parseDate(const char *date)
{
    if(strlen((char*)date) != 10)
    {
        //invalid string length lets just return and ignore this date.
        return;
    }
    
    char buffer[6] = {'\0','\0','\0','\0','\0','\0'};
    buffer[0] = date[8];
    buffer[1] = date[9];
    
    uint32_t day = atoi(buffer);
    
    if(day > 31)
    {
        return;
    }
    
    buffer[0] = date[5];
    buffer[1] = date[6];
    
    uint32_t month = atoi(buffer);
    
    if(month > 12)
    {
        return;
    }
        
    buffer[0] = date[0];
    buffer[1] = date[1];
    buffer[2] = date[2];
    buffer[3] = date[3];
    
    uint32_t year = atoi(buffer);
    
    myDateTime.setDay(day);
    myDateTime.setMonth(month);
    myDateTime.setYear(year);
    
}

void MqttTimeModule::parseTime(const char *time)
{
    if(strlen((char*)time) != 5)
    {
        //invalid string length lets just return and ignore this date.
        return;
    }
    
    char buffer[3] = {'\0','\0','\0'};
    
    buffer[0] = time[0];
    buffer[1] = time[1];
    
    int hour = atoi(buffer);
    
    if(hour > 23)
    {
        return;
    }
    
    buffer[0] = time[3];
    buffer[1] = time[4];
    
    int minute = atoi(buffer);
    
    if(minute > 59)
    {
        return;
    }
    
    myDateTime.setHour(hour);
    myDateTime.setMinute(minute);
    
}

void MqttTimeModule::parseDay(const char *day)
{
    if(strlen((char*)day) != 3)
    {
        //invalid string length lets just return and ignore this date.
        return;
    }
   
    if(day[0] == 'M' && day[1] == 'O' && day[2] == 'N')
    {
        myDateTime.setDayOfWeek(DateTime::DAY_MON);
    }
    else if(day[0] == 'T')
    {
        if(day[1] == 'U' && day[2] == 'E')
        {
                myDateTime.setDayOfWeek(DateTime::DAY_TUE);
        }
        else if(day[1] == 'H' && day[2] == 'U')
        {
            myDateTime.setDayOfWeek(DateTime::DAY_THU);
        }
    }
    else if(day[0] == 'W' && day[1] == 'E' && day[2] == 'D')
    {
        myDateTime.setDayOfWeek(DateTime::DAY_WED);
    }
    else if(day[0] == 'F' && day[1] == 'R' && day[2] == 'I')
    {
        myDateTime.setDayOfWeek(DateTime::DAY_FRI);
    }
    else if(day[0] == 'S')
    {
        if(day[1] == 'A' && day[2] == 'T')
        {
            myDateTime.setDayOfWeek(DateTime::DAY_SAT);
        }
        else if(day[1] == 'U' && day[2] == 'N')
        {
            myDateTime.setDayOfWeek(DateTime::DAY_SUN);
        }
    }
    
}    
