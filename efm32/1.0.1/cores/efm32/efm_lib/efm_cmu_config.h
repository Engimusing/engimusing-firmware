///
///@file efm_cmu_config.h
///@brief Header redirect for em_cmu.h
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

#include "./emlib/inc/em_cmu.h"

#ifdef __cplusplus
extern "C" {
#endif

  uint32_t cmu_hfper_freq_get(void);
  
  #ifdef __cplusplus
}
#endif


// Unused code below. Can probably be removed. Next time I clean up this file I will remove it.
#if 0
#include "io_types.h"
#include <stdint.h>
#include "efm_msc.h"
#include "efm_emu.h"

typedef struct
{
  __IO uint32_t CTRL;         // CMU Control Register
  __IO uint32_t HFCORECLKDIV; // High Frequency Core Clock Division Register
  __IO uint32_t HFPERCLKDIV;  // High Frequency Peripheral Clock Division Register
  __IO uint32_t HFRCOCTRL;    // HFRCO Control Register
  __IO uint32_t LFRCOCTRL;    // LFRCO Control Register
  __IO uint32_t AUXHFRCOCTRL; // AUXHFRCO Control Register
  __IO uint32_t CALCTRL;      // Calibration Control Register
  __IO uint32_t CALCNT;       // Calibration Counter Register
  __IO uint32_t OSCENCMD;     // Oscillator Enable/Disable Command Register
  __IO uint32_t CMD;          // Command Register
  __IO uint32_t LFCLKSEL;     // Low Frequency Clock Select Register
  __I uint32_t  STATUS;       // Status Register 
  __I uint32_t  IF;           // Interrupt Flag Register 
  __IO uint32_t IFS;          // Interrupt Flag Set Register 
  __IO uint32_t IFC;          // Interrupt Flag Clear Register 
  __IO uint32_t IEN;          // Interrupt Enable Register 
  __IO uint32_t HFCORECLKEN0; // High Frequency Core Clock Enable Register 0 
  __IO uint32_t HFPERCLKEN0;  // High Frequency Peripheral Clock Enable Register 0 
  uint32_t RESERVED0[2]; // Reserved for future use **/
  __I  uint32_t SYNCBUSY;     // Synchronization Busy Register 
  __IO uint32_t FREEZE;       // Freeze Register 
  __IO uint32_t LFACLKEN0;    // Low Frequency A Clock Enable Register 0  (Async Reg) 
  uint32_t RESERVED1[1]; // Reserved for future use **/
  __IO uint32_t LFBCLKEN0;    // Low Frequency B Clock Enable Register 0 (Async Reg) 
  uint32_t RESERVED2[1]; // Reserved for future use **/
  __IO uint32_t LFAPRESC0;    // Low Frequency A Prescaler Register 0 (Async Reg) 
  uint32_t RESERVED3[1]; // Reserved for future use **/
  __IO uint32_t LFBPRESC0;    // Low Frequency B Prescaler Register 0  (Async Reg) 
  uint32_t RESERVED4[1]; // Reserved for future use **/
  __IO uint32_t PCNTCTRL;     // PCNT Control Register 
  uint32_t RESERVED5[1]; // Reserved for future use
  __IO uint32_t ROUTE;        // I/O Routing Register 
  __IO uint32_t LOCK;         // Configuration Lock Register 
} CMU_TypeDef;


#define CMU  ((CMU_TypeDef *) 0x400C8000UL) // CMU base address

// Bit fields for CMU CTRL
#define CMU_CTRL_RESETVALUE                           0x000C262CUL  // Default value for CMU_CTRL
#define CMU_CTRL_MASK                                 0x03FE3EEFUL  // Mask for CMU_CTRL

#define CMU_CTRL_HFXOMODE_MASK                               0x3UL  // Bit mask for CMU_HFXOMODE
#define CMU_CTRL_HFXOMODE_DEFAULT                     0x00000000UL  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_HFXOMODE_XTAL                        0x00000000UL  // Mode XTAL for CMU_CTRL
#define CMU_CTRL_HFXOMODE_BUFEXTCLK                   0x00000001UL  // Mode BUFEXTCLK for CMU_CTRL
#define CMU_CTRL_HFXOMODE_DIGEXTCLK                   0x00000002UL  // Mode DIGEXTCLK for CMU_CTRL

#define CMU_CTRL_HFXOBOOST_SHIFT                                 2  // Shift value for CMU_HFXOBOOST
#define CMU_CTRL_HFXOBOOST_MASK                              0xCUL  // Bit mask for CMU_HFXOBOOST
#define CMU_CTRL_HFXOBOOST_50PCENT             (0x00000000UL << 2)  // Mode 50PCENT for CMU_CTRL
#define CMU_CTRL_HFXOBOOST_70PCENT             (0x00000001UL << 2)  // Mode 70PCENT for CMU_CTRL
#define CMU_CTRL_HFXOBOOST_80PCENT             (0x00000002UL << 2)  // Mode 80PCENT for CMU_CTRL
#define CMU_CTRL_HFXOBOOST_DEFAULT             (0x00000003UL << 2)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_HFXOBOOST_100PCENT            (0x00000003UL << 2)  // Mode 100PCENT for CMU_CTRL

#define CMU_CTRL_HFXOBUFCUR_SHIFT                                5  // Shift value for CMU_HFXOBUFCUR
#define CMU_CTRL_HFXOBUFCUR_MASK                            0x60UL  // Bit mask for CMU_HFXOBUFCUR
#define CMU_CTRL_HFXOBUFCUR_DEFAULT            (0x00000001UL << 5)  // Shifted mode DEFAULT for CMU_CTRL
#define CMU_CTRL_HFXOGLITCHDETEN                      (0x1UL << 7)  // HFXO Glitch Detector Enable

#define CMU_CTRL_HFXOGLITCHDETEN_SHIFT                           7  // Shift value for CMU_HFXOGLITCHDETEN
#define CMU_CTRL_HFXOGLITCHDETEN_MASK                       0x80UL  // Bit mask for CMU_HFXOGLITCHDETEN
#define CMU_CTRL_HFXOGLITCHDETEN_DEFAULT              0x00000000UL  // Mode DEFAULT for CMU_CTRL

