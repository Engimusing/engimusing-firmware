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

void boardIO::printBoardParameters(void)
{
  uint32_t *pnum = ((uint32_t *) 0x00FE081FCUL);
  uint32_t family  = (DEVINFO->PART & DEVINFO_PART_DEVICE_FAMILY_MASK) >> DEVINFO_PART_DEVICE_FAMILY_SHIFT;
  uint32_t partnum =  pnum[0] & DEVINFO_PART_DEVICE_NUMBER_MASK;
  uint32_t flashSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_FLASH_MASK) >> DEVINFO_MSIZE_FLASH_SHIFT) << 10;
  uint32_t sramSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_SRAM_MASK) >> DEVINFO_MSIZE_SRAM_SHIFT) << 10;
  uint32_t freq = get_hfrco_freq();

  Serial.printf("\r\n\r\n<BRDINFO>\r\n  <BRD>EFM32ZGUSB</BRD>\r\n  <BLVER>1.0</BLVER>\r\n");
  Serial.printf("  <CHIPID>%x%x</CHIPID>\r\n",DEVINFO->UNIQUEH,DEVINFO->UNIQUEL);

  if ((family == DEVINFO_PART_DEVICE_FAMILY_ZG) && (partnum == 222) && (flashSize == 32768)) {
    Serial.printf("  <CPU>EFM32ZG222F32</CPU>\r\n");
  } else {
    Serial.printf("<CPU>Wrong Gecko</CPU>\r\n");
  }

  Serial.printf("  <FLASHSIZE>%d</FLASHSIZE>\r\n",flashSize);
  Serial.printf("  <SRAMSIZE>%d</SRAMSIZE>\r\n",sramSize);
  Serial.printf("  <CLKFREQ>%d</CLKFREQ>\r\n",freq);

  Serial.printf("</BRDINFO>\r\n");
}

