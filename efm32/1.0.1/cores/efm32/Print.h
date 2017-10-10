///
///@file Print.h
///@brief Contains Print which is an abstract class which defines a bunch of printing related functions
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2014 Arduino.  All right reserved.
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
#include <stdio.h> // for size_t

#include "WString.h"
#include "Printable.h"
#include <stdarg.h>

#define PRINTF_BUF 120 // define the tmp buffer size (change if desired)

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

///@brief Abstract base class with some common printing functions 
/// derived classes just need to implement write() and then they have access to all these print functions
class Print
{
 private:
  int write_error;
  ///@brief Print an integer number with the specified base to the Printer
  ///@param [in] n Number to print
  ///@param [in] base base to print the number in
  ///@return returns the number of characters written
  size_t printNumber(unsigned long n, uint8_t base);
  
  ///@brief Print a floating point number to the specified number of digits
  ///@param [in] number Double precision floating point number to print
  ///@param [in] digits Number of digits of the number to print
  ///@return Number of characters written
  size_t printFloat(double number, uint8_t digits);
  
  ///@brief Print a floating point number to the specified number of digits
  ///@param [in] number Single precision floating point number to print
  ///@param [in] digits Number of digits of the number to print
  ///@return Number of characters written
  size_t printFloat(float number, uint8_t digits);
  
 protected:
  ///@brief Set the current write error. Unused by Print but can be used by derived classes
  ///@param [in] err error code to set the write error to. 0 is default value
  void setWriteError(int err = 1) { write_error = err; }
 public:
 Print() : write_error(0) {}

  ///@brief Get the current write error. Unused by Print but can be used by derived classes.
  ///@return Current write error code. Default is 0 so most likely value to use as no error.
  int getWriteError() { return write_error; }
  
  ///@brief Clears the current write error. Unused by Print but can be used by derived classes. Sets the write error to 0.
  void clearWriteError() { setWriteError(0); }

  ///@brief Function that needs to be implemented by the derived class. Should write to whatever the derived class is used for.
  ///@param [in] uint8_t byte to write
  ///@return Number of bytes written
  virtual size_t write(uint8_t) = 0;
  
  ///@brief write function overload which handles a null terminated char array.
  ///@param [in] str Null terminated char array
  ///@return number of bytes written
  size_t write(const char *str) 
  {
    if (str == NULL) return 0;
    return write((const uint8_t *)str, strlen(str));
  }
  
  
  ///@brief write function overload which handles an unsigned char buffer of a specified size.
  ///@param [in] str char buffer to write
  ///@return number of bytes written
  virtual size_t write(const uint8_t *buffer, size_t size);
  
  ///@brief write function overload which handles a signed char buffer of a specified size.
  ///@param [in] str char buffer to write
  ///@return number of bytes written
  size_t write(const char *buffer, size_t size) {
    return write((const uint8_t *)buffer, size);
  }

  ///@name printFunctions
  ///@brief Functions for printing all different types of things
  ///@return number of bytes written
  ///@details Functions for integer types the second parameter is the base.
  /// For real types, the second parameter is the number of digits.  
  ///@{
  size_t print(const __FlashStringHelper *);
  size_t print(const String &);
  size_t print(const char[]);
  size_t print(char);
  size_t print(unsigned char, int = DEC);
  size_t print(int, int = DEC);
  size_t print(unsigned int, int = DEC);
  size_t print(long, int = DEC);
  size_t print(unsigned long, int = DEC);
  size_t print(double, int = 10);
  size_t print(float, int = 10);
  size_t print(const Printable&);
  ///@}
  
  ///@name printlnFunctions
  ///@brief Functions for printing all different types of things with a new line after the thing has been printed
  ///@return number of bytes written including the newline
  ///@details Functions for integer types the second parameter is the base.
  /// For real types, the second parameter is the number of digits.  
  /// The newline is both a \r and a \n
  ///@{
  size_t println(const __FlashStringHelper *);
  size_t println(const String &s);
  size_t println(const char[]);
  size_t println(char);
  size_t println(unsigned char, int = DEC);
  size_t println(int, int = DEC);
  size_t println(unsigned int, int = DEC);
  size_t println(long, int = DEC);
  size_t println(unsigned long, int = DEC);
  size_t println(double, int = 10);
  size_t println(float, int = 10);
  size_t println(const Printable&);
  size_t println(void);
  ///@}

  ///@brief Complex printing function for printing some text with input variables
  ///@param [in] format Base text use % commands for specifying where input variables go
  ///@param [in] ... Multiple arguments for specifying input variables
  ///@details See http://www.cplusplus.com/reference/cstdio/printf/ for more information
  void printf(const char *format, ...)
  {
    char buf[PRINTF_BUF];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, sizeof(buf), format, ap);
    for(char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
      {
	if(*p == '\n')
	  write('\r');
	write(*p);
      }
    va_end(ap);
  }

};

