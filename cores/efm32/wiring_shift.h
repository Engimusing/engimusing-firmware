///
///@file wiring_shift.h
///@brief Contains some utility functions for reading and writing a character over two pins
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

#ifdef __cplusplus
 extern "C" {
#endif

///@brief Shift in a byte of data from a pin
///@param [in] ulDataPin Pin to read the data from
///@param [in] ulClockPin Pin to use as a clock for the transaction
///@param [in] ulBitOrder Order to shift the data in, either LSBFIRST or MSBFIRST
///@return Character value read off of the pin
extern uint32_t shiftIn( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder ) ;


/*
 * \brief
 */
///@brief Shift a byte out of data on a pin
///@param [in] ulDataPin Pin to send the character out on
///@param [in] ulClockPin Pin to use as a clock for the transaction
///@param [in] ulBitOrder Order for the byte to be shifted out in, either LSBFIRST or MSBFIRST
///@param [in] ulVal value to send out on the pin
extern void shiftOut( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder, uint32_t ulVal ) ;


#ifdef __cplusplus
}
#endif

