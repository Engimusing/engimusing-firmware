///
///@file efm_wdog.c
///@brief Defines for accessing the WDOG peripheral
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
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
#include "io_types.h"

typedef struct
{
  __IO uint32_t CTRL;     // Control Register
  __IO uint32_t CMD;      // Command Register
   __I uint32_t SYNCBUSY; // Synchronization Busy Register
} WDOG_TypeDef;

#define WDOG          ((WDOG_TypeDef *) 0x40088000UL)    // WDOG base pointer

// Watchdog period selection
typedef enum
{
  wdogPeriod_9    = 0x0, // 9 clock periods
  wdogPeriod_17   = 0x1, // 17 clock periods
  wdogPeriod_33   = 0x2, // 33 clock periods
  wdogPeriod_65   = 0x3, // 65 clock periods
  wdogPeriod_129  = 0x4, // 129 clock periods
  wdogPeriod_257  = 0x5, // 257 clock periods
  wdogPeriod_513  = 0x6, // 513 clock periods
  wdogPeriod_1k   = 0x7, // 1025 clock periods
  wdogPeriod_2k   = 0x8, // 2049 clock periods
  wdogPeriod_4k   = 0x9, // 4097 clock periods
  wdogPeriod_8k   = 0xA, // 8193 clock periods
  wdogPeriod_16k  = 0xB, // 16385 clock periods
  wdogPeriod_32k  = 0xC, // 32769 clock periods
  wdogPeriod_64k  = 0xD, // 65537 clock periods
  wdogPeriod_128k = 0xE, // 131073 clock periods
  wdogPeriod_256k = 0xF  // 262145 clock periods
} WDOG_PeriodSel_TypeDef;

// Bit fields for WDOG CTRL
#define WDOG_CTRL_RESETVALUE             0x00000F00UL    // Default value for WDOG_CTRL
#define WDOG_CTRL_MASK                   0x00003F7FUL    // Mask for WDOG_CTRL
#define WDOG_CTRL_EN                     (0x1UL << 0)    // Watchdog Timer Enable
#define WDOG_CTRL_DEBUGRUN               (0x1UL << 1)    // Debug Mode Run Enable
#define WDOG_CTRL_EM2RUN                 (0x1UL << 2)    // Energy Mode 2 Run Enable
#define WDOG_CTRL_EM3RUN                 (0x1UL << 3)    // Energy Mode 3 Run Enable
#define WDOG_CTRL_LOCK                   (0x1UL << 4)    // Configuration lock
#define WDOG_CTRL_EM4BLOCK               (0x1UL << 5)    // Energy Mode 4 Block
#define WDOG_CTRL_SWOSCBLOCK             (0x1UL << 6)    // Software Oscillator Disable Block
#define WDOG_CTRL_SWOSCBLOCK_MASK              0x40UL    // Bit mask for WDOG_SWOSCBLOCK
#define WDOG_CTRL_SWOSCBLOCK_DEFAULT     0x00000000UL    // Mode DEFAULT for WDOG_CTRL
#define WDOG_CTRL_PERSEL_MASK                 0xF00UL    // Bit mask for WDOG_PERSEL
#define WDOG_CTRL_PERSEL_DEFAULT         0x0000000FUL    // Mode DEFAULT for WDOG_CTRL
#define WDOG_CTRL_CLKSEL_MASK                0x3000UL    // Bit mask for WDOG_CLKSEL
#define WDOG_CTRL_CLKSEL_DEFAULT (0x00000000UL << 12)    // Shifted mode DEFAULT for WDOG_CTRL
#define WDOG_CTRL_CLKSEL_ULFRCO  (0x00000000UL << 12)    // Shifted mode ULFRCO for WDOG_CTRL
#define WDOG_CTRL_CLKSEL_LFRCO   (0x00000001UL << 12)    // Shifted mode LFRCO for WDOG_CTRL
#define WDOG_CTRL_CLKSEL_LFXO    (0x00000002UL << 12)    // Shifted mode LFXO for WDOG_CTRL

// Bit fields for WDOG CMD
#define WDOG_CMD_RESETVALUE              0x00000000UL    // Default value for WDOG_CMD
#define WDOG_CMD_MASK                    0x00000001UL    // Mask for WDOG_CMD
#define WDOG_CMD_CLEAR                   (0x1UL << 0)    // Watchdog Timer Clear
#define WDOG_CMD_CLEAR_DEFAULT           0x00000000UL    // Mode DEFAULT for WDOG_CMD
#define WDOG_CMD_CLEAR_UNCHANGED         0x00000000UL    // Mode UNCHANGED for WDOG_CMD
#define WDOG_CMD_CLEAR_CLEARED           0x00000001UL    // Mode CLEARED for WDOG_CMD

// Bit fields for WDOG SYNCBUSY
#define _WDOG_SYNCBUSY_RESETVALUE        0x00000000UL    // Default value for WDOG_SYNCBUSY
#define _WDOG_SYNCBUSY_MASK              0x00000003UL    // Mask for WDOG_SYNCBUSY
#define WDOG_SYNCBUSY_CTRL               (0x1UL << 0)    // CTRL Register Busy
#define WDOG_SYNCBUSY_CMD                (0x1UL << 1)    // CMD Register Busy

void WDOG_Feed(void);
void initWdog(void);

