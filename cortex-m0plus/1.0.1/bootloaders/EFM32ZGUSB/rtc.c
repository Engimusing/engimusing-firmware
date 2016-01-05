/**************************************************************************
 * @file rtc.c
 * @brief EFM32 Bootloader.
 * @author Engimusing LLC
 * @version 1.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Engimusing LLC, http://www.engimusing.com</b>
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
#include "em_device.h"
//#include "usart.h"
#include "rtc.h"

volatile bool rtcInt = false;
//const uint8_t dot1[]     = ".";

void initRTC(void)
{
  // Initialize RTC
  RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;            // Clear interrupt flags
  RTC->COMP0 = 4096;
  RTC->IEN = RTC_IEN_COMP0;                                         // Enable Interrupts on COMP0
  NVIC_EnableIRQ(RTC_IRQn);                                         // Enable RTC interrupts
  RTC->CTRL = RTC_CTRL_COMP0TOP | RTC_CTRL_DEBUGRUN | RTC_CTRL_EN;  // Enable RTC
}

void RTC_IRQHandler(void)
{
  RTC->IFC = RTC_IFC_COMP1 | RTC_IFC_COMP0 | RTC_IFC_OF;  // Clear interrupt flag

  rtcInt = true;
}

bool getRTCint(void)
{
  return rtcInt;
}

void clearRTCint(void)
{
  rtcInt = 0;
}

