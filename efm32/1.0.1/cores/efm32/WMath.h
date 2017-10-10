///
///@file WMath.h
///@brief Contains utility functions for handing common math problems 
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2014 Arduino.  All right reserved.
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

///@brief Return a random long
///@param [in] howbig largest possible random value to return
///@return Random value between 0 and howbig
extern long random( long howbig) ;
///@brief Return a random long
///@param [in] howsmall smallest possible random value to return
///@param [in] howbig largest possible random value to return
///@return Random value between howsmall and howbig
///@details if howsmall is larger than howbig than it will return howsmall
extern long random( long howsmall, long howbig) ;
///@brief Set the current seed to use for rand()
///@param [in] dwSeed new seed to use for rand()
extern void randomSeed( uint32_t dwSeed ) ;
///@brief Map a value from one range of values into another
///@param [in] x Value to map
///@param [in] in_min Input minimum range
///@param [in] in_max Input maximum range
///@param [in] out_min Output minimum range
///@param [in] out_max Output maximum range
///@return Return the mapped value
///@details output = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
extern long map( long x, long in_min, long in_max, long out_min, long out_max) ;

///@brief Returns the input unchanged
///@param [in] w input value
///@return input value
extern uint16_t makeWord( uint16_t w ) ;

///@brief Takes two 8-bit values and combines them into a single 16-bit value
///@param [in] h high byte
///@param [in] l low byte
///@return 16-bit value
extern uint16_t makeWord( uint8_t h, uint8_t l ) ;

#define word(...) makeWord(__VA_ARGS__)

