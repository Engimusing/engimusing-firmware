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


#include <stdbool.h>
#include <stdint.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_usart.h"


void init_efm32zg(void)
{
  uint32_t ul ;
  uint32_t tuning;

  // Enable clocks for peripherals.
  CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO;

  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE | CMU_HFCORECLKEN0_DMA;  // Enable LE and DMA interface
  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;  // Enable LFRCO for RTC
  CMU->LFCLKSEL = CMU_LFCLKSEL_LFA_LFRCO | CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;  // Setup LFA to use LFRCRO
  CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;  // Enable RTC

  // Change to 21MHz internal osciallator to increase speed of bootloader
  tuning = ((DEVINFO->HFRCOCAL1 & _DEVINFO_HFRCOCAL1_BAND21_MASK) >> _DEVINFO_HFRCOCAL1_BAND21_SHIFT);
  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_21MHZ | tuning;

  SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000);

}