#define CMU_CTRL_HFXOTIMEOUT_SHIFT                               9  // Shift value for CMU_HFXOTIMEOUT
#define CMU_CTRL_HFXOTIMEOUT_MASK                          0x600UL  // Bit mask for CMU_HFXOTIMEOUT
#define CMU_CTRL_HFXOTIMEOUT_8CYCLES           (0x00000000UL << 9)  // Mode 8CYCLES for CMU_CTRL
#define CMU_CTRL_HFXOTIMEOUT_256CYCLES         (0x00000001UL << 9)  // Mode 256CYCLES for CMU_CTRL
#define CMU_CTRL_HFXOTIMEOUT_1KCYCLES          (0x00000002UL << 9)  // Mode 1KCYCLES for CMU_CTRL
#define CMU_CTRL_HFXOTIMEOUT_DEFAULT           (0x00000003UL << 9)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_HFXOTIMEOUT_16KCYCLES         (0x00000003UL << 9)  // Mode 16KCYCLES for CMU_CTRL

#define CMU_CTRL_LFXOMODE_SHIFT                                 11  // Shift value for CMU_LFXOMODE
#define CMU_CTRL_LFXOMODE_MASK                            0x1800UL  // Bit mask for CMU_LFXOMODE
#define CMU_CTRL_LFXOMODE_DEFAULT             (0x00000000UL << 11)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_LFXOMODE_XTAL                (0x00000000UL << 11)  // Mode XTAL for CMU_CTRL
#define CMU_CTRL_LFXOMODE_BUFEXTCLK           (0x00000001UL << 11)  // Mode BUFEXTCLK for CMU_CTRL
#define CMU_CTRL_LFXOMODE_DIGEXTCLK           (0x00000002UL << 11)  // Mode DIGEXTCLK for CMU_CTRL

#define CMU_CTRL_LFXOBOOST                           (0x1UL << 13)  // LFXO Start-up Boost Current

#define CMU_CTRL_LFXOBOOST_SHIFT                                13  // Shift value for CMU_LFXOBOOST
#define CMU_CTRL_LFXOBOOST_MASK                           0x2000UL  // Bit mask for CMU_LFXOBOOST
#define CMU_CTRL_LFXOBOOST_70PCENT             (0x00000000UL << 13)  // Mode 70PCENT for CMU_CTRL
#define CMU_CTRL_LFXOBOOST_DEFAULT             (0x00000001UL << 13)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_LFXOBOOST_100PCENT            (0x00000001UL << 13)  // Mode 100PCENT for CMU_CTRL

#define CMU_CTRL_LFXOBUFCUR                           (0x1UL << 17)  // LFXO Boost Buffer Current

#define CMU_CTRL_LFXOTIMEOUT_SHIFT                               18  // Shift value for CMU_LFXOTIMEOUT
#define CMU_CTRL_LFXOTIMEOUT_MASK                         0xC0000UL  // Bit mask for CMU_LFXOTIMEOUT
#define CMU_CTRL_LFXOTIMEOUT_8CYCLES           (0x00000000UL << 18)  // Mode 8CYCLES for CMU_CTRL
#define CMU_CTRL_LFXOTIMEOUT_1KCYCLES          (0x00000001UL << 18)  // Mode 1KCYCLES for CMU_CTRL
#define CMU_CTRL_LFXOTIMEOUT_16KCYCLES         (0x00000002UL << 18)  // Mode 16KCYCLES for CMU_CTRL
#define CMU_CTRL_LFXOTIMEOUT_DEFAULT           (0x00000003UL << 18)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_LFXOTIMEOUT_32KCYCLES         (0x00000003UL << 18)  // Mode 32KCYCLES for CMU_CTRL

#define CMU_CTRL_CLKOUTSEL0_SHIFT                                20  // Shift value for CMU_CLKOUTSEL0
#define CMU_CTRL_CLKOUTSEL0_MASK                         0x700000UL  // Bit mask for CMU_CLKOUTSEL0
#define CMU_CTRL_CLKOUTSEL0_DEFAULT            (0x00000000UL << 20)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFRCO              (0x00000000UL << 20)  // Mode HFRCO for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFXO               (0x00000001UL << 20)  // Mode HFXO for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFCLK2             (0x00000002UL << 20)  // Mode HFCLK2 for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFCLK4             (0x00000003UL << 20)  // Mode HFCLK4 for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFCLK8             (0x00000004UL << 20)  // Mode HFCLK8 for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_HFCLK16            (0x00000005UL << 20)  // Mode HFCLK16 for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_ULFRCO             (0x00000006UL << 20)  // Mode ULFRCO for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL0_AUXHFRCO           (0x00000007UL << 20)  // Mode AUXHFRCO for CMU_CTRL

#define CMU_CTRL_CLKOUTSEL1_SHIFT                                23  // Shift value for CMU_CLKOUTSEL1
#define CMU_CTRL_CLKOUTSEL1_MASK                        0x3800000UL  // Bit mask for CMU_CLKOUTSEL1
#define CMU_CTRL_CLKOUTSEL1_DEFAULT            (0x00000000UL << 23)  // Mode DEFAULT for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_LFRCO              (0x00000000UL << 23)  // Mode LFRCO for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_LFXO               (0x00000001UL << 23)  // Mode LFXO for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_HFCLK              (0x00000002UL << 23)  // Mode HFCLK for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_LFXOQ              (0x00000003UL << 23)  // Mode LFXOQ for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_HFXOQ              (0x00000004UL << 23)  // Mode HFXOQ for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_LFRCOQ             (0x00000005UL << 23)  // Mode LFRCOQ for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_HFRCOQ             (0x00000006UL << 23)  // Mode HFRCOQ for CMU_CTRL
#define CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ          (0x00000007UL << 23)  // Mode AUXHFRCOQ for CMU_CTRL

// Bit fields for CMU HFCORECLKDIV
#define CMU_HFCORECLKDIV_RESETVALUE                    0x00000000UL  // Default value for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_MASK                          0x0000010FUL  // Mask for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_MASK                    0xFUL  // Bit mask for CMU_HFCORECLKDIV

