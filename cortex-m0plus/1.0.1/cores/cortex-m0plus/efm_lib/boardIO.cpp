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

#include "Arduino.h"

extern "C" {
#include "efm_pin_config.h"
#include "pins_arduino.h"
#include "efm_devinfo.h"
}

#include "boardIO.h"

extern LEUARTClass Serial;
boardIO IO;

boardIO::boardIO()
{
  ledAllOff();
}


void boardIO::ledRedOff(void)   {GPIO->P[ledPorts[RED_LED]].DOUTSET   = (1 << ledPins[RED_LED]);}
void boardIO::ledRedOn(void)    {GPIO->P[ledPorts[RED_LED]].DOUTCLR   = (1 << ledPins[RED_LED]);}
void boardIO::ledGreenOff(void) {GPIO->P[ledPorts[GREEN_LED]].DOUTSET = (1 << ledPins[GREEN_LED]);}
void boardIO::ledGreenOn(void)  {GPIO->P[ledPorts[GREEN_LED]].DOUTCLR = (1 << ledPins[GREEN_LED]);}
void boardIO::ledBlueOff(void)  {GPIO->P[ledPorts[BLUE_LED]].DOUTSET  = (1 << ledPins[BLUE_LED]);}
void boardIO::ledBlueOn(void)   {GPIO->P[ledPorts[BLUE_LED]].DOUTCLR  = (1 << ledPins[BLUE_LED]);}

void boardIO::ledAllOff(void)
{
  GPIO->P[ledPorts[RED_LED]].DOUTSET   = (1 << ledPins[RED_LED]);
  GPIO->P[ledPorts[GREEN_LED]].DOUTSET = (1 << ledPins[GREEN_LED]);
  GPIO->P[ledPorts[BLUE_LED]].DOUTSET  = (1 << ledPins[BLUE_LED]);
}

void boardIO::ledAllOn(void)
{
  GPIO->P[ledPorts[RED_LED]].DOUTCLR   = (1 << ledPins[RED_LED]);
  GPIO->P[ledPorts[GREEN_LED]].DOUTCLR = (1 << ledPins[GREEN_LED]);
  GPIO->P[ledPorts[BLUE_LED]].DOUTCLR  = (1 << ledPins[BLUE_LED]);
}

void boardIO::ledReadRed(void)   {
  if((GPIO->P[dPorts[ledPorts[RED_LED]]].DIN >> ledPins[RED_LED]) & 0x1) {
    Serial.printf("{\"REDLED\":\"ISOFF\"}\r\n");
  } else {
    Serial.printf("{\"REDLED\":\"ISON\"}\r\n");
  }
}

void boardIO::ledReadBlue(void)  {
  if((GPIO->P[dPorts[ledPorts[BLUE_LED]]].DIN >> ledPins[BLUE_LED]) & 0x1) {
    Serial.printf("{\"BLUELED\":\"ISOFF\"}\r\n");
  } else {
    Serial.printf("{\"BLUELED\":\"ISON\"}\r\n");
  }
}

void boardIO::ledReadGreen(void) {
  if((GPIO->P[dPorts[ledPorts[GREEN_LED]]].DIN >> ledPins[GREEN_LED]) & 0x1) {
    Serial.printf("{\"GREENLED\":\"ISOFF\"}\r\n");
  } else {
    Serial.printf("{\"GREENLED\":\"ISON\"}\r\n");
  }
}

void boardIO::ledReadAll(void)
{
  if((GPIO->P[dPorts[ledPorts[RED_LED]]].DIN >> ledPins[RED_LED]) & 0x1) {
    Serial.printf("{\"REDLED\":\"ISOFF\",");
  } else {
    Serial.printf("{\"REDLED\":\"ISON\",");
  }
  if((GPIO->P[dPorts[ledPorts[BLUE_LED]]].DIN >> ledPins[BLUE_LED]) & 0x1) {
    Serial.printf("\"BLUELED\":\"ISOFF\",");
  } else {
    Serial.printf("\"BLUELED\":\"ISON\",");
  }
  if((GPIO->P[dPorts[ledPorts[GREEN_LED]]].DIN >> ledPins[GREEN_LED]) & 0x1) {
    Serial.printf("\"GREENLED\":\"ISOFF\"}\r\n");
  } else {
    Serial.printf("\"GREENLED\":\"ISON\"}\r\n");
  }
}

