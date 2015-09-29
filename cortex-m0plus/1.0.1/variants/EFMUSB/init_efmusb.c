/*
  Copyright (c) 2014-2015 Engimusing LLC.  All right reserved.

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

#include "init_efm.h"
#include "efm_pin_config.h"

#ifdef __cplusplus
extern "C" {
#endif


  void init( void )
  {
    init_efm32zg();
    GPIO_config(PORTA,  8, OUTPUT);
    GPIO_config(PORTA,  9, OUTPUT);
    GPIO_config(PORTA, 10, OUTPUT);
    GPIO->P[PORTA].DOUTSET = (1 << 8);
    GPIO->P[PORTA].DOUTSET = (1 << 9);
    GPIO->P[PORTA].DOUTSET = (1 << 10);
  }

#ifdef __cplusplus
}
#endif
