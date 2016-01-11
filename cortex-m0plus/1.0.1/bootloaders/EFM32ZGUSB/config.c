/**************************************************************************
 * @file usart.c
 * @brief USART code for the EFM32 bootloader
 * @author Silicon Labs
 * @version 1.68
 ***************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************
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
 ***************************************************************************/

//*****************************************************************************
// Copyright (c) 2015-2016 Engimusing LLC.  All right reserved.
//
// Modifications by Engimusing are released as a library
// that is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// 
//*****************************************************************************

#include "config.h"
#include "serial.h"
#include "flash.h"
#include "efm_gpio.h"

const uint32_t bootloader_size = BOOTLOADER_SIZE;

volatile unsigned long *TTY1;
int tty1_status_reg;
unsigned long tty1_status_rxdatav;
int tty1_rxdataxp_reg;
int tty1_txdata_reg;
int tty1_status_txbl;

void io_init()
{
  uint32_t tuning;

  unsigned long leuart_clkdiv = EFMTG_LEUART_CLKDIV;

  // Enable clocks for peripherals.
  CMU->HFPERCLKDIV = CMU_HFPERCLKDIV_HFPERCLKEN;
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO;

  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE | CMU_HFCORECLKEN0_DMA;  // Enable LE and DMA interface
  CMU->OSCENCMD = CMU_OSCENCMD_LFRCOEN;  // Enable LFRCO for RTC
  CMU->LFCLKSEL = CMU_LFCLKSEL_LFA_LFRCO | CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2;  // Setup LFA to use LFRCRO
  CMU->LFACLKEN0 = CMU_LFACLKEN0_RTC;  // Enable RTC

  leuart_clkdiv = EFMZG_LEUART_CLKDIV;
  // Change to 21MHz internal osciallator to increase speed of bootloader
  tuning = ((DEVINFO->HFRCOCAL1 & DEVINFO_HFRCOCAL1_BAND21_MASK) >> DEVINFO_HFRCOCAL1_BAND21_SHIFT);
  CMU->HFRCOCTRL = CMU_HFRCOCTRL_BAND_21MHZ | tuning;

  FLASH_CalcPageSize();  // Figure out correct flash page size

  GPIO_pinMode(PORTA,  8, OUTPUT);
  GPIO_pinMode(PORTA,  9, OUTPUT);
  GPIO_pinMode(PORTA, 10, OUTPUT);

  GPIO_pinMode(PORTD, 4, OUTPUT);
  GPIO_pinMode(PORTB, 8, OUTPUT);
  GPIO_pinMode(PORTC, 4, OUTPUT);
  GPIO_pinMode(PORTD, 6, OUTPUT);
  GPIO_pinMode(PORTB, 7, OUTPUT);
  GPIO_pinMode(PORTC, 1, OUTPUT);
  GPIO_pinMode(PORTC, 0, OUTPUT);
  GPIO_pinMode(PORTD, 7, OUTPUT);

  led0_off();
  led1_off();
  led2_off();
  led3_off();
  led4_off();
  led5_off();
  led6_off();
  led7_off();

  // TTY1 - LEUART0
  GPIO->P[1].DOUT  = (1 << 13);  // To avoid false start, configure output LEU0_TX as high on PB13
  GPIO->P[1].MODEH = GPIO_P_MODEH_MODE13_WIREDANDPULLUP | GPIO_P_MODEH_MODE14_WIREDANDPULLUP;
  GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~GPIO_P_MODEH_MODE13_MASK) | GPIO_P_MODEH_MODE13_PUSHPULL;
  GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~GPIO_P_MODEH_MODE14_MASK) | GPIO_P_MODEH_MODE14_INPUT;
  CMU->LFBCLKEN0 |=  CMU_LFBCLKEN_LEUART0;
  TTY1 = ((unsigned long *) LEUART0_BASE_ADDR);      // LEUART0
  TTY1[LEUART_IFC_REG] = LEUART_IFC_MASK;  // clear ints
  TTY1[LEUART_IEN_REG] |= IEN_RXDATAV;    // enable ints
  NVIC_EnableIRQ(LEUART0_IRQn);
  NVIC_ClearPendingIRQ(LEUART0_IRQn);
  TTY1[LEUART_CLKDIV_REG]   = leuart_clkdiv;
  TTY1[ROUTE_REG]           = LEUART_ROUTE_LOCATION_LOC1 | ROUTE_RXPEN_TXPEN;
  TTY1[LEUART_CMD_REG]      = TTY_CMD_RXEN_TXEN;

  init_printf1(NULL,putc1);

}

void led0_on(void)  {GPIO_PinOutClear(PORTD,4);}
void led1_on(void)  {GPIO_PinOutClear(PORTB,8);}
void led2_on(void)  {GPIO_PinOutClear(PORTC,4);}
void led3_on(void)  {GPIO_PinOutClear(PORTD,6);}
void led4_on(void)  {GPIO_PinOutClear(PORTB,7);}
void led5_on(void)  {GPIO_PinOutClear(PORTC,1);}
void led6_on(void)  {GPIO_PinOutClear(PORTC,0);}
void led7_on(void)  {GPIO_PinOutClear(PORTD,7);}

