#pragma once

#include "cmsis.h"

#define EMU_UNLOCK_CODE      0xADE8 /**< EMU unlock code */

__STATIC_INLINE void EMU_EnterEM1(void)
{
  /* Just enter Cortex-M3 sleep mode */
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}

