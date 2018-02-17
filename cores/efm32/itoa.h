///
///@file itoa.h
///@brief utility functions for converting from number formats to strings (char*)
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

#ifdef __cplusplus
extern "C"{
#endif

//extern void itoa( int n, char s[] ) ;

///@brief Convert from int to character array
///@param [in] value integer value to convert from
///@param [in] string character array to use as output
///@param [in] radix base for the string result, needs to be less than or equal to 36 and greater than 1
///@return resulting character array (same as string input value)
extern char* itoa( int value, char *string, int radix ) ;

///@brief Convert from long to character array
///@param [in] value long integer value to convert from
///@param [in] string character array to use as output
///@param [in] radix base for the string result, needs to be less than or equal to 36 and greater than 1
///@return resulting character array (same as string input value)
extern char* ltoa( long value, char *string, int radix ) ;

///@brief Convert from unsigned long to character array
///@param [in] value integer value to convert from
///@param [in] string character array to use as output
///@param [in] radix base for the string result, needs to be less than or equal to 36 and greater than 1
///@return resulting character array (same as string input value)
extern char* utoa( unsigned long value, char *string, int radix ) ;

///@brief Convert from unsigned long to character array
///@param [in] value integer value to convert from
///@param [in] string character array to use as output
///@param [in] radix base for the string result, needs to be less than or equal to 36 and greater than 1
///@return resulting character array (same as string input value)
extern char* ultoa( unsigned long value, char *string, int radix ) ;

///@brief Alternative function to atof which does not use doubles
///@param [in] payload string to parse the float out of
///@return float value parsed from the string
///@details atof is much too large of a function to use on the Energy Micros
/// This is a simpler version that only handles floats with a '.' (so no alternate locals that use ',')
/// It also does not handle scientific notation but it should handle the full range of floats
extern float atofLocal(const char* payload);
#ifdef __cplusplus
} // extern "C"
#endif

