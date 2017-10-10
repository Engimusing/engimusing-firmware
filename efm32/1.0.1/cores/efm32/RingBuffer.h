///
///@file RingBuffer.h
///@brief Contains RingBuffer class which is defines a simple ring buffer object
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

#include <stdint.h>

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.

//bumped up the size so that more than one mqtt command would fit on the buffer at a time.
#define SERIAL_BUFFER_SIZE 256
#define SERIAL_BUFFER_MASK 0x00FF;

///@brief Simple ring buffer where the head is next location to write and the tail is the next location to read
/// currently set to 256 bytes
class RingBuffer
{
  public:
    ///@brief Constructor which sets up a few internal variables
    ///@return RingBuffer object
    RingBuffer( void ) ;
    
    ///@brief Store a character in the ring buffer. This increments the head of the buffer
    ///@param [in] c character to store
    ///@details If storing the character will fill the buffer then it will not be stored and this function will no-op
    void store_char( uint8_t c );
    
    ///@brief Check to see if the buffer is empty
    ///@return Returns true if the buffer is empty
    bool empty();
    
    ///@brief Clear the buffer
    void flush();
    
    ///@brief Read the next character from the buffer and increment the tail. Returns 0 if the buffer is empty.
    ///@return Character read from the buffer.
    char read();
  
  public:
    uint8_t _aucBuffer[SERIAL_BUFFER_SIZE] ;
    volatile uint16_t _iHead ;
    volatile uint16_t _iTail ;
  
} ;

