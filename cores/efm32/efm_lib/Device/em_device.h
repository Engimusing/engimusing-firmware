/**************************************************************************//**
 * @file em_device.h
 * @brief CMSIS Cortex-M Peripheral Access Layer for Silicon Laboratories
 *        microcontroller devices
 *
 * This is a convenience header file for defining the part number on the
 * build command line, instead of specifying the part specific header file.
 *
 * @verbatim
 * Example: Add "-DEFM32G890F128" to your build options, to define part
 *          Add "#include "em_device.h" to your source files
 * @endverbatim
 * @version 3.20.7
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Laboratories, Inc. http://www.silabs.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Laboratories, Inc.
 * has no obligation to support this Software. Silicon Laboratories, Inc. is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of
 * merchantability or fitness for any particular purpose or warranties against
 * infringement of any proprietary rights of a third party.
 *
 * Silicon Laboratories, Inc. will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 *
 *****************************************************************************/

#pragma once

#if defined(EFM32ZG108F32)
#include "../Device/EFM32ZG/Include/efm32zg108f32.h"

#elif defined(EFM32ZG222F32)
#include "../Device/EFM32ZG/Include/efm32zg222f32.h"

#elif defined(EFM32TG110F32)
#include "../Device/EFM32TG/Include/efm32tg110f32.h"

#elif defined(EFM32TG222F32)
#include "../Device/EFM32TG/Include/efm32tg222f32.h"

#elif defined(EFM32G232F64)
#include "../Device/EFM32G/Include/efm32g232f64.h"

#elif defined(EFM32G232F128)
#include "../Device/EFM32G/Include/efm32g232f128.h"

#elif defined(EFM32WG840F256)
#include "../Device/EFM32WG/Include/efm32wg840f256.h"

#elif defined(EFM32WG842F256)
#include "../Device/EFM32WG/Include/efm32wg842f256.h"

#elif defined(EFM32WG842F64)
#include "../Device/EFM32WG/Include/efm32wg842f64.h"

#else
#error "em_device.h: PART NUMBER undefined"
#endif