#define CMU_HFCORECLKDIV_HFCORECLKDIV_DEFAULT          0x00000000UL  // Mode DEFAULT for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK            0x00000000UL  // Mode HFCLK for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK2           0x00000001UL  // Mode HFCLK2 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK4           0x00000002UL  // Mode HFCLK4 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK8           0x00000003UL  // Mode HFCLK8 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK16          0x00000004UL  // Mode HFCLK16 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK32          0x00000005UL  // Mode HFCLK32 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK64          0x00000006UL  // Mode HFCLK64 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK128         0x00000007UL  // Mode HFCLK128 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK256         0x00000008UL  // Mode HFCLK256 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKDIV_HFCLK512         0x00000009UL  // Mode HFCLK512 for CMU_HFCORECLKDIV

#define CMU_HFCORECLKDIV_HFCORECLKLEDIV                (0x1UL << 8)  // Additional Division Factor For HFCORECLKLE
#define CMU_HFCORECLKDIV_HFCORECLKLEDIV_SHIFT                     8  // Shift value for CMU_HFCORECLKLEDIV
#define CMU_HFCORECLKDIV_HFCORECLKLEDIV_MASK                0x100UL  // Bit mask for CMU_HFCORECLKLEDIV
#define CMU_HFCORECLKDIV_HFCORECLKLEDIV_DEFAULT (0x00000000UL << 8)  // Mode DEFAULT for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKLEDIV_DIV2    (0x00000000UL << 8)  // Mode DIV2 for CMU_HFCORECLKDIV
#define CMU_HFCORECLKDIV_HFCORECLKLEDIV_DIV4    (0x00000001UL << 8)  // Mode DIV4 for CMU_HFCORECLKDIV


// Bit fields for CMU HFPERCLKDIV
#define CMU_HFPERCLKDIV_RESETVALUE                     0x00000100UL  // Default value for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_MASK                           0x0000010FUL  // Mask for CMU_HFPERCLKDIV

#define CMU_HFPERCLKDIV_HFPERCLKDIV_MASK                      0xFUL  // Bit mask for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_DEFAULT            0x00000000UL  // Mode DEFAULT for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK              0x00000000UL  // Mode HFCLK for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK2             0x00000001UL  // Mode HFCLK2 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK4             0x00000002UL  // Mode HFCLK4 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK8             0x00000003UL  // Mode HFCLK8 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK16            0x00000004UL  // Mode HFCLK16 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK32            0x00000005UL  // Mode HFCLK32 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK64            0x00000006UL  // Mode HFCLK64 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK128           0x00000007UL  // Mode HFCLK128 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK256           0x00000008UL  // Mode HFCLK256 for CMU_HFPERCLKDIV
#define CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK512           0x00000009UL  // Mode HFCLK512 for CMU_HFPERCLKDIV

#define CMU_HFPERCLKDIV_HFPERCLKEN                     (0x1UL << 8)  // HFPERCLK Enable

// Bit fields for CMU HFRCOCTRL
#define CMU_HFRCOCTRL_RESETVALUE                       0x00000380UL  // Default value for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_MASK                             0x0001F7FFUL  // Mask for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_TUNING_SHIFT                                0  // Shift value for CMU_TUNING

#define CMU_HFRCOCTRL_TUNING_MASK                            0xFFUL  // Bit mask for CMU_TUNING
#define CMU_HFRCOCTRL_TUNING_DEFAULT                   0x00000080UL  // Mode DEFAULT for CMU_HFRCOCTRL

#define CMU_HFRCOCTRL_BAND_SHIFT                                  8  // Shift value for CMU_BAND
#define CMU_HFRCOCTRL_BAND_MASK                             0x700UL  // Bit mask for CMU_BAND

#define CMU_HFRCOCTRL_BAND_1MHZ                 (0x00000000UL << 8)  // Mode 1MHZ for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_7MHZ                 (0x00000001UL << 8)  // Mode 7MHZ for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_11MHZ                (0x00000002UL << 8)  // Mode 11MHZ for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_DEFAULT              (0x00000003UL << 8)  // Mode DEFAULT for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_14MHZ                (0x00000003UL << 8)  // Mode 14MHZ for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_21MHZ                (0x00000004UL << 8)  // Mode 21MHZ for CMU_HFRCOCTRL
#define CMU_HFRCOCTRL_BAND_28MHZ                (0x00000005UL << 8)  // Mode 28MHZ for CMU_HFRCOCTRL

#define CMU_HFRCOCTRL_SUDELAY_SHIFT                              12  // Shift value for CMU_SUDELAY
#define CMU_HFRCOCTRL_SUDELAY_MASK                        0x1F000UL  // Bit mask for CMU_SUDELAY

// Bit fields for CMU LFRCOCTRL
#define CMU_LFRCOCTRL_RESETVALUE                       0x00000040UL  // Default value for CMU_LFRCOCTRL
#define CMU_LFRCOCTRL_MASK                             0x0000007FUL  // Mask for CMU_LFRCOCTRL
#define CMU_LFRCOCTRL_TUNING_DEFAULT                   0x00000040UL  // Shifted mode DEFAULT for CMU_LFRCOCTRL

// Bit fields for CMU AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_RESETVALUE                    0x00000080UL  // Default value for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_MASK                          0x000007FFUL  // Mask for CMU_AUXHFRCOCTRL

#define CMU_AUXHFRCOCTRL_TUNING_SHIFT                             0  // Shift value for CMU_TUNING
#define CMU_AUXHFRCOCTRL_TUNING_MASK                         0xFFUL  // Bit mask for CMU_TUNING
#define CMU_AUXHFRCOCTRL_TUNING_DEFAULT                0x00000080UL  // Mode DEFAULT for CMU_AUXHFRCOCTRL

#define CMU_AUXHFRCOCTRL_BAND_SHIFT                               8  // Shift value for CMU_BAND
#define CMU_AUXHFRCOCTRL_BAND_MASK                          0x700UL  // Bit mask for CMU_BAND
#define CMU_AUXHFRCOCTRL_BAND_DEFAULT           (0x00000000UL << 8)  // Mode DEFAULT for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_BAND_14MHZ             (0x00000000UL << 8)  // Mode 14MHZ for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_BAND_11MHZ             (0x00000001UL << 8)  // Mode 11MHZ for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_BAND_7MHZ              (0x00000002UL << 8)  // Mode 7MHZ for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_BAND_1MHZ              (0x00000003UL << 8)  // Mode 1MHZ for CMU_AUXHFRCOCTRL
#define CMU_AUXHFRCOCTRL_BAND_21MHZ             (0x00000007UL << 8)  // Mode 21MHZ for CMU_AUXHFRCOCTRL