void led0_off(void) {GPIO_PinOutSet(PORTD,4);}
void led1_off(void) {GPIO_PinOutSet(PORTB,8);}
void led2_off(void) {GPIO_PinOutSet(PORTC,4);}
void led3_off(void) {GPIO_PinOutSet(PORTD,6);}
void led4_off(void) {GPIO_PinOutSet(PORTB,7);}
void led5_off(void) {GPIO_PinOutSet(PORTC,1);}
void led6_off(void) {GPIO_PinOutSet(PORTC,0);}
void led7_off(void) {GPIO_PinOutSet(PORTD,7);}

void leds_off(void)
{
  led0_off();
  led1_off();
  led2_off();
  led3_off();
  led4_off();
  led5_off();
  led6_off();
  led7_off();
}

const uint8_t patterns[16] = {0x01,0x02,0x04,0x08, 0x10,0x20,0x40,0x80,  0xAA,0x55,0x33,0xCC,0xF0,0x0F,0xFF,0x00};

void led_on_off(uint8_t on, uint8_t port, uint8_t pin)
{
  if(on) GPIO_PinOutClear(port,pin);  else GPIO_PinOutSet(port,pin);
}

#define PUSHPULL  0x00000004UL


void GPIO_pinMode(GPIO_Port_TypeDef port, unsigned int pin, GPIO_Mode_TypeDef mode)
{
  uint32_t mask, val;

  if(pin < 8) {
    mask = GPIO_MODE_MASK << (pin << 2);
    val = GPIO->P[port].MODEL & ~mask;
    GPIO->P[port].MODEL = val | mode << (pin << 2);
  } else {
    mask = GPIO_MODE_MASK << ((pin & 0x7) << 2);
    val = GPIO->P[port].MODEH & ~mask;
    GPIO->P[port].MODEH = val | mode << ((pin & 0x7) << 2);
  }
}

void ledOn(void) {}
void ledOff(void) {}

void ledGreenOff(void) {GPIO_PinOutSet(PORTA,  8);}
void ledBlueOff(void)  {GPIO_PinOutSet(PORTA,  9);}
void ledRedOff(void)   {GPIO_PinOutSet(PORTA, 10);}

void ledGreenOn(void)  {GPIO_PinOutClear(PORTA,  8);}
void ledBlueOn(void)   {GPIO_PinOutClear(PORTA,  9);}
void ledRedOn(void)    {GPIO_PinOutClear(PORTA, 10);}

void ledAllOff(void)
{
  ledGreenOff();
  ledBlueOff();
  ledRedOff();
}

void ledAllOn(void)
{
  ledGreenOn();
  ledBlueOn();
  ledRedOn();
}

void reset_from_break(void)
{
  for(volatile int i = 0; i < 150000; i++);
  SCB->AIRCR = 0x05FA0004;  // Write to the Application Interrupt/Reset Command Register to reset
}


void LEUART0_IRQHandler(void)
{
  if(TTY1[LEUART_RXDATAXP_REG] & RXDATAXP_FERRP)
    reset_from_break();
  // Check for RX data valid interrupt
  if (TTY1[LEUART_STATUS_REG] & LEUART_STATUS_RXDATAV) {
    tty1_rx_data(TTY1[RXDATA_REG]);
  }
  if (TTY1[LEUART_STATUS_REG] & LEUART_STATUS_TXBL) { // Check TX buffer level status
    if(tty1_get_number_pendingBytes() > 0) {
      TTY1[LEUART_TXDATA_REG] = tty1_get_pending_byte();
    }
    if(tty1_get_number_pendingBytes() < 1) {
      TTY1[LEUART_IEN_REG] &= ~IEN_TXBL;
    }
  }
}

void tty0_enable_tx_int(void)
{
}

void tty1_enable_tx_int(void)
{
  TTY1[LEUART_IEN_REG] |= IEN_TXBL;  // Enable interrupt on SERIAL TX Buffer
}


void tty0_enable_rx_ints(void)  {NVIC_EnableIRQ(USART1_RX_IRQn);}
void tty0_disable_rx_ints(void) {NVIC_DisableIRQ(USART1_RX_IRQn);}
void tty1_enable_rx_ints(void)  {NVIC_EnableIRQ(LEUART0_IRQn);}
void tty1_disable_rx_ints(void) {NVIC_DisableIRQ(LEUART0_IRQn);}

void tty0_enable_tx_ints(void)  {NVIC_EnableIRQ(USART1_TX_IRQn);}
void tty0_disable_tx_ints(void) {NVIC_DisableIRQ(USART1_TX_IRQn);}
void tty1_enable_tx_ints(void)  {NVIC_EnableIRQ(LEUART0_IRQn);}
void tty1_disable_tx_ints(void) {NVIC_DisableIRQ(LEUART0_IRQn);}



