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

  clk_enable_HFPER();
  clk_enable_GPIO();
  clk_enable_LE();
  clk_enable_DMA();

  //  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;  // Enable LFRCO for RTC
  clk_osc_enable_LFRCO();
  clk_lfa_select_LFRCO();
  clk_lfb_select_HFCORECLKLEDIV2();
  clk_enable_RTC();

  // Change to 21MHz internal oscillator band
  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_21MHZ | (DEVINFO->HFRCOCAL1 & 0xFF);

  SysTick_Config(21000000 / 1000);
}