// Bit fields for CMU CALCTRL
#define CMU_CALCTRL_RESETVALUE                         0x00000000UL  // Default value for CMU_CALCTRL
#define CMU_CALCTRL_MASK                               0x0000007FUL  // Mask for CMU_CALCTRL

#define CMU_CALCTRL_UPSEL_SHIFT                                   0  // Shift value for CMU_UPSEL
#define CMU_CALCTRL_UPSEL_MASK                                0x7UL  // Bit mask for CMU_UPSEL

#define CMU_CALCTRL_UPSEL_DEFAULT                      0x00000000UL  // Mode DEFAULT for CMU_CALCTRL
#define CMU_CALCTRL_UPSEL_HFXO                         0x00000000UL  // Mode HFXO for CMU_CALCTRL
#define CMU_CALCTRL_UPSEL_LFXO                         0x00000001UL  // Mode LFXO for CMU_CALCTRL
#define CMU_CALCTRL_UPSEL_HFRCO                        0x00000002UL  // Mode HFRCO for CMU_CALCTRL
#define CMU_CALCTRL_UPSEL_LFRCO                        0x00000003UL  // Mode LFRCO for CMU_CALCTRL
#define CMU_CALCTRL_UPSEL_AUXHFRCO                     0x00000004UL  // Mode AUXHFRCO for CMU_CALCTRL

#define CMU_CALCTRL_DOWNSEL_SHIFT                                 3  // Shift value for CMU_DOWNSEL
#define CMU_CALCTRL_DOWNSEL_MASK                             0x38UL  // Bit mask for CMU_DOWNSEL

#define CMU_CALCTRL_DOWNSEL_DEFAULT             (0x00000000UL << 3)  // Mode DEFAULT for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_HFCLK               (0x00000000UL << 3)  // Mode HFCLK for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_HFXO                (0x00000001UL << 3)  // Mode HFXO for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_LFXO                (0x00000002UL << 3)  // Mode LFXO for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_HFRCO               (0x00000003UL << 3)  // Mode HFRCO for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_LFRCO               (0x00000004UL << 3)  // Mode LFRCO for CMU_CALCTRL
#define CMU_CALCTRL_DOWNSEL_AUXHFRCO            (0x00000005UL << 3)  // Mode AUXHFRCO for CMU_CALCTRL

#define CMU_CALCTRL_CONT                               (0x1UL << 6)  // Continuous Calibration
#define CMU_CALCTRL_CONT_SHIFT                                    6  // Shift value for CMU_CONT
#define CMU_CALCTRL_CONT_MASK                                0x40UL  // Bit mask for CMU_CONT
#define CMU_CALCTRL_CONT_DEFAULT                       0x00000000UL  // Mode DEFAULT for CMU_CALCTRL

// Bit fields for CMU CALCNT
#define CMU_CALCNT_RESETVALUE                          0x00000000UL  // Default value for CMU_CALCNT
#define CMU_CALCNT_MASK                                0x000FFFFFUL  // Mask for CMU_CALCNT
#define CMU_CALCNT_CALCNT_DEFAULT                      0x00000000UL  // Mode DEFAULT for CMU_CALCNT

// Bit fields for CMU OSCENCMD
#define CMU_OSCENCMD_RESETVALUE                        0x00000000UL  // Default value for CMU_OSCENCMD
#define CMU_OSCENCMD_MASK                              0x000003FFUL  // Mask for CMU_OSCENCMD

#define CMU_OSCENCMD_HFRCOEN                           (0x1UL << 0)  // HFRCO Enable
#define CMU_OSCENCMD_HFRCODIS                          (0x1UL << 1)  // HFRCO Disable
#define CMU_OSCENCMD_HFXOEN                            (0x1UL << 2)  // HFXO Enable
#define CMU_OSCENCMD_HFXODIS                           (0x1UL << 3)  // HFXO Disable
#define CMU_OSCENCMD_AUXHFRCOEN                        (0x1UL << 4)  // AUXHFRCO Enable
#define CMU_OSCENCMD_AUXHFRCODIS                       (0x1UL << 5)  // AUXHFRCO Disable
#define CMU_OSCENCMD_LFRCOEN                           (0x1UL << 6)  // LFRCO Enable
#define CMU_OSCENCMD_LFRCODIS                          (0x1UL << 7)  // LFRCO Disable
#define CMU_OSCENCMD_LFXOEN                            (0x1UL << 8)  // LFXO Enable
#define CMU_OSCENCMD_LFXODIS                           (0x1UL << 9)  // LFXO Disable

// Bit fields for CMU CMD
#define CMU_CMD_RESETVALUE                             0x00000000UL  // Default value for CMU_CMD
#define CMU_CMD_MASK                                   0x0000001FUL  // Mask for CMU_CMD
#define CMU_CMD_HFCLKSEL_MASK                                 0x7UL  // Bit mask for CMU_HFCLKSEL

#define CMU_CMD_HFCLKSEL_DEFAULT                       0x00000000UL  // Mode DEFAULT for CMU_CMD
#define CMU_CMD_HFCLKSEL_HFRCO                         0x00000001UL  // Mode HFRCO for CMU_CMD
#define CMU_CMD_HFCLKSEL_HFXO                          0x00000002UL  // Mode HFXO for CMU_CMD
#define CMU_CMD_HFCLKSEL_LFRCO                         0x00000003UL  // Mode LFRCO for CMU_CMD
#define CMU_CMD_HFCLKSEL_LFXO                          0x00000004UL  // Mode LFXO for CMU_CMD

#define CMU_CMD_CALSTART                               (0x1UL << 3)  // Calibration Start
#define CMU_CMD_CALSTOP                                (0x1UL << 4)  // Calibration Stop

// Bit fields for CMU LFCLKSEL
#define CMU_LFCLKSEL_RESETVALUE                        0x00000005UL  // Default value for CMU_LFCLKSEL
#define CMU_LFCLKSEL_MASK                              0x0011000FUL  // Mask for CMU_LFCLKSEL

