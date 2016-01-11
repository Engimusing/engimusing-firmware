/**************************************************************************//**
 * @file config.h
 * @brief Bootloader Configuration.
 *    This file defines how the bootloader is set up.
 * @author Silicon Labs
 * @version 1.68
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "io_types.h"
#include "cmsis.h"
#include "efm_cmu_config.h"
#include "efm_devinfo.h"
#include "efm_emu.h"
#include "efm_wdog.h"
#include "leds.h"

#include "boot.h"
#include "crc.h"
#include "flash.h"
#include "printf.h"
#include "rtc.h"
#include "serial.h"
#include "xmodem.h"
#include "efm_gpio.h"
#include "efm_leuart.h"


void io_init(void);
void setup_gpios(unsigned int, unsigned int, unsigned int);
void put_rx_data(uint8_t);
void initLEDs(void);
void ledOn(void);
void ledOff(void);
uint8_t bootloaderLEDflash(void);

void    tty0_rx_data(uint8_t);
void    tty1_rx_data(uint8_t);

uint8_t tty0_get_pending_byte(void);
uint8_t tty1_get_pending_byte(void);

uint32_t tty0_get_number_pendingBytes(void);
uint32_t tty1_get_number_pendingBytes(void);

void tty0_enable_tx_int(void);
void tty1_enable_tx_int(void);

void putc0(void* p, char ch);
void putc1(void* p, char ch);

void tfp_printf0(char *fmt, ...);
void tfp_printf1(char *fmt, ...);

#define USART0_BASE_ADDR       (0x4000C000UL)
#define USART1_BASE_ADDR       (0x4000C400UL)
#define USART2_BASE_ADDR       (0x4000C800UL)

#define LEUART0_BASE_ADDR      (0x40084000UL)
#define LEUART1_BASE_ADDR      (0x40084400UL)

#define TTY_CMD_RXEN_TXEN      (0x00000005UL)

#define RXDATA_REG		6
#define ROUTE_REG		21

#define USART_STATUS_REG	4
#define LEUART_STATUS_REG	2

#define USART_RXDATAXP_REG	10
#define LEUART_RXDATAXP_REG	8

#define USART_TXDATA_REG	13
#define LEUART_TXDATA_REG	10

#define USART_CLKDIV_REG	5
#define LEUART_CLKDIV_REG	3

#define USART_IEN_REG		19
#define LEUART_IEN_REG		14

#define USART_IFC_REG		18
#define LEUART_IFC_REG		13

#define USART_CMD_REG		3
#define LEUART_CMD_REG		1

#define EFMZG_LEUART_CLKDIV 0x59D0
#define EFMTG_LEUART_CLKDIV 0x77C0
#define EFMWG_LEUART_CLKDIV 0x77C0

#define EFMZG_USART_CLKDIV  0x0A65
#define EFMTG_USART_CLKDIV  0x0E32
#define EFMWG_USART_CLKDIV  0x77C0

#define ROUTE_RXPEN_TXPEN   0x0003

#define USART_STATUS_TXBL	(0x1UL << 6)

#define RXDATAXP_FERRP    (0x1UL << 15)
#define USART_CMD_CLEAR   USART_CMD_CLEARRX | USART_CMD_CLEARTX

#define CMU_LFBCLKEN_LEUART0      (0x1UL << 0)
#define CMU_LFBCLKEN_LEUART1      (0x1UL << 1)

#define TG_ZG_CMU_HFPERCLKEN0_USART0	(0x1UL << 2)
#define TG_ZG_CMU_HFPERCLKEN0_USART1	(0x1UL << 3)

#define WG_CMU_HFPERCLKEN0_USART0	(0x1UL << 0)
#define WG_CMU_HFPERCLKEN0_USART1	(0x1UL << 1)
#define WG_CMU_HFPERCLKEN0_USART2	(0x1UL << 2)

#define CMU_LFBCLKEN_LEUART0		(0x1UL << 0)
#define CMU_LFBCLKEN_LEUART1		(0x1UL << 1)

#define LEUART_IFC_MASK        (0x000007F9UL)
#define USART_IFC_MASK         (0x00001FF9UL)

#define IEN_RXDATAV            (0x1UL << 2)
#define IEN_TXBL               (0x1UL << 1)

/** Frequency of the LF clock */
#define LFRCO_FREQ           (32768)

/** The size of the bootloader flash image */
#define BOOTLOADER_SIZE      0x2000

#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

