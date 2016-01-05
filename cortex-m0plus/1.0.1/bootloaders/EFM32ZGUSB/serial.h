/**************************************************************************
 * @file usart.h
 * @brief USART code for the EFM32 bootloader
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

#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdbool.h>
#include "em_usart.h"

void    SERIAL_txByte(uint8_t uartID, uint8_t data);
uint8_t SERIAL_rxByte(uint8_t uartID);
uint8_t SERIAL_check_rxByte(uint8_t uartID);
uint8_t SERIAL_rx_ready(uint8_t uartID);

void    SERIAL_printString(uint8_t uartID, const uint8_t *string);
void    SERIAL_printHex(uint8_t uartID, uint32_t integer);

void tty0_enable_rx_ints(void);
void tty0_disable_rx_ints(void);
void tty1_enable_rx_ints(void);
void tty1_disable_rx_ints(void);

void tty0_enable_tx_ints(void);
void tty0_disable_tx_ints(void);
void tty1_enable_tx_ints(void);
void tty1_disable_tx_ints(void);


// Declare a circular buffer structure to use for Rx and Tx queues
#define BUFFERSIZE          256

#endif
