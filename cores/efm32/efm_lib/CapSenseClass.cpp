/**************************************************************************//**
 * @file lesense_letouch.c
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

#include "efm_devinfo.h"
#include "efm_cmu_config.h"
#include "efm_acmp.h"
#include "efm_gpio.h"
#include "efm_int.h"
#include "CapSenseClass.h"

#include "Arduino.h"

#if NUM_LESENSE_CHANNELS > 0


static uint16_t sValidateCnt = VALIDATE_CNT;

CapSenseClass::CapSenseClass()
    : myInitialized(false)
    , myChannelsUsedMask(0)
    , myNumChannelsUsed(0)
    , myButtonsPressed(0)
    , myChannelInitDirty(false)
{
    for(int i = 0; i < NUM_LESENSE_CHANNELS; i++)
    {    
        /* Init min and max values for each channel */
        myChannelMaxValue[i] = 0;
        myChannelMinValue[i] = 0xffff;
        myChannelThresholdPercent[i] = 0.0;
    }
}


/**************************************************************************//**
 * @brief Initializes the capacative touch system with LESENSE.
 *
 * @param[in] sensitivity
 *   An array of floats, indication of threshold level, in percent,
 *   of nominal count value.
 *
 *****************************************************************************/
void CapSenseClass::begin(LESENSE_ClkPresc_TypeDef lesenseClkDiv, uint16_t sampleDelay, uint16_t validateCnt)
{
  if(myInitialized)
      return;
  
  myLesenseClkDiv = lesenseClkDiv;
  mySampleDelay= sampleDelay;
  sValidateCnt = validateCnt;
  /* Disable interrupts while initializing */
  INT_Disable();

  /* Setup CMU. */
  setupCMU();
  
  /* Setup GPIO. */
  setupGPIO();
  
  /* Setup ACMP. */
  setupACMP();
  
  /* Setup LESENSE. */
  setupLESENSE();
  
  /* Initialization done, enable interrupts globally. */
  INT_Enable();
  
  myInitialized = true;

}

void CapSenseClass::initChannel(uint8_t channel, float sensitivity)
{
    if(sensitivity != 0.0)
    {
        if(myChannelThresholdPercent[channel] == 0.0)
        {
            myNumChannelsUsed++;
        }
        
        myChannelsUsedMask |= (1 << channel);
        
        
        
        /* Channel configuration */
        static const LESENSE_ChDesc_TypeDef initLesenseCh =
        {
            .enaScanCh     = true,
            .enaPin        = true,
            .enaInt        = true,
            .chPinExMode   = lesenseChPinExDis,
            .chPinIdleMode = lesenseChPinIdleDis,
            .useAltEx      = false,
            .shiftRes      = false,
            .invRes        = false,
            .storeCntRes   = true,
            .exClk         = lesenseClkLF,
            .sampleClk     = lesenseClkLF,
            .exTime        = 0x0,
            .sampleDelay   = mySampleDelay,
            .measDelay     = 0x0,
            .acmpThres     = 0x0,                   // don't care, configured by ACMPInit
            .sampleMode    = lesenseSampleModeCounter,
            .intMode       = lesenseSetIntLevel,
            .cntThres      = 0x0,                   // Configured later by calibration function
            .compMode      = lesenseCompModeLess
        };
        LESENSE_ChannelConfig(&initLesenseCh, channel);
        
        
    }
    else
    {
        if(myChannelThresholdPercent[channel] != 0.0)
        {
            myNumChannelsUsed--;
        }
        
        myChannelsUsedMask &= ~(1 << channel);
    }
    
    myChannelThresholdPercent[channel] = sensitivity;
    
    myChannelInitDirty = true;
}

void CapSenseClass::update()
{
    if(myChannelInitDirty)
    {
        for(int i = 0; i < NUMBER_OF_CALIBRATION_VALUES * 10; i++)
        {
            LESENSE_ScanStart();
            calibrate();
        }
        myChannelInitDirty = false;
        myLastCalibration = millis();
    }
    else if(myLastCalibration + (CALIBRATION_INTERVAL * 1000) < millis())
    {
        myLastCalibration = millis();
        calibrate();
    }
}

/***************************************************************************//**
 * @brief
 *   Get the buttons pressed variable, one bit for each channel pressed 
 *   or'ed together.
 *
 * @return
 *   The touch buttons/pads that are in touched state is or'ed together and
 *   returned.
 ******************************************************************************/
