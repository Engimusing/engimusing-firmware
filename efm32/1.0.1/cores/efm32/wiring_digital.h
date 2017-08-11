/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
  Copyright (c) 2014 Arduino.  All right reserved.

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

#include "wiring_constants.h"

#ifdef __cplusplus
extern "C" {
#endif


	void GPIO_config(uint32_t port, uint32_t pin, WiringModeTypeDef ulMode);


  /**
   * \brief Configures the specified pin to behave either as an input or an output.
   * See the description of digital pins for details.
   *
   * \param ulPin The number of the pin whose mode you wish to set
   * \param ulMode Can be INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN
   */
  extern uint8_t pinMode( uint32_t dwPin, WiringModeTypeDef dwMode ) ;
  extern uint8_t intrPinMode(uint32_t pin, WiringModeTypeDef mode);

  /**
   * \brief Write a HIGH or a LOW value to a digital pin.
   *
   * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the
   * corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
   *
   * If the pin is configured as an INPUT, writing a HIGH value with digitalWrite() will enable an internal
   * 20K pullup resistor (see the tutorial on digital pins). Writing LOW will disable the pullup. The pullup
   * resistor is enough to light an LED dimly, so if LEDs appear to work, but very dimly, this is a likely
   * cause. The remedy is to set the pin to an output with the pinMode() function.
   *
   * \param dwPin the pin number
   * \param dwVal HIGH or LOW
   */
  extern void digitalWrite( uint32_t dwPin, uint32_t dwVal ) ;

  /**
   * \brief Reads the value from a specified digital pin, either HIGH or LOW.
   *
   * \param ulPin The number of the digital pin you want to read (int)
   *
   * \return HIGH or LOW
   */
  extern int digitalRead( uint32_t ulPin ) ;
  extern int intrDigitalRead(uint32_t pin);

  void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);

  void detachInterrupt(uint8_t pin);

  void enableDebugPins();
#ifdef __cplusplus
}
#endif