#define CMU_LFCLKSEL_LFA_MASK                                 0x3UL  // Bit mask for CMU_LFA
#define CMU_LFCLKSEL_LFA_DISABLED                      0x00000000UL  // Mode DISABLED for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_DEFAULT                       0x00000001UL  // Mode DEFAULT for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_LFRCO                         0x00000001UL  // Mode LFRCO for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_LFXO                          0x00000002UL  // Mode LFXO for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2               0x00000003UL  // Mode HFCORECLKLEDIV2 for CMU_LFCLKSEL

#define CMU_LFCLKSEL_LFB_SHIFT                                    2  // Shift value for CMU_LFB
#define CMU_LFCLKSEL_LFB_MASK                                 0xCUL  // Bit mask for CMU_LFB
#define CMU_LFCLKSEL_LFB_DISABLED               (0x00000000UL << 2)  // Mode DISABLED for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFB_DEFAULT                (0x00000001UL << 2)  // Mode DEFAULT for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFB_LFRCO                  (0x00000001UL << 2)  // Mode LFRCO for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFB_LFXO                   (0x00000002UL << 2)  // Mode LFXO for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2        (0x00000003UL << 2)  // Mode HFCORECLKLEDIV2 for CMU_LFCLKSEL

#define CMU_LFCLKSEL_LFAE                             (0x1UL << 16)  // Clock Select for LFA Extended
#define CMU_LFCLKSEL_LFBE                             (0x1UL << 20)  // Clock Select for LFB Extended

// Bit fields for CMU STATUS
#define CMU_STATUS_RESETVALUE                          0x00000403UL  // Default value for CMU_STATUS
#define CMU_STATUS_MASK                                0x00007FFFUL  // Mask for CMU_STATUS

#define CMU_STATUS_HFRCOENS                            (0x1UL << 0)  // HFRCO Enable Status
#define CMU_STATUS_HFRCORDY                            (0x1UL << 1)  // HFRCO Ready
#define CMU_STATUS_HFXOENS                             (0x1UL << 2)  // HFXO Enable Status
#define CMU_STATUS_HFXORDY                             (0x1UL << 3)  // HFXO Ready
#define CMU_STATUS_AUXHFRCOENS                         (0x1UL << 4)  // AUXHFRCO Enable Status
#define CMU_STATUS_AUXHFRCORDY                         (0x1UL << 5)  // AUXHFRCO Ready
#define CMU_STATUS_LFRCOENS                            (0x1UL << 6)  // LFRCO Enable Status
#define CMU_STATUS_LFRCORDY                            (0x1UL << 7)  // LFRCO Ready
#define CMU_STATUS_LFXOENS                             (0x1UL << 8)  // LFXO Enable Status
#define CMU_STATUS_LFXORDY                             (0x1UL << 9)  // LFXO Ready
#define CMU_STATUS_HFRCOSEL                           (0x1UL << 10)  // HFRCO Selected
#define CMU_STATUS_HFXOSEL                            (0x1UL << 11)  // HFXO Selected
#define CMU_STATUS_LFRCOSEL                           (0x1UL << 12)  // LFRCO Selected
#define CMU_STATUS_LFXOSEL                            (0x1UL << 13)  // LFXO Selected
#define CMU_STATUS_CALBSY                             (0x1UL << 14)  // Calibration Busy

// Bit fields for CMU IF
#define CMU_IF_RESETVALUE                              0x00000001UL  // Default value for CMU_IF
#define CMU_IF_MASK                                    0x0000007FUL  // Mask for CMU_IF
#define CMU_IF_HFRCORDY                                (0x1UL << 0)  // HFRCO Ready Interrupt Flag
#define CMU_IF_HFXORDY                                 (0x1UL << 1)  // HFXO Ready Interrupt Flag
#define CMU_IF_LFRCORDY                                (0x1UL << 2)  // LFRCO Ready Interrupt Flag
#define CMU_IF_LFXORDY                                 (0x1UL << 3)  // LFXO Ready Interrupt Flag
#define CMU_IF_AUXHFRCORDY                             (0x1UL << 4)  // AUXHFRCO Ready Interrupt Flag
#define CMU_IF_CALRDY                                  (0x1UL << 5)  // Calibration Ready Interrupt Flag
#define CMU_IF_CALOF                                   (0x1UL << 6)  // Calibration Overflow Interrupt Flag

// Bit fields for CMU IFS
#define CMU_IFS_RESETVALUE                             0x00000000UL  // Default value for CMU_IFS
#define CMU_IFS_MASK                                   0x0000007FUL  // Mask for CMU_IFS
#define CMU_IFS_HFRCORDY                               (0x1UL << 0)  // HFRCO Ready Interrupt Flag Set
#define CMU_IFS_HFXORDY                                (0x1UL << 1)  // HFXO Ready Interrupt Flag Set
#define CMU_IFS_LFRCORDY                               (0x1UL << 2)  // LFRCO Ready Interrupt Flag Set
#define CMU_IFS_LFXORDY                                (0x1UL << 3)  // LFXO Ready Interrupt Flag Set
#define CMU_IFS_AUXHFRCORDY                            (0x1UL << 4)  // AUXHFRCO Ready Interrupt Flag Set
#define CMU_IFS_CALRDY                                 (0x1UL << 5)  // Calibration Ready Interrupt Flag Set
#define CMU_IFS_CALOF                                  (0x1UL << 6)  // Calibration Overflow Interrupt Flag Set

// Bit fields for CMU IFC
#define CMU_IFC_RESETVALUE                             0x00000000UL  // Default value for CMU_IFC
#define CMU_IFC_MASK                                   0x0000007FUL  // Mask for CMU_IFC
#define CMU_IFC_HFRCORDY                               (0x1UL << 0)  // HFRCO Ready Interrupt Flag Clear
#define CMU_IFC_HFXORDY                                (0x1UL << 1)  // HFXO Ready Interrupt Flag Clear
#define CMU_IFC_LFRCORDY                               (0x1UL << 2)  // LFRCO Ready Interrupt Flag Clear
#define CMU_IFC_LFXORDY                                (0x1UL << 3)  // LFXO Ready Interrupt Flag Clear
#define CMU_IFC_AUXHFRCORDY                            (0x1UL << 4)  // AUXHFRCO Ready Interrupt Flag Clear
#define CMU_IFC_CALRDY                                 (0x1UL << 5)  // Calibration Ready Interrupt Flag Clear
#define CMU_IFC_CALOF                                  (0x1UL << 6)  // Calibration Overflow Interrupt Flag Clear

