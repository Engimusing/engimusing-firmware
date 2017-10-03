///
///@file coreclk.h
///@brief Core Clock speeds for different CORTEX cores
///
///@section License
///Copyright (c) 2016 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///

#pragma once

#ifdef CORTEX_M0PLUS
  #define VARIANT_MCK 21000000
#elif  CORTEX_M3
  #define VARIANT_MCK 28000000
#elif  CORTEX_M4
  #define VARIANT_MCK 28000000
#endif

