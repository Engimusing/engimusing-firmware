/*
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

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

#pragma once

#include "cmsis.h"

#define EMU_UNLOCK_CODE      0xADE8 /**< EMU unlock code */

__STATIC_INLINE void EMU_EnterEM1(void)
{
  /* Just enter Cortex-M3 sleep mode */
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}

