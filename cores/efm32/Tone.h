///
///@file Tone.h
///@brief Contains a couple utility functions for turning on a tone on a pin
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2015 Arduino LLC.  All right reserved.
///
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

#ifdef __cplusplus


///@brief Generates a tone on the given pin
///@param [in] _pin Pin to play the tone on
///@param [in] frequency Frequency of the tone to play
///@param [in] duration Duration to play the tone for in milliseconds
///@details Function defined in timer.cpp
void tone(uint32_t _pin, uint32_t frequency, uint32_t duration = 0);

///@brief Stop generating a tone on a given pin
///@param [in] _pin Pin to stop the tone from playing on
///@details Function defined in timer.cpp
void noTone(uint32_t _pin);

#endif


