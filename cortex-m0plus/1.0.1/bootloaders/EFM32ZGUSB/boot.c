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

#include <stdbool.h>
#include "xmodem.h"
#include "em_device.h"
#include "boot.h"
#include "config.h"
#include "serial.h"

extern const uint32_t bootloader_size;

#define CPU_USER_PROGRAM_STARTADDR_PTR    ((uint32_t)(bootloader_size + 0x00000004))
#define CPU_USER_PROGRAM_VECTABLE_OFFSET  ((uint32_t)bootloader_size)
#define SCB_VTOR    (*((volatile uint32_t *) 0xE000ED08))


// Boots the application
void BOOT_boot()
{
  void (*pProgResetHandler)(void);

  WDOG->CTRL = 0;

  NVIC->ICER[0] = 0xFFFFFFFF;
  //  NVIC->ICER[1] = 0xFFFFFFFF;
  RTC->CTRL  = _RTC_CTRL_RESETVALUE;
  RTC->COMP0 = _RTC_COMP0_RESETVALUE;
  RTC->IEN   = _RTC_IEN_RESETVALUE;

  // Reset GPIO settings
  CMU->LFACLKEN0 = _CMU_LFACLKEN0_RESETVALUE;
  CMU->LFCLKSEL  = _CMU_LFCLKSEL_RESETVALUE;
  // Disable LFRCO
  CMU->OSCENCMD = CMU_OSCENCMD_LFRCODIS;
  // Disable LE interface
  CMU->HFCORECLKEN0 = _CMU_HFCORECLKEN0_RESETVALUE;
  // Reset clocks
  CMU->HFPERCLKDIV = _CMU_HFPERCLKDIV_RESETVALUE;
  CMU->HFPERCLKEN0 = _CMU_HFPERCLKEN0_RESETVALUE;

  SCB_VTOR = CPU_USER_PROGRAM_VECTABLE_OFFSET & (uint32_t)0x1FFFFF80;
  pProgResetHandler = (void(*)(void))(*((uint32_t*)CPU_USER_PROGRAM_STARTADDR_PTR));
  pProgResetHandler();
}

void checkForValidApp(uint8_t uartID, uint32_t flashSize)
{
  uint32_t pc, sp;

  sp = *((uint32_t *) bootloader_size);
  pc = *((uint32_t *) bootloader_size + 1);
  if (pc > flashSize) {
    if(uartID == 0) printf0("\r\nApplication pc > flash size\r\n"); else printf1("\r\nApplication pc > flash size\r\n");
  }
  if(uartID == 0) printf0("\r\n%x %x\r\n",sp,pc); else printf1("\r\n%x %x\r\n",sp,pc);
}

