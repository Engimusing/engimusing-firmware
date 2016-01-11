/**************************************************************************
 * @file boot.c
 * @brief Boot Loader
 * @author Silicon Labs
 * @version 1.68
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

//*****************************************************************************
// Copyright (c) 2015-2016 Engimusing LLC.  All right reserved.
//
// Modifications by Engimusing are released as a library
// that is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 
//*****************************************************************************

#include "config.h"
#include "xmodem.h"
#include "boot.h"
#include "serial.h"

extern const uint32_t bootloader_size;

#define CPU_USER_PROGRAM_STARTADDR_PTR    ((uint32_t)(bootloader_size + 0x00000004))
#define CPU_USER_PROGRAM_VECTABLE_OFFSET  ((uint32_t)bootloader_size)
#define SCB_VTOR    (*((volatile uint32_t *) 0xE000ED08))

static uint32_t x[128];

// Boots the application
void BOOT_boot()
{
  void (*pProgResetHandler)(void);

  for(int i = 0; i < 128; i++) {
    x[i] += x[i>>1];
  }

  NVIC->ICER[0] = 0xFFFFFFFF;
  //  NVIC->ICER[1] = 0xFFFFFFFF;
  RTC->CTRL  = RTC_CTRL_RESETVALUE;
  RTC->COMP0 = RTC_COMP0_RESETVALUE;
  RTC->IEN   = RTC_IEN_RESETVALUE;

  // Reset GPIO settings
  CMU->LFACLKEN0    = CMU_LFACLKEN0_RESETVALUE;
  CMU->LFCLKSEL     = CMU_LFCLKSEL_RESETVALUE;
  // Disable LFRCO
  CMU->OSCENCMD     = CMU_OSCENCMD_LFRCODIS;
  // Disable LE interface
  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_RESETVALUE;
  // Reset clocks
  CMU->HFPERCLKDIV  = CMU_HFPERCLKDIV_RESETVALUE;
  CMU->HFPERCLKEN0  = CMU_HFPERCLKEN0_RESETVALUE;

  SCB_VTOR = CPU_USER_PROGRAM_VECTABLE_OFFSET & (uint32_t)0x1FFFFF80;
  pProgResetHandler = (void(*)(void))(*((uint32_t*)CPU_USER_PROGRAM_STARTADDR_PTR));
  pProgResetHandler();
}

void checkForValidApp(uint32_t flashSize)
{
  uint32_t pc, sp;

  sp = *((uint32_t *) bootloader_size);
  pc = *((uint32_t *) bootloader_size + 1);
  if (pc > flashSize) {
    printf1("\r\nApplication pc > flash size\r\n");
  }
  printf1("\r\n%x %x\r\n",sp,pc);
}