uint16_t CapSenseClass::channelsState(void)
{
  return myButtonsPressed;
}

void CapSenseClass::updateChannelsState(uint16_t state)
{
    myButtonsPressed = state;
}

/***************************************************************************//**
 * @brief
 *   Get the maximum value registered for a given channel.
 *
 * @param[in] channel
 *   The channel to get maximum value for
 *
 * @return
 *   The maximum value registered for the given channel.
 ******************************************************************************/
uint16_t CapSenseClass::getChannelMaxValue(uint8_t channel)
{
  return myChannelMaxValue[channel];
}

/***************************************************************************//**
 * @brief
 *   Get the minimum value registered for a given channel.
 *
 * @param[in] channel
 *   The channel to get minimum value for
 *
 * @return
 *   The minimum value registered for the given channel.
 ******************************************************************************/
uint16_t CapSenseClass::getChannelMinValue(uint8_t channel)
{
  return myChannelMinValue[channel];
}

/**************************************************************************//**
 * @brief  Enable clocks for all the peripherals to be used
 *****************************************************************************/
void CapSenseClass::setupCMU( void )
{
  /* Ensure core frequency has been updated */
  SystemCoreClockUpdate();

  /* ACMP */
  CMU_ClockEnable(cmuClock_ACMP0, true);
  CMU_ClockEnable(cmuClock_ACMP1, true);

  /* GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Low energy peripherals
  *   LESENSE
  *   LFXO clock must be enabled prior to enabling
  *   clock for the low energy peripherals */
 
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);

  CMU_ClockEnable(cmuClock_CORELE, true);
  CMU_ClockEnable(cmuClock_LESENSE, true);
}

/**************************************************************************//**
 * @brief  Sets up the ACMP
 *****************************************************************************/
void CapSenseClass::setupACMP( void )
{
  /* Configuration structure for ACMP */
  /* See application note document for description of the different settings. */
  static const ACMP_CapsenseInit_TypeDef acmpInit =
  {
    .fullBias                 = true,            //Configured according to application note
    .halfBias                 = true,            //Configured according to application note 
    .biasProg                 = 0x5,             //Configured according to application note
    .warmTime                 = acmpWarmTime512, //LESENSE uses a fixed warmup time
    .hysteresisLevel          = acmpHysteresisLevel5, //Configured according to application note
    .resistor                 = acmpResistor0,   //Configured according to application note   
    .lowPowerReferenceEnabled = false,           //LP-reference can introduce glitches with captouch
    .vddLevel                 = 0x30,            //Configured according to application note 
    .enable                   = false            //LESENSE enables the ACMP
  };
  
  /* Initialize ACMP in capsense mode*/
  ACMP_CapsenseInit(ACMP0, &acmpInit);
  ACMP_CapsenseInit(ACMP1, &acmpInit);

}

/**************************************************************************//**
 * @brief  Sets up the LESENSE
 *****************************************************************************/
void CapSenseClass::setupLESENSE( void )
{
  uint8_t i;
  
  /* LESENSE configuration structure */
  static const LESENSE_Init_TypeDef initLesense =
  {
    .coreCtrl         =
    {
      .scanStart    = lesenseScanStartPeriodic,
      .prsSel       = lesensePRSCh0,
      .scanConfSel  = lesenseScanConfDirMap,
      .invACMP0     = false,
      .invACMP1     = false,
      .dualSample   = false,
      .storeScanRes = false,
      .bufOverWr    = true,
      .bufTrigLevel = lesenseBufTrigHalf,
      .wakeupOnDMA  = lesenseDMAWakeUpDisable,
      .biasMode     = lesenseBiasModeDutyCycle,
      .debugRun     = false
    },

    .timeCtrl         =
    {
      .startDelay     = 0x0
    },

    .perCtrl          =
    {
      .dacCh0Data     = lesenseDACIfData,
      .dacCh0ConvMode = lesenseDACConvModeDisable,
      .dacCh0OutMode  = lesenseDACOutModeDisable,
      .dacCh1Data     = lesenseDACIfData,
      .dacCh1ConvMode = lesenseDACConvModeDisable,
      .dacCh1OutMode  = lesenseDACOutModeDisable,
      .dacPresc       = 0,
      .dacRef         = lesenseDACRefBandGap,
      .acmp0Mode      = lesenseACMPModeMux,   // only acmp mux controlled by lesense
      .acmp1Mode      = lesenseACMPModeMux,   // only acmp mux controlled by lesense
      .warmupMode     = lesenseWarmupModeNormal
    },

    .decCtrl          =
    {
      .decInput  = lesenseDecInputSensorSt,
      .initState = 0,
      .chkState  = false,
      .intMap    = false,
      .hystPRS0  = false,
      .hystPRS1  = false,
      .hystPRS2  = false,
      .hystIRQ   = false,
      .prsCount  = false,
      .prsChSel0 = lesensePRSCh0,
      .prsChSel1 = lesensePRSCh1,
      .prsChSel2 = lesensePRSCh2,
      .prsChSel3 = lesensePRSCh3
    }
  };

  /* Initialize LESENSE interface _with_ RESET. */
  LESENSE_Init(&initLesense, true);
    
  /* Set scan frequency */
  LESENSE_ScanFreqSet(0, LESENSE_SCAN_FREQUENCY);

  /* Set clock divisor for LF clock. */
  LESENSE_ClkDivSet(lesenseClkLF, myLesenseClkDiv);
  //LESENSE_ClkDivSet(lesenseClkLF, lesenseClkDiv_8);

  /* Enable interrupt in NVIC. */
  NVIC_EnableIRQ(LESENSE_IRQn);

}

