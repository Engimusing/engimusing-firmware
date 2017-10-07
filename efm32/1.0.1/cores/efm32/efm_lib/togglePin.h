///
///@file togglePin.h
///@brief Contains the TogglePin class which Toggles a pin periodically
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

#include <Arduino.h>
#include "wiring_constants.h"

///@brief This class is used for setting up a digital output to toggle between high and low at a set interval. 
class TogglePin
{
 public:
  
  ///@brief Constructor which initializes some internal variables
  ///@return Returns a TogglePin object
  TogglePin();
  
  ///@brief Sets up configuration for TogglePin class
  ///@param [in] toggleTime Time in milliseconds between toggling of digital output
  ///@param [in] activeLevel Voltage level for setting the pin to turn on the device being controlled by the pin
  void begin(int toggleTime, uint8_t activeLevel = HIGH);
  
  ///@brief Sets up configuration for TogglePin class
  ///@param [in] dwPin Pin to control with this instance of the TogglePin class and toggle periodically
  ///@param [in] offTime Time to keep the pin in the off state or at the !activeLevel
  ///@param [in] onTime Time to keep the pin in the on state or at the activeLevel
  ///@param [in] activeLevel Voltage level for setting the pin to turn on the device being controlled by the pin
  void begin(uint32_t dwPin, int offTime, int onTime, uint8_t activeLevel = HIGH);
  
  ///@brief Sets up configuration for TogglePin class
  ///@param [in] dwPin Pin to control with this instance of the TogglePin class and toggle periodically
  ///@param [in] dwMode Wiring mode for the pin if it needs to be something besides OUTPUT
  ///@param [in] offTime Time to keep the pin in the off state or at the !activeLevel
  ///@param [in] onTime Time to keep the pin in the on state or at the activeLevel
  ///@param [in] activeLevel Voltage level for setting the pin to turn on the device being controlled by the pin
  void begin(uint32_t dwPin, WiringModeTypeDef dwMode, int offTime, int onTime, uint8_t activeLevel = HIGH);
  
  ///@brief Call periodically so that it can update the state of the pin if enough time has past and it is time to toggle the pin
  void update(void);
  
  ///@brief Sets both the offTime and onTime to be the same value
  ///@param [in] time Time in milliseconds for the pin to be off and on
  void setToggleTime(int time) ;
  
  ///@brief Sets the off and on times
  ///@param [in] offTime Time to keep the pin in the off state or at the !activeLevel
  ///@param [in] onTime Time to keep the pin in the on state or at the activeLevel
  void setOffOnTimes(int offTime, int onTime);
  
  ///@brief Get the offTime that is currently being used
  int offTime();
  
  ///@brief Get the onTime that is currently being used
  int onTime();
  
 private:
  Timeout myOnTimeout;
  Timeout myOffTimeout;
  int myOn;
  uint32_t myPin;
  uint8_t myActiveLevel;
  
};

