///
///@file wiring_digital.h
///@brief Utility functions for accessing the pins in a digital way.
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2014 Arduino.  All right reserved.
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

#include "wiring_constants.h"

#ifdef __cplusplus
extern "C" {
#endif


	///@brief Used to configure a pin, shouldn't be used outside of this and the wiring_digital.cpp files.
    ///@param [in] port Port the pin is a part of
    ///@param [in] pin Pin number to configure
    ///@param [in] ulMode WiringModeTypeDef mode to set the pin to use
    void GPIO_config(uint32_t port, uint32_t pin, WiringModeTypeDef ulMode);


  /**
   * \brief Configures the specified pin to behave either as an input or an output.
   * See the description of digital pins for details.
   *
   * \param ulPin The number of the pin whose mode you wish to set
   * \param ulMode Can be INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN
   */
  extern uint8_t pinMode( uint32_t dwPin, WiringModeTypeDef dwMode ) ;
  
    /**
   * \brief Configures the specified pin to behave either as an input or an output.
   * See the description of digital pins for details.
   *
   * \param ulPin The number of the pin whose mode you wish to set
   * \param ulMode Can be INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN
   */
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
  
    /**
   * \brief Reads the value from a specified digital pin, either HIGH or LOW.
   *
   * \param ulPin The number of the digital pin you want to read (int)
   *
   * \return HIGH or LOW
   */
  extern int intrDigitalRead(uint32_t pin);

  
    ///@brief Attach an interrupt to a pin
    ///@param [in] pin pin to attach the interrupt function to
    ///@param [in] gpioIntFunc Function to attach to the pin
    ///@param [in] mode mode to use for the interrupt, can be RISING, FALLING, or CHANGE
    ///@details Defined in the gpio_inters.cpp file
    void attachInterrupt(uint8_t pin, void (*gpioIntFunc)(void), uint8_t mode);

    ///@brief Dettach an interrupt from a pin
    ///@param [in] pin pin to detach the interrupt function to
    ///@details Defined in the gpio_inters.cpp file
    void detachInterrupt(uint8_t pin);

    ///@brief Enables the debug pins. They can be used as a couple more GPIO's or even a simple Two Wire interface
    void enableDebugPins();
    
#ifdef __cplusplus
}
#endif

