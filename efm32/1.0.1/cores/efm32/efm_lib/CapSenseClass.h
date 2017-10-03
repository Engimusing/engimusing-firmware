///
///@file CapSenseClass.h
///@brief Contains class for accessing the capacitance sensors on an Energy Micro
///
///@details Based on lesense_letouch.h from examples provided by Silicon Labs
///
///@section License
///Copyright (c) 2016 Engimusing LLC.  All right reserved.
/// </p><b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
///
///
///Permission is granted to anyone to use this software for any purpose,
///including commercial applications, and to alter it and redistribute it
///freely, subject to the following restrictions:
///
///1. The origin of this software must not be misrepresented; you must not
///   claim that you wrote the original software.
///2. Altered source versions must be plainly marked as such, and must not be
///   misrepresented as being the original software.
///3. This notice may not be removed or altered from any source distribution.
///
///DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
///obligation to support this Software. Silicon Labs is providing the
///Software "AS IS", with no express or implied warranties of any kind,
///including, but not limited to, any implied warranties of merchantability
///or fitness for any particular purpose or warranties against infringement
///of any proprietary rights of a third party.
///
///Silicon Labs will not be liable for any consequential, incidental, or
///special damages, or any other relief, or for any claim by any third party,
///arising from your use of this Software.
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

#include "Arduino.h"

#if NUM_LESENSE_CHANNELS > 0

#include "efm_lesense.h"

/** These are settings that need to be tuned for different PCB's, overlays and applications. */

/** Scan frequency for LESENSE, how often all the pads are scanned. */
#define LESENSE_SCAN_FREQUENCY          50

/** Sample delay, how long the rc-oscillations are sampled. */
#define SAMPLE_DELAY                   30 

/** Validate count is the number of consecutive scan-cycles a button needs to */
/** be in the changed state before an actual button press or release is acknowledged. */
#define VALIDATE_CNT                   10

/** Number of calibration events used to calculate threshold. */
#define NUMBER_OF_CALIBRATION_VALUES    10

/** Interval between calibration, in seconds. */
#define CALIBRATION_INTERVAL            5

///@brief Used for accessing capacitance sensors. Should be setup as a global object.
class CapSenseClass 
{
public:
    
    ///@brief Constructor that initializes some internal variables
    ///@return Returns a CapSenseClass object
    ///@details There is a single global CapSenseClass called CapSense that is defined in CapSenseClass.cpp
    /// This global should be the only instance of CapSenseClass.
    CapSenseClass();
    
    ///@brief Start up the cap sense class and configure it. Should be called before any other functions.
    ///@param [in] lesenseClkDiv Sets up the clock divider to use for the capacitance sensor
    ///@param [in] sampleDelay Set up the delay to use with the capacitance sensor
    ///@param [in] validateCnt Number of times to measure the channel before reporting a touch
    void begin(LESENSE_ClkPresc_TypeDef lesenseClkDiv = lesenseClkDiv_1, uint16_t sampleDelay = SAMPLE_DELAY, uint16_t validateCnt = VALIDATE_CNT);
    
    ///@brief Called to initialize a Channel and start the readings for the specified channel
    ///@param [in] channel channel number to start capacitance sensor readings
    ///@param [in] sensitivity If != to 0.0 than the channel is turned on. If 0.0 then the channel is turned off. Also used to control how sensitive the channel is to touch.
    void initChannel(uint8_t channel, float sensitivity);
    
    ///@brief Get the current state of all the channels
    ///@return Returns a 16-bit integer where each bit represents a button and if the button has been pressed then the corresponding bit will be set to 1
    uint16_t channelsState();
    ///@brief Function that should not be called except by the LESENSE_IRQHandler. Used to update the current state of the buttons.
    ///@param [in] state Current state of the buttons
    void updateChannelsState(uint16_t state); //should only be called by the LESENSE_IRQHandler
    ///@brief Should be called periodically (called by CapSenseDevice::update()). Calibrates the CapSense every CALIBRATION_INTERVAL seconds
    void update();
    ///@brief Scan a single channel and return the result. This can be used to calculate the actual capacitance.
    ///@param [in] channelToScan Channel to scan and return the capacitance for.
    ///@return Raw capacitance value recieved from LESENSE 
    uint16_t scanSingleChannel(uint16_t channelToScan);
    
    ///@brief Return the max value seen for the specified channel
    ///@param [in] channel Channel to get the maximum value for
    ///@return Maximum value seen for the specified channel
    uint16_t getChannelMaxValue(uint8_t channel);
    ///@brief Return the min value seen for the specified channel
    ///@param [in] channel Channel to get the minimum value for
    ///@return Minimum value seen for the specified channel
    uint16_t getChannelMinValue(uint8_t channel);
    
    ///@brief Calibrate all active channels. Run automatically ever CALIBRATION_INTERVAL seconds or after a new channel is initialized
    void calibrate(void);
    
protected:
 
    void setupACMP(void);
    void setupLESENSE(void);
    void setupGPIO(void);
    void setupCMU(void);
    
    

    ///@brief Helper function for getting the max value in a list of values
    ///@param [in] A List of 16-bit integers
    ///@param [in] N Number of integers in A
    ///@return Maximum integer in A
    uint16_t getMaxValue(volatile uint16_t* A, uint16_t N);
    ///@brief Helper function for getting the min value in a list of values
    ///@param [in] A List of 16-bit integers
    ///@param [in] N Number of integers in A
    ///@return Minimum integer in A
    uint16_t getMinValue(volatile uint16_t* A, uint16_t N);
    
    uint16_t myCalibrationValue[NUM_LESENSE_CHANNELS][NUMBER_OF_CALIBRATION_VALUES];
    uint16_t myButtonsPressed;
    uint16_t myChannelMaxValue[NUM_LESENSE_CHANNELS];
    uint16_t myChannelMinValue[NUM_LESENSE_CHANNELS];

    uint16_t myChannelsUsedMask;
    uint8_t myNumChannelsUsed;
    float myChannelThresholdPercent[NUM_LESENSE_CHANNELS];
    bool myInitialized;
    bool myChannelInitDirty;
    
    uint32_t myLastCalibration;
    
    uint16_t mySampleDelay;
    LESENSE_ClkPresc_TypeDef myLesenseClkDiv;
    
};

///@brief Global object for accessing LESENSE. Allows for checking for touches on capacitance sensors.
extern CapSenseClass CapSense;
    
///@brief Interrupt handlers prototypes for LESENSE. Checks for touches on all active channels and sets up the CapSense state appropriately
void LESENSE_IRQHandler(void);

#endif