/**************************************************************************//**
 * @brief  Sets up the GPIO
 *****************************************************************************/
void CapSenseClass::setupGPIO( void )
{
  unsigned int i;
  
  /* Set GPIO pin mode to disabled for all active pins */
  for(i = 0; i < NUM_LESENSE_CHANNELS; i++){
    if((myChannelsUsedMask >> i) & 0x1){
      GPIO_PinModeSet(LESENSE_CH_PORT, i, gpioModeDisabled, 0);
    }
  }
}

uint16_t CapSenseClass::scanSingleChannel(uint16_t channelToScan)
{
   int i,k;
   
   /* Wait for current scan to finish */
  while(LESENSE->STATUS & LESENSE_STATUS_SCANACTIVE); 
  
  /* Get position for first channel data in count buffer from lesense write pointer */
  k = ((LESENSE->PTR & _LESENSE_PTR_WR_MASK) >> _LESENSE_PTR_WR_SHIFT);
  
  /* Handle circular buffer wraparound */
  if(k >= myNumChannelsUsed){
    k = k - myNumChannelsUsed;
  }
  else{
    k = k - myNumChannelsUsed + NUM_LESENSE_CHANNELS;
  }
  
  /* Fill calibration values array with buffer values */
  for(i = 0; i < NUM_LESENSE_CHANNELS; i++){
    if((myChannelsUsedMask >> i) & 0x1){
      if(i == channelToScan)
      {
          uint16_t value = LESENSE_ScanResultDataBufferGet(k++);
          return value;
      }
      else
      {
          k++;
      }
    }
  }
  
  return 0;
}


/**************************************************************************//**
 * Calibration function 
*****************************************************************************/
void CapSenseClass::calibrate( void )
{
  int i,k;
  uint16_t nominal_count;
  static uint8_t calibrationValueIndex = 0;
  
  
  
  /* Wait for current scan to finish */
  while(LESENSE->STATUS & LESENSE_STATUS_SCANACTIVE); 
  
  /* Get position for first channel data in count buffer from lesense write pointer */
  k = ((LESENSE->PTR & _LESENSE_PTR_WR_MASK) >> _LESENSE_PTR_WR_SHIFT);
  
  /* Handle circular buffer wraparound */
  if(k >= myNumChannelsUsed){
    k = k - myNumChannelsUsed;
  }
  else{
    k = k - myNumChannelsUsed + NUM_LESENSE_CHANNELS;
  }
  
  /* Fill calibration values array with buffer values */
  for(i = 0; i < NUM_LESENSE_CHANNELS; i++){
    if((myChannelsUsedMask >> i) & 0x1){
      
      myCalibrationValue[i][calibrationValueIndex] = LESENSE_ScanResultDataBufferGet(k++);
      
    }
  }
 
  /* Wrap around myCalibrationValues_index */
  calibrationValueIndex++;
  if(calibrationValueIndex >= NUMBER_OF_CALIBRATION_VALUES){
    calibrationValueIndex = 0;
  }
  
  /* Calculate max/min-value for each channel and set threshold */
  for(i = 0; i < NUM_LESENSE_CHANNELS; i++){
    if((myChannelsUsedMask >> i) & 0x1){
      myChannelMaxValue[i] = getMaxValue(myCalibrationValue[i], NUMBER_OF_CALIBRATION_VALUES);
      myChannelMinValue[i] = getMinValue(myCalibrationValue[i], NUMBER_OF_CALIBRATION_VALUES);
      
      nominal_count = myChannelMaxValue[i];
      LESENSE_ChannelThresSet(i, 0x0,(uint16_t) (nominal_count - ((nominal_count * myChannelThresholdPercent[i])/100.0)) ); 
    }
  }
}

