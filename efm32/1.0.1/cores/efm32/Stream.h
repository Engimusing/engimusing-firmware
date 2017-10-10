///
///@file Stream.h
///@brief Contains the Stream class which is an abstract class for specifying a stream class
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2010 David A. Mellis.  All right reserved.
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

#include <inttypes.h>
#include "Print.h"

// compatibility macros for testing
/*
#define   getInt()            parseInt()
#define   getInt(skipChar)    parseInt(skipchar)
#define   getFloat()          parseFloat()
#define   getFloat(skipChar)  parseFloat(skipChar)
#define   getString( pre_string, post_string, buffer, length)
readBytesBetween( pre_string, terminator, buffer, length)
*/

class Stream : public Print
{

  public:
    ///@brief Check to see if the stream has any data available
    ///@return Number of bytes available to read
    virtual int available() = 0;
    ///@brief Read the next byte of data
    ///@return returns -1 if there is no data or the next value if data is available
    virtual int read() = 0;
    ///@brief Read the next byte of data without consuming it. Subsequent peek() calls will return the same value until read() is called.  
    ///@return Next available character to read.
    virtual int peek() = 0;
    ///@brief Clear all the available data.
    virtual void flush() = 0;

    ///@brief Constructor which initializes the timeout to 1000ms
    ///@return Stream object
    Stream() {_timeout=1000;}

    // parsing methods

    ///@brief Change the timeout for the stream
    ///@param [in] timeout time to wait for stream data in millisecond
    void setTimeout(unsigned long timeout);  // sets maximum milliseconds to wait for stream data, default is 1 second

    ///@name findFunctions
    ///@brief Functions for finding a character in the stream data
    ///@return True if it finds the target
    ///@{
    bool find(char *target);   // reads data from the stream until the target string is found
    bool find(uint8_t *target) { return find ((char *)target); }
    // returns true if target string is found, false if timed out (see setTimeout)

    bool find(char *target, size_t length);   // reads data from the stream until the target string of given length is found
    bool find(uint8_t *target, size_t length) { return find ((char *)target, length); }
    ///@}
    // returns true if target string is found, false if timed out

    ///@name findUntilFunctions
    ///@brief Functions for finding a character in the stream data but before the terminator is found   
    ///@return True if it finds the target
    ///@{
    bool findUntil(char *target, char *terminator);   // as find but search ends if the terminator string is found
    bool findUntil(uint8_t *target, char *terminator) { return findUntil((char *)target, terminator); }

    bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);   // as above but search ends if the terminate string is found
    bool findUntil(uint8_t *target, size_t targetLen, char *terminate, size_t termLen) {return findUntil((char *)target, targetLen, terminate, termLen); }
    ///@}

    ///@brief returns the first valid (long) integer value from the current position.
    ///@return parsed integer 
    ///@details initial characters that are not digits (or the minus sign) are skipped
    /// integer is terminated by the first character that is not a digit.
    long parseInt(); 
    

    ///@brief returns the first valid (single) float value from the current position.
    ///@return parsed float
    ///@details initial characters that are not digits (or the minus sign) are skipped
    /// float is terminated by the first character that is not a digit.
    float parseFloat();              

    ///@brief read chars from stream into buffer
    ///@param [in] buffer buffer to read characters into
    ///@param [in] length maximum number of characters to read 
    ///@return number of characters read, 0 if there were no characters read
    ///@details terminates if length characters have been read or timeout (see setTimeout)
    size_t readBytes( char *buffer, size_t length);
    ///@brief read chars from stream into buffer
    ///@param [in] buffer buffer to read characters into
    ///@param [in] length maximum number of characters to read 
    ///@return number of characters read, 0 if there were no characters read
    ///@details terminates if length characters have been read or timeout (see setTimeout)
    size_t readBytes( uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
   

    
    ///@brief read chars from stream into buffer with terminator character
    ///@param [in] terminator character to terminate the read command if found
    ///@param [in] buffer buffer to read characters into
    ///@param [in] length maximum number of characters to read 
    ///@return number of characters read, 0 if there were no characters read
    ///@details terminates if length characters have been read or timeout (see setTimeout) or if the terminator character is found
    size_t readBytesUntil( char terminator, char *buffer, size_t length); 
    ///@brief read chars from stream into buffer with terminator character
    ///@param [in] terminator character to terminate the read command if found
    ///@param [in] buffer buffer to read characters into
    ///@param [in] length maximum number of characters to read 
    ///@return number of characters read, 0 if there were no characters read
    ///@details terminates if length characters have been read or timeout (see setTimeout) or if the terminator character is found
    size_t readBytesUntil( char terminator, uint8_t *buffer, size_t length) { return readBytesUntil(terminator, (char *)buffer, length); }
    
    ///@brief read values into a string
    ///@return String object with read characters in it
    String readString();
    
    ///@brief Read values into a string until a charater is found or the timeout is expired
    ///@param [in] terminator character which terminates the read
    ///@return String object with read characters in it
    String readStringUntil(char terminator);

    protected:
    long parseInt(char skipChar); // as above but the given skipChar is ignored
    // as above but the given skipChar is ignored
    // this allows format characters (typically commas) in values to be ignored

    float parseFloat(char skipChar);  // as above but the given skipChar is ignored

    struct MultiTarget {
    const char *str;  // string you're searching for
    size_t len;       // length of string you're searching for
    size_t index;     // index used by the search routine.
    };

    // This allows you to search for an arbitrary number of strings.
    // Returns index of the target that is found first or -1 if timeout occurs.
    int findMulti(struct MultiTarget *targets, int tCount);

  protected:
    int timedRead();    // private method to read stream with timeout
    int timedPeek();    // private method to peek stream with timeout
    int peekNextDigit(); // returns the next numeric digit in the stream or -1 if timeout
  
  protected:
    unsigned long _timeout;      // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis;  // used for timeout measurement
 

};