void boardIO::printBoardParameters(void)
{
  uint32_t *pnum = ((uint32_t *) 0x00FE081FCUL);
  uint32_t family  = (DEVINFO->PART & DEVINFO_PART_DEVICE_FAMILY_MASK) >> DEVINFO_PART_DEVICE_FAMILY_SHIFT;
  uint32_t partnum =  pnum[0] & DEVINFO_PART_DEVICE_NUMBER_MASK;
  uint32_t flashSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_FLASH_MASK) >> DEVINFO_MSIZE_FLASH_SHIFT) << 10;
  uint32_t sramSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_SRAM_MASK) >> DEVINFO_MSIZE_SRAM_SHIFT) << 10;
  uint32_t freq = get_hfrco_freq();

  // need to generalize these to work for any board - store actual board somewhere

  Serial.printf("{\"BRDNAME\":\"EFM32ZGUSB\",");
  Serial.printf("\"CHIPID\":\"%x%x\",",DEVINFO->UNIQUEH,DEVINFO->UNIQUEL);
  if ((family == DEVINFO_PART_DEVICE_FAMILY_ZG) && (partnum == 222) && (flashSize == 32768)) {
    Serial.printf("\"CPU\":\"EFM32ZG222F32\",");
  }
  Serial.printf("\"FLASHSIZE\":\"%d\",",flashSize);
  Serial.printf("\"SRAMSIZE\":\"%d\",",sramSize);
  Serial.printf("\"CLKFREQ\":\"%d\",",freq);
  Serial.printf("\"BLVER\":\"1.0\"}\r\n");
}

void boardIO::commBoardName(void)
{
  Serial.printf("{\"BRDNAME\":\"EFM32ZGUSB\"}\r\n");
}

void boardIO::commBootloaderVersion(void)
{
  // need to fix this to get the data from the actual bootloader
  Serial.printf("BLVER\":\"1.0\"}\r\n");
}

void boardIO::commChipID(void)
{
  Serial.printf("CHIPID\":\"%x%x\"}\r\n",DEVINFO->UNIQUEH,DEVINFO->UNIQUEL);
}

void boardIO::commCPUtype(void)
{
  uint32_t *pnum = ((uint32_t *) 0x00FE081FCUL);
  uint32_t family  = (DEVINFO->PART & DEVINFO_PART_DEVICE_FAMILY_MASK) >> DEVINFO_PART_DEVICE_FAMILY_SHIFT;
  uint32_t partnum =  pnum[0] & DEVINFO_PART_DEVICE_NUMBER_MASK;
  uint32_t flashSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_FLASH_MASK) >> DEVINFO_MSIZE_FLASH_SHIFT) << 10;

  if ((family == DEVINFO_PART_DEVICE_FAMILY_ZG) && (partnum == 222) && (flashSize == 32768)) {
    Serial.printf("CPU\":\"EFM32ZG222F32\"}");
  }
}

void boardIO::commFlashSize(void)
{
  uint32_t flashSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_FLASH_MASK) >> DEVINFO_MSIZE_FLASH_SHIFT) << 10;
  Serial.printf("FLASHSIZE\":\"%d\"}\r\n",flashSize);
}

void boardIO::commSRAMsize(void)
{
  uint32_t sramSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_SRAM_MASK) >> DEVINFO_MSIZE_SRAM_SHIFT) << 10;
  Serial.printf("SRAMSIZE\":\"%d\"}\r\n",sramSize);
}

char* boardIO::getChipID(void)
{
  static char id[] = "0000000000000000";
  sprintf(id, "%x%x",DEVINFO->UNIQUEH,DEVINFO->UNIQUEL);
  return id;
}


