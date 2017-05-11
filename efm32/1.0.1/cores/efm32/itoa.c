/*
  Copyright (c) 2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "itoa.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* reverse:  reverse string s in place */
/*
static void reverse( char s[] )
{
  int i, j ;
  char c ;

  for ( i = 0, j = strlen(s)-1 ; i < j ; i++, j-- )
  {
    c = s[i] ;
    s[i] = s[j] ;
    s[j] = c ;
  }
}
*/

/* itoa:  convert n to characters in s */
/*
extern void itoa( int n, char s[] )
{
  int i, sign ;

  if ( (sign = n) < 0 )  // record sign
  {
    n = -n;          // make n positive
  }

  i = 0;
  do
  {       // generate digits in reverse order
    s[i++] = n % 10 + '0';   // get next digit
  } while ((n /= 10) > 0) ;     // delete it

  if (sign < 0 )
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  reverse( s ) ;
}
*/

extern char* itoa( int value, char *string, int radix )
{
  return ltoa( value, string, radix ) ;
}

extern char* ltoa( long value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char *sp;

  if ( string == NULL )
  {
    return 0 ;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0 ;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
  {
    v = -value;
  }
  else
  {
    v = (unsigned long)value;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

extern char* utoa( unsigned long value, char *string, int radix )
{
  return ultoa( value, string, radix ) ;
}

extern char* ultoa( unsigned long value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v = value;
  char *sp;

  if ( string == NULL )
  {
    return 0;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;


  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}


//atof is much too large of a function to use on the Energy Micros
// This is a simpler version that only handles floats with a '.' (so no alternalte locals that use ',')
// It also does not handle scientific notation but it should handle the full range of floats
extern float atofLocal(const char* payload)
{
      int i = 0;
      
      //handle the integer portion of the float
      char integerString[40];
      integerString[0] = '\0';
      int intLen = 0;
      int maxIntegerDigits = 9;
      int largeFloat = 0;
      for(i = 0; i < 40 && payload[i] != '\0'; i++)
      {
          if((payload[i] <= '9' && payload[i] >= '0') || (i == 0 && payload[i] == '-'))
          {
                intLen++;
                if(intLen >= maxIntegerDigits)
                {
                    largeFloat = 1;
                }else
                {
                    integerString[intLen - 1] = payload[i];
                    integerString[intLen] = '\0';
                }
          }
          else if(payload[i] == '.') 
          {
            break;
          }    
          else if(payload[i] == ' ')
          {
             break;
          }
          else
          {
             return 0.0f;
          }
      }
      
      
      //handle the decimal portion of the float
      char decimalString[40];
      decimalString[0] = '\0';
      int decLen = 0;
      int foundNonZero = 0;
      int maxDecimalDigits = 9;
      int curDecIdx = 0;
      if(payload[i] == '.' && largeFloat == 0)
      {
           for(i++; i < 40 && payload[i] != '\0'; i++)
          {
              if(payload[i] <= '9' && payload[i] >= '0')
              {
                  if(payload[i] > '0')
                  {
                      foundNonZero = 1;
                  }else if(foundNonZero == 0)
                  {
                      maxDecimalDigits++;
                  }
                    decLen++;
                    if(decLen < maxDecimalDigits)
                    {
                        if(foundNonZero == 1)
                        {
                            curDecIdx++;
                            decimalString[curDecIdx - 1] = payload[i];
                            decimalString[curDecIdx] = '\0';
                        }
                    }
                    else
                    {
                        decLen = maxDecimalDigits - 1;
                        break;
                    }
              }  
              else if(payload[i] == ' ')
              {
                 break;
              }
              else
              {
                 return 0.0f;
              }
          }
      }
      
      
      float integer = 0;
      float decimal = 0.0f;
      
      if(foundNonZero == 0)
      {
          integer = (float)atoi(integerString);
          decimal = 0.0f;
          if(largeFloat)
          {
              float multiplier = 1;
              while(intLen - maxIntegerDigits >= 0)
              {
                  multiplier *= 10;
                  intLen--;
              }

              integer *= multiplier;
          }

      }
      else
      {
          integer = atoi(integerString);
          decimal = (float)atoi(decimalString);
          
          float divider = 1;
          while(decLen > 0)
          {
              divider *= 10;
              decLen--;
          }

          decimal /= divider;
          
          if(payload[0] == '-')
          {
              decimal *= -1;
          }
      }
      
      return ((float)integer) + decimal;
}    

#ifdef __cplusplus
} // extern "C"
#endif
