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
#include "efm_cmu_config.h"
#include "efm_devinfo.h"
#include "cmsis.h"

void init_efm32zg(void)
{
  // Enable clocks for peripherals.
  CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO;

  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE | CMU_HFCORECLKEN0_DMA;  // Enable LE and DMA interface
  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;  // Enable LFRCO for RTC
  CMU->LFCLKSEL = CMU_LFCLKSEL_LFA_LFRCO | CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;  // Setup LFA to use LFRCRO
  CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;  // Enable RTC

  // Change to 21MHz internal oscillator to increase speed of bootloader
  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_21MHZ | (DEVINFO->HFRCOCAL1 & 0xFF);

  SysTick_Config(cmu_hfper_freq_get() / 1000);
}

