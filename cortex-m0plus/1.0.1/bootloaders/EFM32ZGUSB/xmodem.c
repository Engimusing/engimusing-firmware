/**************************************************************************
 * @file xmodem.c
 * @brief XMODEM protocol
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

#include "config.h"
#include "xmodem.h"
#include "serial.h"
#include "flash.h"
#include "crc.h"
 
const uint8_t dot[]    = ".";


extern const uint32_t bootloader_size;

#define ALIGNMENT(base,align) (((base)+((align)-1))&(~((align)-1)))

// Packet storage. Double buffered version.
uint8_t rawPacket[2][ALIGNMENT(sizeof(XMODEM_packet),4)] __attribute__ ((aligned(4)));


// Verifies checksum, packet numbering and pkt The packet to verify
__INLINE int XMODEM_verifyPacketChecksum(XMODEM_packet *pkt, int sequenceNumber)
{
  uint16_t packetCRC;
  uint16_t calculatedCRC;

  printf1('#');
  if (pkt->packetNumber + pkt->packetNumberC != 255) { // Check the packet number integrity
    SERIAL_txByte(XMODEM_NAK);
    printf1("!");
    return -1;
  }
  if (pkt->packetNumber != (sequenceNumber % 256)) { // Check that the packet number matches the excpected number
    SERIAL_txByte(XMODEM_NAK);
    printf1("@");
    return -1;
  }

  calculatedCRC = CRC_calc((uint8_t *) pkt->data, (uint8_t *) &(pkt->crcHigh));
  packetCRC     = pkt->crcHigh << 8 | pkt->crcLow;

  if (calculatedCRC != packetCRC) { // Check the CRC value
    SERIAL_txByte(XMODEM_NAK);
    printf1("~");
    return -1;
  }
  return 0;
}


// Starts a XMODEM download.
int XMODEM_download(uint32_t baseAddress, uint32_t endAddress)
{
  XMODEM_packet *pkt;
  uint32_t      i;
  uint32_t      addr;
  uint32_t      byte;
  uint32_t      sequenceNumber = 1;

  printf1("Erase\r\n");

  for (addr = baseAddress; addr < endAddress; addr += flashPageSize) {
    WDOG_Feed();
    FLASH_eraseOneBlock(addr);
    printf1(".");
  }
  printf1("#");

  // Send one start transmission packet. Wait for a response. If there is no
  // response, we resend the start transmission packet.
  // Note: This is a fairly long delay between retransmissions(~6 s).
  while(1) {
    SERIAL_txByte(XMODEM_NCG);
    for (i = 0; i < 100000; i++) {
      WDOG_Feed();
      if(SERIAL_rx_ready())
	goto xmodem_transfer;
    }
  }
 xmodem_transfer:
  while(1) {
    WDOG_Feed();
    // Swap buffer for packet buffer
    pkt = (XMODEM_packet *) rawPacket[sequenceNumber & 1];

    // Fetch the first byte of the packet explicitly, as it defines the rest of the packet
    pkt->header = SERIAL_rxByte();

    if (pkt->header == XMODEM_EOT)  {     // Check for end of transfer
      printf1(XMODEM_ACK);  // Acknowledget End of transfer
      break;
    }
    // If the header is not a start of header (SOH), then cancel the transfer.
    if (pkt->header != XMODEM_SOH)	{
      SERIAL_txByte(XMODEM_NAK);
      printf1('^');
      return -1;
    }
    // Fill the remaining bytes packet
    // Byte 0 is padding, byte 1 is header
    uint32_t t = millis();
    for (byte = 2; byte < sizeof(XMODEM_packet); byte++) {
      *(((uint8_t *) pkt) + byte) = SERIAL_rxByte();
      if(t > millis() + 12) {
	printf1('`');
	SERIAL_txByte(XMODEM_NAK);
	break;
      }
    }
    if (XMODEM_verifyPacketChecksum(pkt, sequenceNumber) != 0) {
      // On a malformed packet, we send a NAK, and start over
      //SERIAL_printString(1, s12);
      SERIAL_txByte(XMODEM_NAK);
      continue;
    }
    // Write data to flash
    FLASH_writeBlock((void *) baseAddress,
		     (sequenceNumber - 1) * XMODEM_DATA_SIZE,
		     XMODEM_DATA_SIZE,
		     (uint8_t const *) pkt->data);

    sequenceNumber++;
    SERIAL_txByte(XMODEM_ACK);    // Send ACK
  }
  WDOG_Feed();
  while (DMA->CHENS & DMA_CHENS_CH0ENS) ;  // Wait for the last DMA transfer to finish.
  printf1("$");

  uint32_t endp =  bootloader_size + (XMODEM_DATA_SIZE * (sequenceNumber -1));
  uint16_t crc = CRC_calc((uint8_t *)bootloader_size, (uint8_t *)endp);
  printf1("CRC of data in Flash = %x\n\r",crc);
  return 0;
}

int XMODEM_downloadAndReset(uint32_t baseAddress, uint32_t endAddress)
{
  XMODEM_download(baseAddress, endAddress);
  printf1("resetting");
  for(volatile int i = 0; i < 100000; i++);
  SCB->AIRCR = 0x05FA0004;
  //there is nowhere to jump back to if this is called from the application so loop
  // forever in case the reset command is not immediete
  while(0){}
  return 0;
}


