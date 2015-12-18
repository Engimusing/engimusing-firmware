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


#include <Arduino.h>
#include "em_cmu.h"
#include "analog.h"

extern LEUARTClass Serial;
AnalogLP Analog;


AnalogLP::AnalogLP()
{
  adc_reference = DEFAULT;
  adc_resolution = ADC_SINGLECTRL_RES_12BIT;
  adc_oversampling = ADC_CTRL_OVSRSEL_X2;
}

uint32_t AnalogLP::analogRead(uint8_t pin)
{
  if(valid_pin(pin)) {
    // Enable clock for ADC0
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_ADC0;      // Enable clock for ADC0

    uint32_t hfperFreq = cmu_hfper_freq_get();
    hfperFreq += 999999;
    hfperFreq /= 1000000;
    hfperFreq -= 1;

    ADC0->CTRL = ADC_CTRL_WARMUPMODE_NORMAL
      | ADC_CTRL_LPFMODE_BYPASS
      | (3 << _ADC_CTRL_PRESC_SHIFT)  // set ADC frequency = HFPerClk divided by 3
      | (hfperFreq <<  _ADC_CTRL_TIMEBASE_SHIFT)
      | adc_oversampling; // oversampling rate if enabled

    ADC0->SINGLECTRL = adc_resolution
      | (adcPins[pin] << _ADC_SINGLECTRL_INPUTSEL_SHIFT)
      | adc_reference
      | ADC_SINGLECTRL_AT_32CYCLES;

    ADC0->CMD = ADC_CMD_SINGLESTART;
    while (ADC0->STATUS & ADC_STATUS_SINGLEACT) ;  // Wait while conversion is active

    uint32_t data = ADC0->SINGLEDATA;
    CMU->HFPERCLKEN0 &= ~CMU_HFPERCLKEN0_ADC0;
    return data;
  } else {
    return 0;
  }
}


uint32_t AnalogLP::analogReference(uint32_t ref)
{
  adc_reference = ref;
}

void AnalogLP::analogReadResolution(uint8_t bits)
{
  if(bits == 6) {
    adc_resolution = ADC_SINGLECTRL_RES_6BIT;
  } else if(bits == 8) {
    adc_resolution = ADC_SINGLECTRL_RES_8BIT;
  } else if(bits >= 16) {
    adc_resolution = ADC_SINGLECTRL_RES_OVS;
    if(adc_oversampling == ADC_CTRL_OVSRSEL_X2) {
      adc_oversampling = ADC_CTRL_OVSRSEL_X64;
    }
  } else {
    adc_resolution = ADC_SINGLECTRL_RES_12BIT;
  }
}


void print_adc_regs(void)
{
  uint32_t regs[15];

  regs[0] = ADC0->CTRL;
  regs[1] = ADC0->CMD;
  regs[2] = ADC0->STATUS;
  regs[3] = ADC0->SINGLECTRL;
  regs[4] = ADC0->SCANCTRL;
  regs[5] = ADC0->IEN;
  regs[6] = ADC0->IF;
  regs[7] = ADC0->IFS;
  regs[8] = ADC0->IFC;
  regs[9] = ADC0->SINGLEDATA;
  regs[10] = ADC0->SCANDATA;
  regs[11] = ADC0->SINGLEDATAP;
  regs[12] = ADC0->SCANDATAP;
  regs[13] = ADC0->CAL;
  regs[14] = ADC0->BIASPROG;

  Serial.print(" CTRL        = "); Serial.println(regs[0],HEX);
  Serial.print(" CMD         = "); Serial.println(regs[1],HEX);
  Serial.print(" STATUS      = "); Serial.println(regs[2],HEX);
  Serial.print(" SINGLECTRL  = "); Serial.println(regs[3],HEX);
  Serial.print(" SCANCTRL    = "); Serial.println(regs[4],HEX);
  Serial.print(" IEN         = "); Serial.println(regs[5],HEX);
  Serial.print(" IF          = "); Serial.println(regs[6],HEX);
  Serial.print(" IFS         = "); Serial.println(regs[7],HEX);
  Serial.print(" IFC         = "); Serial.println(regs[8],HEX);
  Serial.print(" SINGLEDATA  = "); Serial.println(regs[9],HEX);
  Serial.print(" SCANDATA    = "); Serial.println(regs[10],HEX);
  Serial.print(" SINGLEDATAP = "); Serial.println(regs[11],HEX);
  Serial.print(" SCANDATAP   = "); Serial.println(regs[12],HEX);
  Serial.print(" CAL         = "); Serial.println(regs[13],HEX);
  Serial.print(" BIASPROG    = "); Serial.println(regs[14],HEX);
  Serial.println("");
}