#define GPIO_MODE_MASK                          0x0000000FUL  // BIT MASK
#define GPIO_MODE_DISABLED                      0x00000000UL  // DISABLED
#define GPIO_MODE_INPUT                         0x00000001UL  // INPUT
#define GPIO_MODE_INPUTPULL                     0x00000002UL  // INPUTPULL
#define GPIO_MODE_INPUTPULLFILTER               0x00000003UL  // INPUTPULLFILTER
#define GPIO_MODE_PUSHPULL                      0x00000004UL  // PUSHPULL
#define GPIO_MODE_PUSHPULLDRIVE                 0x00000005UL  // PUSHPULLDRIVE
#define GPIO_MODE_WIREDOR                       0x00000006UL  // WIREDOR
#define GPIO_MODE_WIREDORPULLDOWN               0x00000007UL  // WIREDORPULLDOWN
#define GPIO_MODE_WIREDAND                      0x00000008UL  // WIREDAND
#define GPIO_MODE_WIREDANDFILTER                0x00000009UL  // WIREDANDFILTER
#define GPIO_MODE_WIREDANDPULLUP                0x0000000AUL  // WIREDANDPULLUP
#define GPIO_MODE_WIREDANDPULLUPFILTER          0x0000000BUL  // WIREDANDPULLUPFILTER
#define GPIO_MODE_WIREDANDDRIVE                 0x0000000CUL  // WIREDANDDRIVE
#define GPIO_MODE_WIREDANDDRIVEFILTER           0x0000000DUL  // WIREDANDDRIVEFILTER
#define GPIO_MODE_WIREDANDDRIVEPULLUP           0x0000000EUL  // WIREDANDDRIVEPULLUP
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER     0x0000000FUL  // WIREDANDDRIVEPULLUPFILTER

#define DRIVEMODE_STANDARD                      0x00000000UL
#define DRIVEMODE_LOWEST                        0x00000001UL
#define DRIVEMODE_HIGH                          0x00000002UL
#define DRIVEMODE_LOW                           0x00000003UL

#define GPIO_DISABLED                    (0x00)
#define DISABLED_PULLUP                  (0x01)
#define INPUT                            (0x02)
#define INPUT_PULLUP                     (0x03)
#define INPUT_PULLDOWN                   (0x04)
#define INPUT_FILTER                     (0x05)
#define INPUT_PU_FILTER                  (0x06)
#define INPUT_PD_FILTER                  (0x07)
#define WIRED_OR                         (0x08)
#define WIRED_OR_PULLDOWN                (0x09)
#define OUTPUT                           (0x0A)
#define OUTPUT_LOWEST_DRIVE              (0x0B)
#define OUTPUT_LOW_DRIVE                 (0x0C)
#define OUTPUT_HIGH_DRIVE                (0x0D)
#define WIRED_AND                        (0x0E)
#define WIRED_AND_LOWEST_DRIVE           (0x0F)
#define WIRED_AND_LOW_DRIVE              (0x10)
#define WIRED_AND_HIGH_DRIVE             (0x11)
#define WIRED_AND_FILTER                 (0x12)
#define WIRED_AND_FILTER_LOWEST_DRIVE    (0x13)
#define WIRED_AND_FILTER_LOW_DRIVE       (0x14)
#define WIRED_AND_FILTER_HIGH_DRIVE      (0x15)
#define WIRED_AND_PULLUP                 (0x16)
#define WIRED_AND_PULLUP_LOWEST_DRIVE    (0x17)
#define WIRED_AND_PULLUP_LOW_DRIVE       (0x18)
#define WIRED_AND_PULLUP_HIGH_DRIVE      (0x19)
#define WIRED_AND_PU_FILTER              (0x1A)
#define WIRED_AND_PU_FILTER_LOWEST_DRIVE (0x1B)
#define WIRED_AND_PU_FILTER_LOW_DRIVE    (0x1C)
#define WIRED_AND_PU_FILTER_HIGH_DRIVE   (0x1D)


#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5

void init_connector_test(void);
void p_test(void);
void test_inputs(void);
void print_txparams(void);
void delayt(uint32_t val);
void GPIO_pinMode(GPIO_Port_TypeDef port, unsigned int pin, GPIO_Mode_TypeDef mode);

void led0_on(void);
void led1_on(void);
void led2_on(void);
void led3_on(void);
void led4_on(void);
void led5_on(void);
void led6_on(void);
void led7_on(void);

void led0_off(void);
void led1_off(void);
void led2_off(void);
void led3_off(void);
void led4_off(void);
void led5_off(void);
void led6_off(void);
void led7_off(void);

