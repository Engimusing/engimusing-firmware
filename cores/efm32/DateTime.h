///
///@file DateTime.h
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

#pragma once

#ifdef TESTING
void setMillis(unsigned int millis);
unsigned long millis();
#endif

///@brief Class which keeps track of the current date and time. 
/// Can be passed the current time from the server and then will keep track of the current time based on
/// the number of milliseconds since the last update.
class DateTime
{
    public:
        ///@brief Constructor for DateTime class, initializes the date and time
        ///@details Initializes the date/time to March 4th 2018 06:24 
        DateTime();
        ///@brief Destructor for the DateTime class
        ///@details Noop for now
        ~DateTime();
        
        ///@brief Sets the year
        ///@param [in] year year
        void setYear(unsigned int year);
        ///@brief Get the year after updating the current time.
        ///@return Year
        unsigned int year();
        
        ///@brief Set the month
        ///@param [in] month month
        ///@details Month of the year where January is 0
        void setMonth(unsigned int month);
        ///@brief Get the month after updating the current time.
        ///@return Month
        ///@details Month of the year where January is 0
        unsigned int month();
        
        ///@brief Set the day
        ///@param [in] day day
        void setDay(unsigned int day);
        ///@brief Get the day after updating the current time.
        ///@return day
        unsigned int day();
        
        ///@brief Set the hour
        ///@param [in] hour hour
        void setHour(unsigned int hour);
        ///@brief Get the hour after updating the current time.
        ///@return hour
        unsigned int hour();
        
        ///@brief Set the minute
        ///@param [in] minute minute
        void setMinute(unsigned int minute);
        ///@brief Get the minute after updating the current time.
        ///@return minute
        unsigned int minute();
    
        ///@brief Set the second
        ///@param [in] second second
        void setSecond(unsigned int second);
        ///@brief Get the second after updating the current time.
        ///@return second
        unsigned int second();

        ///@brief set the current day of the week
        ///@param [in] dayOfWeek day of the week
        ///@details Day of the week where Monday is 0
        void setDayOfWeek(unsigned int dayOfWeek);
        ///@brief get the current day of the week after updating the current time.
        ///@return current day of the week
        ///@details Day of the week where Monday is 0
        unsigned int dayOfWeek();
        
        ///@brief Updates the current time and date based on the current value of millis()
        void updateCurrentTime();
        
        ///@brief returns the number of days in February for the current year
        ///@return number of days in February for the current year
        unsigned int daysInFeburary();
        
    protected:
        unsigned int myYear;
        unsigned int myMonth;
        unsigned int myDay;
        unsigned int myHour;
        unsigned int myMinute;
        unsigned int mySecond;
        unsigned int myDayOfWeek;
        
        int myLastUpdateTime;
        
};
