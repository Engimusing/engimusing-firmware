///
///@file delay.h
///@brief Utility functions for delaying different lengths of time
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2015 Arduino LLC.  All right reserved.
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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

///@brief Returns the number of milliseconds since the Arduino board began running the current program.
///@return Number of milliseconds since the program started (uint32_t)
///@details This number will overflow (go back to zero), after approximately 50 days.
extern uint32_t millis( void ) ;

///@brief Returns the number of microseconds since the Arduino board began running the current program.
///@return Number of microseconds since the program started (uint32_t)
///@details There are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
extern uint32_t micros( void ) ;

///@brief Pauses the program for the amount of time (in miliseconds) specified as parameter.
///@param [in] dwMs the number of milliseconds to pause (uint32_t)
///@details (There are 1000 milliseconds in a second.)
extern void delay( uint32_t dwMs ) ;

///@brief Pauses the program for the amount of time (in microseconds) specified as parameter.
///@param [in] usec the number of microseconds to pause (uint32_t)
extern void delayMicroseconds( uint32_t usec );

///@brief Set an energy saving delay
///@param [in] maxMillisecondDelay maximum number of milliseconds the loop() will wait every time around the loop
///@details This will cause the processor to delay between times that loop() is called. It will wait for within 1 ms of maxMillisecondDelay. 
extern void setEnergySavingDelay(uint32_t maxMillisecondDelay);

///@brief Called by main.cpp between every call to loop()
extern void energySavingDelay();

#ifdef __cplusplus
}
#endif

