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

#ifndef _ANALOGLP_
#define _ANALOGLP_

#include "Arduino.h"
#include "em_cmu.h"
#include "em_emu.h"

#define INTERNAL1V25 ADC_SINGLECTRL_REF_1V25
#define INTERNAL2V5  ADC_SINGLECTRL_REF_2V5
#define DEFAULT      ADC_SINGLECTRL_REF_VDD
#define EXTERNAL     ADC_SINGLECTRL_REF_EXTSINGLE

class AnalogLP
{
public:
AnalogLP();
uint32_t analogRead(uint8_t pin);
uint32_t analogReference(uint32_t ref);
void analogReadResolution(uint8_t bits);
private:
uint32_t adc_reference;
uint32_t adc_resolution;
uint32_t adc_oversampling;
};


#ifdef __cplusplus
extern "C"{
void print_adc_regs(void);

} // extern "C"

#endif

#endif /* _ANALOGLP_ */
