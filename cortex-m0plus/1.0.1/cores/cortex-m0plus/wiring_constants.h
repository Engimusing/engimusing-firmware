/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

#ifndef _WIRING_CONSTANTS_
#define _WIRING_CONSTANTS_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#define LOW             (0x0)
#define HIGH            (0x1)

#define GPIO_DISABLED                    (0x00)
#define DISABLED_PULLUP                  (0x01)
#define INPUT                            (0x02)
#define INPUT_PULLUP                     (0x03)
#define INPUT_PULLDOWN                   (0x04)
#define INPUT_FILTER                     (0x05)
#define INPUT_PU_FILTER                  (0x06)
#define INPUT_PD_FILTER                  (0x07)
#define WIRED_OR                         (0x08)
#define WIRED_OR_PULLDOWN                (0x09)
#define OUTPUT                           (0x0A)
#define OUTPUT_LOWEST_DRIVE              (0x0B)
#define OUTPUT_LOW_DRIVE                 (0x0C)
#define OUTPUT_HIGH_DRIVE                (0x0D)
#define WIRED_AND                        (0x0E)
#define WIRED_AND_LOWEST_DRIVE           (0x0F)
#define WIRED_AND_LOW_DRIVE              (0x10)
#define WIRED_AND_HIGH_DRIVE             (0x11)
#define WIRED_AND_FILTER                 (0x12)
#define WIRED_AND_FILTER_LOWEST_DRIVE    (0x13)
#define WIRED_AND_FILTER_LOW_DRIVE       (0x14)
#define WIRED_AND_FILTER_HIGH_DRIVE      (0x15)
#define WIRED_AND_PULLUP                 (0x16)
#define WIRED_AND_PULLUP_LOWEST_DRIVE    (0x17)
#define WIRED_AND_PULLUP_LOW_DRIVE       (0x18)
#define WIRED_AND_PULLUP_HIGH_DRIVE      (0x19)
#define WIRED_AND_PU_FILTER              (0x1A)
#define WIRED_AND_PU_FILTER_LOWEST_DRIVE (0x1B)
#define WIRED_AND_PU_FILTER_LOW_DRIVE    (0x1C)
#define WIRED_AND_PU_FILTER_HIGH_DRIVE   (0x1D)



#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _WIRING_CONSTANTS_ */