// Bit fields for CMU IEN
#define CMU_IEN_RESETVALUE                             0x00000000UL  // Default value for CMU_IEN
#define CMU_IEN_MASK                                   0x0000007FUL  // Mask for CMU_IEN
#define CMU_IEN_HFRCORDY                               (0x1UL << 0)  // HFRCO Ready Interrupt Enable
#define CMU_IEN_HFXORDY                                (0x1UL << 1)  // HFXO Ready Interrupt Enable
#define CMU_IEN_LFRCORDY                               (0x1UL << 2)  // LFRCO Ready Interrupt Enable
#define CMU_IEN_LFXORDY                                (0x1UL << 3)  // LFXO Ready Interrupt Enable
#define CMU_IEN_AUXHFRCORDY                            (0x1UL << 4)  // AUXHFRCO Ready Interrupt Enable
#define CMU_IEN_CALRDY                                 (0x1UL << 5)  // Calibration Ready Interrupt Enable
#define CMU_IEN_CALOF                                  (0x1UL << 6)  // Calibration Overflow Interrupt Enable

// Bit fields for CMU HFCORECLKEN0
#define CMU_HFCORECLKEN0_RESETVALUE                    0x00000000UL  // Default value for CMU_HFCORECLKEN0
#define CMU_HFCORECLKEN0_MASK                          0x00000007UL  // Mask for CMU_HFCORECLKEN0
#define CMU_HFCORECLKEN0_AES                           (0x1UL << 0)  // Advanced Encryption Standard Accelerator Clock Enable
#define CMU_HFCORECLKEN0_DMA                           (0x1UL << 1)  // Direct Memory Access Controller Clock Enable
#define CMU_HFCORECLKEN0_LE                            (0x1UL << 2)  // Low Energy Peripheral Interface Clock Enable

// Bit fields for CMU HFPERCLKEN0
#define CMU_HFPERCLKEN0_RESETVALUE                     0x00000000UL  // Default value for CMU_HFPERCLKEN0
#define CMU_HFPERCLKEN0_MASK                           0x00000DDFUL  // Mask for CMU_HFPERCLKEN0
#define CMU_HFPERCLKEN0_TIMER0                         (0x1UL << 0)  // Timer 0 Clock Enable
#define CMU_HFPERCLKEN0_TIMER1                         (0x1UL << 1)  // Timer 1 Clock Enable
#define CMU_HFPERCLKEN0_ACMP0                          (0x1UL << 2)  // Analog Comparator 0 Clock Enable
#define CMU_HFPERCLKEN0_USART1                         (0x1UL << 3)  // Universal Synchronous/Asynchronous Receiver/Transmitter 1 Clock Enable
#define CMU_HFPERCLKEN0_PRS                            (0x1UL << 4)  // Peripheral Reflex System Clock Enable
#define CMU_HFPERCLKEN0_IDAC0                          (0x1UL << 6)  // Current Digital to Analog Converter 0 Clock Enable
#define CMU_HFPERCLKEN0_GPIO                           (0x1UL << 7)  // General purpose Input/Output Clock Enable
#define CMU_HFPERCLKEN0_VCMP                           (0x1UL << 8)  // Voltage Comparator Clock Enable
#define CMU_HFPERCLKEN0_ADC0                          (0x1UL << 10)  // Analog to Digital Converter 0 Clock Enable
#define CMU_HFPERCLKEN0_I2C0                          (0x1UL << 11)  // I2C 0 Clock Enable

// Bit fields for CMU SYNCBUSY
#define CMU_SYNCBUSY_RESETVALUE                        0x00000000UL  // Default value for CMU_SYNCBUSY
#define CMU_SYNCBUSY_MASK                              0x00000055UL  // Mask for CMU_SYNCBUSY
#define CMU_SYNCBUSY_LFACLKEN0                         (0x1UL << 0)  // Low Frequency A Clock Enable 0 Busy
#define CMU_SYNCBUSY_LFAPRESC0                         (0x1UL << 2)  // Low Frequency A Prescaler 0 Busy
#define CMU_SYNCBUSY_LFBCLKEN0                         (0x1UL << 4)  // Low Frequency B Clock Enable 0 Busy
#define CMU_SYNCBUSY_LFBPRESC0                         (0x1UL << 6)  // Low Frequency B Prescaler 0 Busy

// Bit fields for CMU FREEZE
#define CMU_FREEZE_RESETVALUE                          0x00000000UL  // Default value for CMU_FREEZE
#define CMU_FREEZE_REGFREEZE_UPDATE                    0x00000000UL  // Mode UPDATE for CMU_FREEZE
#define CMU_FREEZE_REGFREEZE_FREEZE                    0x00000001UL  // Mode FREEZE for CMU_FREEZE

// Bit fields for CMU LFACLKEN0
#define CMU_LFACLKEN0_RESETVALUE                       0x00000000UL  // Default value for CMU_LFACLKEN0
#define CMU_LFACLKEN0_RTC                              (0x1UL << 0)  // Real-Time Counter Clock Enable

// Bit fields for CMU LFBCLKEN0
#define CMU_LFBCLKEN0_LEUART0                          (0x1UL << 0)  // Low Energy UART 0 Clock Enable

// Bit fields for CMU LFAPRESC0
#define CMU_LFAPRESC0_RTC_MASK                                0xFUL  // Bit mask for CMU_RTC
#define CMU_LFAPRESC0_RTC_DIV1                         0x00000000UL  // Mode DIV1 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV2                         0x00000001UL  // Mode DIV2 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV4                         0x00000002UL  // Mode DIV4 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV8                         0x00000003UL  // Mode DIV8 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV16                        0x00000004UL  // Mode DIV16 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV32                        0x00000005UL  // Mode DIV32 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV64                        0x00000006UL  // Mode DIV64 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV128                       0x00000007UL  // Mode DIV128 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV256                       0x00000008UL  // Mode DIV256 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV512                       0x00000009UL  // Mode DIV512 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV1024                      0x0000000AUL  // Mode DIV1024 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV2048                      0x0000000BUL  // Mode DIV2048 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV4096                      0x0000000CUL  // Mode DIV4096 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV8192                      0x0000000DUL  // Mode DIV8192 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV16384                     0x0000000EUL  // Mode DIV16384 for CMU_LFAPRESC0
#define CMU_LFAPRESC0_RTC_DIV32768                     0x0000000FUL  // Mode DIV32768 for CMU_LFAPRESC0

