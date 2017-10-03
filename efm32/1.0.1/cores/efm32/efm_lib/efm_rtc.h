///
///@file efm_rtc.h
///@brief Defines for accessing the RTC peripheral
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

#include "io_types.h"

typedef struct
{
  __IO uint32_t CTRL;     // Control Register
  __IO uint32_t CNT;      // Counter Value Register
  __IO uint32_t COMP0;    // Compare Value Register 0
  __IO uint32_t COMP1;    // Compare Value Register 1
  __I uint32_t  IF;       // Interrupt Flag Register
  __IO uint32_t IFS;      // Interrupt Flag Set Register
  __IO uint32_t IFC;      // Interrupt Flag Clear Register
  __IO uint32_t IEN;      // Interrupt Enable Register
  __IO uint32_t FREEZE;   // Freeze Register
  __I uint32_t  SYNCBUSY; // Synchronization Busy Register
} RTC_TypeDef;

#define RTC          ((RTC_TypeDef *) 0x4008000UL)        // RTC base pointer

// Bit fields for RTC CTRL
#define RTC_CTRL_RESETVALUE                      0x0      // Default value for RTC_CTRL
#define RTC_CTRL_EN                     (0x1UL << 0)      // RTC Enable
#define RTC_CTRL_DEBUGRUN               (0x1UL << 1)      // Debug Mode Run Enable
#define RTC_CTRL_COMP0TOP               (0x1UL << 2)      // Compare Channel 0 is Top Value

// Bit fields for RTC CNT
#define RTC_CNT_RESETVALUE                       0x0      // Default value for RTC_CNT
#define RTC_CNT_MASK                    0x00FFFFFFUL      // Mask for RTC_CNT

// Bit fields for RTC COMP0
#define RTC_COMP0_RESETVALUE            0x00000000UL      // Default value for RTC_COMP0
#define RTC_COMP0_MASK                  0x00FFFFFFUL      // Mask for RTC_COMP0

// Bit fields for RTC COMP1
#define RTC_COMP1_RESETVALUE            0x00000000UL      // Default value for RTC_COMP1
#define RTC_COMP1_MASK                  0x00FFFFFFUL      // Mask for RTC_COMP1

// Bit fields for RTC IF
#define RTC_IF_RESETVALUE               0x00000000UL      // Default value for RTC_IF
#define RTC_IF_MASK                     0x00000007UL      // Mask for RTC_IF
#define RTC_IF_OF                       (0x1UL << 0)      // Overflow Interrupt Flag
#define RTC_IF_COMP0                    (0x1UL << 1)      // Compare Match 0 Interrupt Flag
#define RTC_IF_COMP1                    (0x1UL << 2)      // Compare Match 1 Interrupt Flag

// Bit fields for RTC IFS
#define RTC_IFS_RESETVALUE              0x00000000UL      // Default value for RTC_IFS
#define RTC_IFS_MASK                    0x00000007UL      // Mask for RTC_IFS
#define RTC_IFS_OF                      (0x1UL << 0)      // Set Overflow Interrupt Flag
#define RTC_IFS_COMP0                   (0x1UL << 1)      // Set Compare match 0 Interrupt Flag
#define RTC_IFS_COMP1                   (0x1UL << 2)      // Set Compare match 1 Interrupt Flag

// Bit fields for RTC IFC
#define RTC_IFC_RESETVALUE              0x00000000UL      // Default value for RTC_IFC
#define RTC_IFC_MASK                    0x00000007UL      // Mask for RTC_IFC
#define RTC_IFC_OF                      (0x1UL << 0)      // Clear Overflow Interrupt Flag
#define RTC_IFC_COMP0                   (0x1UL << 1)      // Clear Compare match 0 Interrupt Flag
#define RTC_IFC_COMP1                   (0x1UL << 2)      // Clear Compare match 1 Interrupt Flag

// Bit fields for RTC IEN
#define RTC_IEN_RESETVALUE              0x00000000UL      // Default value for RTC_IEN
#define _RTC_IEN_MASK                   0x00000007UL      // Mask for RTC_IEN
#define RTC_IEN_OF                      (0x1UL << 0)      // Overflow Interrupt Enable
#define RTC_IEN_COMP0                   (0x1UL << 1)      // Compare Match 0 Interrupt Enable
#define RTC_IEN_COMP1                   (0x1UL << 2)      // Compare Match 1 Interrupt Enable

// Bit fields for RTC FREEZE
#define RTC_FREEZE_RESETVALUE           0x00000000UL      // Default value for RTC_FREEZE
#define RTC_FREEZE_MASK                 0x00000001UL      // Mask for RTC_FREEZE
#define RTC_FREEZE_REGFREEZE            (0x1UL << 0)      // Register Update Freeze

// Bit fields for RTC SYNCBUSY
#define RTC_SYNCBUSY_RESETVALUE         0x00000000UL      // Default value for RTC_SYNCBUSY
#define _RTC_SYNCBUSY_MASK              0x00000007UL      // Mask for RTC_SYNCBUSY
#define RTC_SYNCBUSY_CTRL               (0x1UL << 0)      // CTRL Register Busy
#define RTC_SYNCBUSY_COMP0              (0x1UL << 1)      // COMP0 Register Busy
#define RTC_SYNCBUSY_COMP1              (0x1UL << 2)      // COMP1 Register Busy