/**************************************************************************//**
 * Returns maximum value in input array of size N 
*****************************************************************************/
uint16_t CapSenseClass::getMaxValue(volatile uint16_t* A, uint16_t N)
{
  int i;
  uint16_t max = 0;
    
  for(i=0; i<N; i++)
  {
    if(max < A[i]){
      max = A[i];
    }
  } 
  return max;
}

/**************************************************************************//**
 * Returns minimum value in input array of size N 
*****************************************************************************/
uint16_t CapSenseClass::getMinValue(volatile uint16_t* A, uint16_t N)
{
  int i;
  uint16_t min = 0xffff;
    
  for(i=0; i<N; i++)
  {
    if(A[i] < min){
      min = A[i];
    }
  } 
  return min;
}

/**************************************************************************//**
 * Interrupt handlers
 *****************************************************************************/

/**************************************************************************//**
 * @brief LESENSE_IRQHandler
 * Interrupt Service Routine for LESENSE Interrupt Line
 *****************************************************************************/
void LESENSE_IRQHandler( void )
{
  uint8_t channel, i, valid_touch;
  uint32_t interrupt_flags, tmp, channels_enabled;
  uint16_t threshold_value;
  
  /* Get interrupt flag */
  interrupt_flags = LESENSE_IntGet();
  /* Clear interrupt flag */
  LESENSE_IntClear(interrupt_flags);
  
  /* Interrupt handles only one channel at a time */ 
  /* therefore only first active channel found is handled by the interrupt. */
  for(channel = 0; channel < NUM_LESENSE_CHANNELS; channel++){
    if( (interrupt_flags >> channel) & 0x1 ){
      break;
    }
  }
  
  /* To filter out possible false touches, the suspected channel is measured several times */
  /* All samples should be below threshold to trigger an actual touch. */

  /* Disable other channels. */
  channels_enabled = LESENSE->CHEN;
  LESENSE->CHEN = 1 << channel;
  
   /* Evaluate VALIDATE_CNT results for touched channel. */
  valid_touch = 1;
  for(i = 0;i<sValidateCnt;i++){
    /* Start new scan and wait while active. */
    LESENSE_ScanStart();
    while(LESENSE->STATUS & LESENSE_STATUS_SCANACTIVE);
    
    tmp = LESENSE->SCANRES;
    if((tmp & (1 << channel)) == 0){
      valid_touch = 0;
    }
  }  
    
  /* Enable all channels again. */
  LESENSE->CHEN = channels_enabled;
  
  uint16_t buttonsPressed = CapSense.channelsState();
  if(valid_touch){
    /* If logic was switched clear button flag and set logic back, else set button flag and invert logic. */
    if(LESENSE->CH[channel].EVAL & LESENSE_CH_EVAL_COMP){
      buttonsPressed &= ~(1 << channel);
      LESENSE->CH[channel].EVAL &= ~LESENSE_CH_EVAL_COMP;
      
      threshold_value = LESENSE->CH[channel].EVAL & (_LESENSE_CH_EVAL_COMPTHRES_MASK);
      /* Change threshold value 1 LSB for hysteresis. */
      threshold_value -= 1;
      LESENSE_ChannelThresSet(channel, 0, threshold_value);
    }
    else{
      buttonsPressed |= (1 << channel);
      LESENSE->CH[channel].EVAL |= LESENSE_CH_EVAL_COMP;
      
      threshold_value = LESENSE->CH[channel].EVAL & (_LESENSE_CH_EVAL_COMPTHRES_MASK);
      /* Change threshold value 1 LSB for hysteresis. */
      threshold_value += 1;
      LESENSE_ChannelThresSet(channel, 0, threshold_value);
    }
  }
  CapSense.updateChannelsState(buttonsPressed);
  /* Need to reset RTC counter so we don't get new calibration event right after buttons are pushed/released. */
  //RTC_CounterReset();
  
}

CapSenseClass CapSense = CapSenseClass();
#endif
