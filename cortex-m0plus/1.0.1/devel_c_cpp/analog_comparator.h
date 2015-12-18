/*
  Copyright (c) 2014-2015 Engimusing LLC.  All right reserved.

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

#ifndef _VARIANT_ACMP_
#define _VARIANT_ACMP_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ACMP_NO_HYSTERESIS              (ACMP_CTRL_HYSTSEL_HYST0)
#define ACMP_HYSTERESIS_15MV            (ACMP_CTRL_HYSTSEL_HYST1)
#define ACMP_HYSTERESIS_22MV            (ACMP_CTRL_HYSTSEL_HYST2)
#define ACMP_HYSTERESIS_29MV            (ACMP_CTRL_HYSTSEL_HYST3)
#define ACMP_HYSTERESIS_36MV            (ACMP_CTRL_HYSTSEL_HYST4)
#define ACMP_HYSTERESIS_43MV            (ACMP_CTRL_HYSTSEL_HYST5)
#define ACMP_HYSTERESIS_50MV            (ACMP_CTRL_HYSTSEL_HYST6)
#define ACMP_HYSTERESIS_57MV            (ACMP_CTRL_HYSTSEL_HYST7)

#define ACMP_WARMTIME_4CYCLES    (ACMP_CTRL_WARMTIME_4CYCLES)
#define ACMP_WARMTIME_8CYCLES    (ACMP_CTRL_WARMTIME_8CYCLES)
#define ACMP_WARMTIME_16CYCLES   (ACMP_CTRL_WARMTIME_16CYCLES)
#define ACMP_WARMTIME_32CYCLES   (ACMP_CTRL_WARMTIME_32CYCLES)
#define ACMP_WARMTIME_64CYCLES   (ACMP_CTRL_WARMTIME_64CYCLES)
#define ACMP_WARMTIME_128CYCLES  (ACMP_CTRL_WARMTIME_128CYCLES)
#define ACMP_WARMTIME_256CYCLES  (ACMP_CTRL_WARMTIME_256CYCLES)
#define ACMP_WARMTIME_512CYCLES  (ACMP_CTRL_WARMTIME_512CYCLES)

#define ACMP0_INTERRUPT_RISING_EDGE   (ACMP_CTRL_IRISE)
#define ACMP0_INTERRUPT_FALLING_EDGE  (ACMP_CTRL_IFALL)
#define ACMP0_INTERRUPT_BOTH_EDGES    (ACMP_CTRL_IRISE | ACMP_CTRL_IFALL)

#define ACMP_CTRL_FULLBIAS_ON         (ACMP_CTRL_FULLBIAS)
#define ACMP_CTRL_FULLBIAS_OFF        (0x00)
#define ACMP_CTRL_HALFBIAS_ON         (ACMP_CTRL_HALFBIAS)
#define ACMP_CTRL_HALFBIAS_OFF        (0x00)


#endif