// Bit fields for CMU LFBPRESC0
#define CMU_LFBPRESC0_LEUART0_MASK                            0x3UL  // Bit mask for CMU_LEUART0
#define CMU_LFBPRESC0_LEUART0_DIV1                     0x00000000UL  // Mode DIV1 for CMU_LFBPRESC0
#define CMU_LFBPRESC0_LEUART0_DIV2                     0x00000001UL  // Mode DIV2 for CMU_LFBPRESC0
#define CMU_LFBPRESC0_LEUART0_DIV4                     0x00000002UL  // Mode DIV4 for CMU_LFBPRESC0
#define CMU_LFBPRESC0_LEUART0_DIV8                     0x00000003UL  // Mode DIV8 for CMU_LFBPRESC0

// Bit fields for CMU PCNTCTRL
#define CMU_PCNTCTRL_PCNT0CLKEN                        (0x1UL << 0)  // PCNT0 Clock Enable
#define CMU_PCNTCTRL_PCNT0CLKSEL                       (0x1UL << 1)  // PCNT0 Clock Select

// Bit fields for CMU ROUTE
#define CMU_ROUTE_CLKOUT0PEN                           (0x1UL << 0)  // CLKOUT0 Pin Enable
#define CMU_ROUTE_CLKOUT1PEN                           (0x1UL << 1)  // CLKOUT1 Pin Enable
#define CMU_ROUTE_LOCATION_LOC0                        0x00000000UL  // Mode LOC0 for CMU_ROUTE
#define CMU_ROUTE_LOCATION_LOC1                        0x00000001UL  // Mode LOC1 for CMU_ROUTE
#define CMU_ROUTE_LOCATION_LOC2                        0x00000002UL  // Mode LOC2 for CMU_ROUTE

// Bit fields for CMU LOCK
#define CMU_LOCK_RESETVALUE                            0x00000000UL  // Default value for CMU_LOCK
#define CMU_LOCK_MASK                                  0x0000FFFFUL  // Mask for CMU_LOCK
#define CMU_LOCK_LOCKKEY_DEFAULT                       0x00000000UL  // Mode DEFAULT for CMU_LOCK
#define CMU_LOCK_LOCKKEY_LOCK                          0x00000000UL  // Mode LOCK for CMU_LOCK
#define CMU_LOCK_LOCKKEY_UNLOCKED                      0x00000000UL  // Mode UNLOCKED for CMU_LOCK
#define CMU_LOCK_LOCKKEY_LOCKED                        0x00000001UL  // Mode LOCKED for CMU_LOCK
#define CMU_LOCK_LOCKKEY_UNLOCK                        0x0000580EUL  // Mode UNLOCK for CMU_LOCK


