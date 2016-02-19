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

#pragma once

#define RED_LED       2
#define BLUE_LED      1
#define GREEN_LED     0


class boardIO
{
 public:
  boardIO();
  void ledReadRed(void);
  void ledReadBlue(void);
  void ledReadGreen(void);
  void ledReadAll(void);
  void ledRedOff(void);
  void ledRedOn(void);
  void ledGreenOff(void);
  void ledGreenOn(void);
  void ledBlueOff(void);
  void ledBlueOn(void);
  void ledAllOff(void);
  void ledAllOn(void);
  void commBoardName(void);
  void commBootloaderVersion(void);
  void commChipID(void);
  void commCPUtype(void);
  void commFlashSize(void);
  void commSRAMsize(void);
  void printBoardParameters(void);
  char* getChipID(void);
  char* getBootloaderVersion(void);
  char* getFlashSize(void);
  char* getSRAMsize(void);
  char* getCPUtype(void);

 private:

};


