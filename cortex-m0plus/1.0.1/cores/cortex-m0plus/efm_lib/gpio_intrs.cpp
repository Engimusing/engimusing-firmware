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

#include "gpio_intrs.h"

extern LEUARTClass Serial;

INTRClass INTR;


// GPIO Interrupts
volatile voidFuncPtr intFunc[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
// storage for 16 interrupt functions
// corresponding to #bits in IEN

// GPIO Interrupts
void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode)
{
  INTR.attachIntr(pin, gpioIntFunc, mode);
}

INTRClass::INTRClass()
{
  for(int i = 0; i < NUMBER_GPIO_INTRS; i++) {
    nints[i] = 0;
  }
}

void INTRClass::attachIntr(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode)
{
  if(valid_pin(pin)) {

    intFunc[iPins[pin]] = gpioIntFunc;

    int shift = ((iPins[pin] & 0x7) * 4);
    uint32_t mask = 0xF << shift;

    if(iPins[pin] < 8) {
      GPIO->EXTIPSELL = (GPIO->EXTIPSELL & ~mask) | (iPorts[pin] << shift); 
    } else {
      GPIO->EXTIPSELH = (GPIO->EXTIPSELH & ~mask) | (iPorts[pin] << shift); 
    }
    if((mode == RISING) || (mode == CHANGE)) {
      GPIO->EXTIRISE |= 0x1 << iPins[pin];
    }
    if((mode == FALLING) || (mode == CHANGE)) {
      GPIO->EXTIFALL |= 0x1 << iPins[pin];
    }
    GPIO->IFC = 0x1 << iPins[pin];
    GPIO->IEN |= 0x1 << iPins[pin];

    NVIC_EnableIRQ(GPIO_EVEN_IRQn);
    NVIC_EnableIRQ(GPIO_ODD_IRQn);
  }
}

void detachInterrupt(uint8_t pin)
{
  INTR.detachIntr(pin);
}

void INTRClass::detachIntr(uint8_t pin)
{
  if(valid_pin(pin)) {
    int shift = ((iPins[pin] & 0x7) * 4);
    uint32_t mask = 0xF << shift;

    intFunc[iPins[pin]] = 0;
    GPIO->EXTIRISE &= 0x1 << iPins[pin];
    GPIO->EXTIFALL &= 0x1 << iPins[pin];
    GPIO->IFC = 0x1 << iPins[pin];
    GPIO->IEN &= 0x1 << iPins[pin];

    if(iPins[pin] < 8) {
      GPIO->EXTIPSELL = GPIO->EXTIPSELL & ~mask;
    } else {
      GPIO->EXTIPSELH = GPIO->EXTIPSELH & ~mask;
    }
  }
}

void INTRClass::GPIO_ODD_IRQHandler(void)
{
  for(int i = 1; i < 16; i+=2) {
    if (GPIO->IF & (0x2 << (i-1))) {
      GPIO->IFC = (0x2 << (i-1));
      if(intFunc[i]) {
	intFunc[i]();
      }
      nints[i]++;
    }
  }
}

void INTRClass::GPIO_EVEN_IRQHandler(void)
{
  for(int i = 0; i < 16; i+=2) {
    if (GPIO->IF & (0x1 << i)) {
      GPIO->IFC = (0x1 << i);
      if(intFunc[i]) {
	intFunc[i]();
      }
      nints[i]++;
    }
  }  
}

uint8_t INTRClass::read_nints(uint8_t pin)
{
  return nints[iPins[pin]];
}

uint8_t INTRClass::read_clr_nints(uint8_t pin)
{
  uint8_t n = nints[iPins[pin]];
  noInterrupts();
  nints[iPins[pin]] = 0;
  interrupts();
  return n;
}
uint8_t INTRClass::read_decrement_nints(uint8_t pin)
{
  noInterrupts();
  uint8_t n = nints[pin];
  if(nints[iPins[pin]] > 0) {
    nints[iPins[pin]]--;
  }
  interrupts();
  return n;
}

void GPIO_ODD_IRQHandler(void)
{
  INTR.GPIO_ODD_IRQHandler();
}

void GPIO_EVEN_IRQHandler(void)
{
  INTR.GPIO_EVEN_IRQHandler();
}

