///
///@file timeout.h
///@brief Contains Timeout Class which is used for timing an interval
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

///@brief This class is used for timing and will return true from it's update() when the timeout expires
class Timeout
{
 public:
  ///@brief Contructor initializes a few internal variables
  ///@return Returns Timeout object
  Timeout();
  
  ///@brief Setup the Timeout setting and start the timing
  ///@param [in] timeoutRateMs Number of milliseconds before update will return true
  ///@param [in] loop If true then then update() will return true once every timeoutRateMs milliseconds
  ///@details If loop is false then update() will return true after timeoutRateMs milliseconds and will
  /// return true forever after that. 
  /// If loop is true then update() will return true once every timeoutRateMs milliseconds.  
  void begin(int timeoutRateMs = 1000, bool loop = true);
  
  ///@brief Reset the timer and after timeoutTime() milliseconds after reset() is called update() will return true again.
  void reset(); 
  
  ///@brief Change the timeout length.
  ///@param [in] timeoutRateMs Timeout length of time in milliseconds before update() returns true.
  void setTimeoutTime(int timeoutRateMs);
  
  ///@brief Get the current timeout length 
  ///@return Timeout length of time in milliseconds before update() returns true.
  int timeoutTime();
  
  ///@brief Set whether or not the timeout should loop or only trigger once.
  ///@param [in] loop If true then the timeout will loop
  void setShouldLoop(bool loop);
  
  ///@brief Should be run periodically to check if the timeout length of time has past
  ///@return Returns true if the timeout has expired and false if it has not. 
  ///@details Will return true forever after the timeout expires if loop is set to false. 
  /// If loop is true then it will return true once every timeoutTime() milliseconds.
  /// If loop is false then it will return true forever after timeoutTime() milliseconds has past.
  bool update(void);
  
 private:
  bool myLoop;
  int myTimeoutTime;
  int myLastUpdateTime;
};

