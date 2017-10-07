///
///@file io_types.h
///@brief Defines for a few IO types
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
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

#define  __I   volatile  // Read Only permission
#define  __IO  volatile  // Read Write permission
#define  __O   volatile  // Write only permission
#define __ASM            __asm          // asm keyword for GNU Compiler
#define __INLINE         inline         // inline keyword for GNU Compiler
#define __STATIC_INLINE  static inline

