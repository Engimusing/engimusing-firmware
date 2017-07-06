/**************************************************************************//**
 * @file lesense_letouch.h
 * @brief LESENSE CAPACITIVE TOUCH code example
 * @author Silicon Labs
 * @version 2.05
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
  
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

#include "Arduino.h"

#if NUM_LESENSE_CHANNELS > 0

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


class CapSenseClass 
{
public:
    CapSenseClass();
    
    void begin();
    
    void initChannel(uint8_t channel, float sensitivity);
    bool isChannelTouched(uint8_t channel);
    uint16_t channelsState();
    void updateChannelsState(uint16_t state); //should only be called by the LESENSE_IRQHandler
    void update();

    
    
protected:
 
    /* Function prototypes */
    void setupACMP(void);
    void setupLESENSE(void);
    void setupGPIO(void);
    void setupCMU(void);
    void calibrate(void);
    
    uint16_t getChannelMaxValue(uint8_t channel);
    uint16_t getChannelMinValue(uint8_t channel);
    uint16_t getMaxValue(volatile uint16_t* A, uint16_t N);
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
    
    uint16_t myLastCalibration;
};

extern CapSenseClass CapSense;

/**************************************************************************//**
 * Interrupt handlers prototypes
 *****************************************************************************/
void LESENSE_IRQHandler(void);

#endif