/**************************************************************************
 * @file serial.c
 * @brief Serial code for the EFM32 bootloader
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

volatile struct circularBuffer
{
  uint8_t  data[BUFFERSIZE];  /* data buffer */
  uint32_t rdI;               /* read index */
  uint32_t wrI;               /* write index */
  uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
  bool     overflow;          /* buffer overflow indicator */
} rxBuf0, txBuf0, rxBuf1, txBuf1 = { {0}, 0, 0, 0, false };


void tty1_rx_data(uint8_t rxData)
{
  rxBuf1.data[rxBuf1.wrI] = rxData;
  rxBuf1.wrI = (rxBuf1.wrI + 1) % BUFFERSIZE;
  rxBuf1.pendingBytes++;
  if (rxBuf1.pendingBytes > BUFFERSIZE)    // Flag Rx overflow
    {
      rxBuf1.overflow = true;
    }
}

uint8_t tty1_get_pending_byte(void)
{
  uint8_t data = txBuf1.data[txBuf1.rdI];      // Transmit pending character
  txBuf1.rdI = (txBuf1.rdI + 1) % BUFFERSIZE;
  txBuf1.pendingBytes--;
  return data;
}

uint32_t tty1_get_number_pendingBytes(void)
{
  return txBuf1.pendingBytes;
}


// Transmit single byte
void SERIAL_txByte(uint8_t data)
{
    if ((txBuf1.pendingBytes + 1) > BUFFERSIZE)  // Check if Tx queue has room for new data
      {
	while ((txBuf1.pendingBytes + 1) > BUFFERSIZE) ;    // Wait until there is room in queue
      }
    txBuf1.data[txBuf1.wrI] = data;  // Copy ch into txBuffer
    txBuf1.wrI             = (txBuf1.wrI + 1) % BUFFERSIZE;
    tty1_disable_tx_ints();
    txBuf1.pendingBytes++;  // Increment pending byte counter
    tty1_enable_tx_ints();
    tty1_enable_tx_int();
}

uint8_t SERIAL_rxByte(void)
{
  uint8_t ch;
  // Check if there is a byte that is ready to be fetched. If no byte is ready, wait for incoming data
  if (rxBuf1.pendingBytes < 1) {
    while (rxBuf1.pendingBytes < 1) ;
  }
  ch = rxBuf1.data[rxBuf1.rdI];    // Copy data from buffer
  rxBuf1.rdI = (rxBuf1.rdI + 1) % BUFFERSIZE;
  tty1_disable_rx_ints();
  rxBuf1.pendingBytes--;    // Decrement pending byte counter
  tty1_enable_rx_ints();
  return ch;
}

uint8_t SERIAL_check_rxByte(void)
{
  uint8_t ch;
  if (rxBuf1.pendingBytes > 0) {
    ch = rxBuf1.data[rxBuf1.rdI];    // Copy data from buffer
    rxBuf1.rdI = (rxBuf1.rdI + 1) % BUFFERSIZE;
    tty1_disable_rx_ints();
    rxBuf1.pendingBytes--;    // Decrement pending byte counter
    tty1_enable_rx_ints();
    return ch;
  }
  return 0;
}

uint8_t SERIAL_rx_ready(void)
{
  return (rxBuf1.pendingBytes);
}


void putc1(void* p, char ch)
{
  (void) p;

  while ((txBuf1.pendingBytes + 1) > BUFFERSIZE) ;    // Wait until there is room in queue
  txBuf1.data[txBuf1.wrI] = ch;  // Copy ch into txBuffer
  txBuf1.wrI = (txBuf1.wrI + 1) % BUFFERSIZE;
  tty1_disable_tx_ints();
  txBuf1.pendingBytes++;  // Increment pending byte counter
  tty1_enable_tx_ints();
  tty1_enable_tx_int();
}

