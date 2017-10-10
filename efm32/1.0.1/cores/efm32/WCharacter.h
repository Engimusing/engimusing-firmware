///
///@file WCharacter.h
///@brief Utility functions that wrap character utility functions from the main c library
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

#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

// WCharacter.h prototypes
#if defined (  __GNUC__  )
inline boolean isAlphaNumeric(int c) __attribute__((always_inline));
inline boolean isAlpha(int c) __attribute__((always_inline));
inline boolean isAscii(int c) __attribute__((always_inline));
inline boolean isWhitespace(int c) __attribute__((always_inline));
inline boolean isControl(int c) __attribute__((always_inline));
inline boolean isDigit(int c) __attribute__((always_inline));
inline boolean isGraph(int c) __attribute__((always_inline));
inline boolean isLowerCase(int c) __attribute__((always_inline));
inline boolean isPrintable(int c) __attribute__((always_inline));
inline boolean isPunct(int c) __attribute__((always_inline));
inline boolean isSpace(int c) __attribute__((always_inline));
inline boolean isUpperCase(int c) __attribute__((always_inline));
inline boolean isHexadecimalDigit(int c) __attribute__((always_inline));
inline int toAscii(int c) __attribute__((always_inline));
inline int toLowerCase(int c) __attribute__((always_inline));
inline int toUpperCase(int c)__attribute__((always_inline));
#elif defined ( __ICCARM__ )
#endif

///@brief Checks for an alphanumeric character.
///@param [in] c character to check
///@return true if the character is alpha or numeric
///@details It is equivalent to (isalpha(c) || isdigit(c)).
inline boolean isAlphaNumeric(int c)
{
  return ( isalnum(c) == 0 ? false : true);
}

///@brief Checks for an alphabetic character.
///@param [in] c character to check
///@return true if the character is alpha
///@details It is equivalent to (isupper(c) || islower(c)).
inline boolean isAlpha(int c)
{
  return ( isalpha(c) == 0 ? false : true);
}


///@brief Checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.
///@param [in] c character to check
///@return true if the character is Ascii
inline boolean isAscii(int c)
{
/*  return ( isascii(c) == 0 ? false : true); */
  return ( (c & ~0x7f) != 0 ? false : true);
}


///@brief Checks for a blank character, that is, a space or a tab.
///@param [in] c character to check
///@return true is the character is blank
inline boolean isWhitespace(int c)
{
  return ( isblank (c) == 0 ? false : true);
}


// Checks for a control character.
///@brief Checks for a control character.
///@param [in] c character to check
///@return true if tHe character is a control character
inline boolean isControl(int c)
{
  return ( iscntrl (c) == 0 ? false : true);
}


///@brief Checks for a digit (0 through 9).
///@param [in] c character to check
///@return true if the character is a digit
inline boolean isDigit(int c)
{
  return ( isdigit (c) == 0 ? false : true);
}

///@brief Checks for any printable character except space.
///@param [in] c character to check
///@return true if the character is a printable character except space
inline boolean isGraph(int c)
{
  return ( isgraph (c) == 0 ? false : true);
}

///@brief Checks for a lower-case character.
///@param [in] c character to check
///@return true if the character is a lowercase character
inline boolean isLowerCase(int c)
{
  return (islower (c) == 0 ? false : true);
}

///@brief Checks for any printable character including space.
///@param [in] c character to check
///@return true if the character is a printable character including space.
inline boolean isPrintable(int c)
{
  return ( isprint (c) == 0 ? false : true);
}


///@brief Checks for any printable character which is not a space or an alphanumeric character.
///@param [in] c character to check
///@return true if the character is a printable character that is not a space or alphanumeric
inline boolean isPunct(int c)
{
  return ( ispunct (c) == 0 ? false : true);
}

// Checks for white-space characters. For the avr-libc library,
// these are: space, formfeed ('\f'), newline ('\n'), carriage
// return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
///@brief Checks for white-space characters.
///@param [in] c character to check 
///@return true if the character is a whitespace character
///@details For the avr-libc library,
/// these are: space, formfeed ('\f'), newline ('\n'), carriage
/// return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
inline boolean isSpace(int c)
{
  return ( isspace (c) == 0 ? false : true);
}

///@brief Checks for an uppercase character.
///@param [in] c character to check
///@return true if the character is a uppercase character
inline boolean isUpperCase(int c)
{
  return ( isupper (c) == 0 ? false : true);
}

///@brief Checks for a hexadecimal digits
///@param [in] c character to check
///@return true if the character is a hexadecimal digit
///@details i.e. one of 0 1 2 3 4 5 6 7
/// 8 9 a b c d e f A B C D E F.
inline boolean isHexadecimalDigit(int c)
{
  return ( isxdigit (c) == 0 ? false : true);
}

///@brief Converts c to a 7-bit unsigned char value that fits into the ASCII character set, by clearing the high-order bits.
///@param [in] c Character to convert  
///@return Converted character in ascii format 
inline int toAscii(int c)
{
/*  return toascii (c); */
  return (c & 0x7f);
}

///@brief Converts the letter c to lower case, if possible.
///@param [in] c Character to convert
///@return Lowercase version of the character
///@details Warning:
/// Many people will be unhappy if you use this function.
/// This function will convert accented letters into random
/// characters.
inline int toLowerCase(int c)
{
  return tolower (c);
}

///@brief Converts the letter c to upper case, if possible.
///@param [in] c Character to convert
///@return uppercase version of the character
inline int toUpperCase(int c)
{
  return toupper (c);
}

#ifdef __cplusplus
}
#endif