#ifdef __cplusplus
extern "C" {
#endif

  uint32_t cmu_hfper_freq_get(void);

  // CMU_HFPERCLKEN0 enable and disable functions
  __STATIC_INLINE void clk_enable_TIMER0(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;}
  __STATIC_INLINE void clk_disable_TIMER0(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER0;}

  __STATIC_INLINE void clk_enable_TIMER1(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1;}
  __STATIC_INLINE void clk_disable_TIMER1(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_TIMER1;}

  __STATIC_INLINE void clk_enable_ACMP0(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_ACMP0;}
  __STATIC_INLINE void clk_disable_ACMP0(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_ACMP0;}

  __STATIC_INLINE void clk_enable_USART1(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_USART1;}
  __STATIC_INLINE void clk_disable_USART1(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_USART1;}

  __STATIC_INLINE void clk_enable_PRS(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_PRS;}
  __STATIC_INLINE void clk_disable_PRS(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_PRS;}

  __STATIC_INLINE void clk_enable_IDAC0(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_IDAC0;}
  __STATIC_INLINE void clk_disable_IDAC0(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_IDAC0;}

  __STATIC_INLINE void clk_enable_GPIO(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;}
  __STATIC_INLINE void clk_disable_GPIO(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_GPIO;}

  __STATIC_INLINE void clk_enable_VCMP(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_VCMP;}
  __STATIC_INLINE void clk_disable_VCMP(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_VCMP;}

  __STATIC_INLINE void clk_enable_ADC0(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_ADC0;}
  __STATIC_INLINE void clk_disable_ADC0(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_ADC0;}

  __STATIC_INLINE void clk_enable_I2C0(void)  {CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_I2C0;}
  __STATIC_INLINE void clk_disable_I2C0(void) {CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_I2C0;}

  // CMU_HFCORECLKEN0 enable and disable functions
  __STATIC_INLINE void clk_enable_AES(void)  {CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_AES;}
  __STATIC_INLINE void clk_disable_AES(void) {CMU->HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_AES;}

  __STATIC_INLINE void clk_enable_DMA(void)  {CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_DMA;}
  __STATIC_INLINE void clk_disable_DMA(void) {CMU->HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_DMA;}

  __STATIC_INLINE void clk_enable_LE(void)  {CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_LE;}
  __STATIC_INLINE void clk_disable_LE(void) {CMU->HFCORECLKEN0 &= ~CMU_HFCORECLKEN0_LE;}


  // CMU_HFPERCLKDIV enable and disable functions
  __STATIC_INLINE void clk_enable_HFPER(void)  {CMU->HFPERCLKDIV |= CMU_HFPERCLKDIV_HFPERCLKEN;}
  __STATIC_INLINE void clk_disable_HFPER(void) {CMU->HFPERCLKDIV &= ~CMU_HFPERCLKDIV_HFPERCLKEN;}

  // CMU_LFACLKEN0 enable and disable functions
  __STATIC_INLINE void clk_enable_RTC(void)
  {
    CMU->LFACLKEN0 |= CMU_LFACLKEN0_RTC;
    while(CMU->SYNCBUSY & CMU_SYNCBUSY_LFACLKEN0);
  }

  __STATIC_INLINE void clk_disable_RTC(void)
  {
    CMU->LFACLKEN0 &= ~CMU_LFACLKEN0_RTC;
    while(CMU->SYNCBUSY & CMU_SYNCBUSY_LFACLKEN0);
  }

  // CMU_LFBCLKEN0 enable and disable functions
  __STATIC_INLINE void clk_enable_LEUART0(void)
  {
    CMU->LFBCLKEN0 |= CMU_LFBCLKEN0_LEUART0;
    while(CMU->SYNCBUSY & CMU_SYNCBUSY_LFBCLKEN0);
  }

  __STATIC_INLINE void clk_disable_LEUART0(void)
  {
    CMU->LFBCLKEN0 &= CMU_LFBCLKEN0_LEUART0;
    while(CMU->SYNCBUSY & ~CMU_SYNCBUSY_LFBCLKEN0);
  }

  // CMU_PCNTCTRL enable and disable functions
  __STATIC_INLINE void clk_enable_PCNT0(void)  {CMU->PCNTCTRL |= CMU_PCNTCTRL_PCNT0CLKEN;}
  __STATIC_INLINE void clk_disable_PCNT0(void) {CMU->PCNTCTRL &= ~CMU_PCNTCTRL_PCNT0CLKEN;}

  __STATIC_INLINE void clk_enable_PCNT0_LFACLK(void)  {CMU->PCNTCTRL |= CMU_PCNTCTRL_PCNT0CLKSEL;}
  __STATIC_INLINE void clk_disable_PCNT0_EXTPIN(void) {CMU->PCNTCTRL &= ~CMU_PCNTCTRL_PCNT0CLKSEL;}

  // CMU_LFCLKSEL LFA Select
  __STATIC_INLINE void clk_lfa_select_DISABLED(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFA_MASK | CMU_LFCLKSEL_LFAE);
  }

  __STATIC_INLINE void clk_lfa_select_LFRCO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFA_MASK | CMU_LFCLKSEL_LFAE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFA_LFRCO;
  }

  __STATIC_INLINE void clk_lfa_select_LFXO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFA_MASK | CMU_LFCLKSEL_LFAE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFA_LFXO;
  }

  __STATIC_INLINE void clk_lfa_select_HFCORECLKLEDIV2(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFA_MASK | CMU_LFCLKSEL_LFAE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2;
  }

  __STATIC_INLINE void clk_lfa_select_ULFRCO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFA_MASK | CMU_LFCLKSEL_LFAE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFAE;
  }

  // CMU_LFCLKSEL LFB Select
  __STATIC_INLINE void clk_lfb_select_DISABLED(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFB_MASK | CMU_LFCLKSEL_LFBE);
  }

  __STATIC_INLINE void clk_lfb_select_LFRCO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFB_MASK | CMU_LFCLKSEL_LFBE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFB_LFRCO;
  }

  __STATIC_INLINE void clk_lfb_select_LFXO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFB_MASK | CMU_LFCLKSEL_LFBE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFB_LFXO;
  }

  __STATIC_INLINE void clk_lfb_select_HFCORECLKLEDIV2(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFB_MASK | CMU_LFCLKSEL_LFBE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;
  }

  __STATIC_INLINE void clk_lfb_select_ULFRCO(void)
  {
    CMU->LFCLKSEL &= ~(CMU_LFCLKSEL_LFB_MASK | CMU_LFCLKSEL_LFBE);
    CMU->LFCLKSEL |= CMU_LFCLKSEL_LFBE;
  }

  __STATIC_INLINE void wait_state_select(void)
  {
    if(CMU->STATUS & CMU_STATUS_HFXOSEL) {
      if((CMU->HFRCOCTRL & CMU_HFRCOCTRL_BAND_MASK) <= CMU_HFRCOCTRL_BAND_14MHZ) {
	MSC->READCTRL &= ~MSC_READCTRL_MODE_WS1;
      }
    }
  }

  __STATIC_INLINE void clk_osc_select_LFXO(void)
  {
    CMU->OSCENCMD = CMU_OSCENCMD_LFXOEN;
    while (!(CMU->STATUS & CMU_STATUS_LFXORDY));
    MSC->READCTRL = MSC_READCTRL_MODE_WS1;
    CMU->CMD = CMU_CMD_HFCLKSEL_LFXO;
    //EMU_UpdateOscConfig();
    wait_state_select();
  }

  __STATIC_INLINE void clk_osc_select_LFRCO(void)
  {
    CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
    while (!(CMU->STATUS & CMU_STATUS_LFRCORDY));
    MSC->READCTRL = MSC_READCTRL_MODE_WS1;
    CMU->CMD = CMU_CMD_HFCLKSEL_LFRCO;
    //EMU_UpdateOscConfig();
    wait_state_select();
  }

  __STATIC_INLINE void clk_osc_select_HFXO(void)
  {
    CMU->OSCENCMD = CMU_OSCENCMD_HFXOEN;
    while (!(CMU->STATUS & CMU_STATUS_HFXORDY));
    MSC->READCTRL = MSC_READCTRL_MODE_WS1;
    CMU->CMD = CMU_CMD_HFCLKSEL_HFXO;
    //EMU_UpdateOscConfig();
    wait_state_select();
  }

  __STATIC_INLINE void clk_osc_select_HFRCO(void)
  {
    CMU->OSCENCMD = CMU_OSCENCMD_HFRCOEN;
    while (!(CMU->STATUS & CMU_STATUS_HFRCORDY));
    MSC->READCTRL = MSC_READCTRL_MODE_WS1;
    CMU->CMD = CMU_CMD_HFCLKSEL_HFRCO;
    //EMU_UpdateOscConfig();
    wait_state_select();
  }

  __STATIC_INLINE void clk_osc_enable_LFRCO(void)
  {
    CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;
    while (!(CMU->STATUS & CMU_STATUS_LFRCORDY));
  }


  __STATIC_INLINE uint32_t get_hfrco_freq(void)
  {
    const uint32_t hf_bands[5] = {1,7,11,14,21};

    return (hf_bands[(CMU->HFRCOCTRL & CMU_HFRCOCTRL_BAND_MASK) >> CMU_HFRCOCTRL_BAND_SHIFT] * 1000000);
  }


#ifdef __cplusplus
}
#endif

#endif

