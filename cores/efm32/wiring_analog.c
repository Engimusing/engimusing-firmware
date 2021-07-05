/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include "Arduino.h"
#include "variant.h"
#include "em_adc.h"

#include "em_dac.h"
#include "em_vdac.h"

#include "em_timer.h"
#include "em_cmu.h"
#include "pins_arduino.h"
#include "em_emu.h"
#include "efm_lib/efm_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

  static int _readResolution = 10;
  static int _writeResolution = 8;

  void analogReadResolution(int res) {
    _readResolution = res;
  }

  void analogWriteResolution(int res) {
    _writeResolution = res;
  }

  static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
    if (from == to)
      return value;
    if (from > to)
      return value + ( 1 << (from-to - 1)) >> (from-to);
    else
      {
	uint32_t mappedVal = value << (to-from);
	if(mappedVal != 0)
	  {
	    //make it so max value of from = max value of to 
	    // also maintain that 0 == 0
	    // probably not the best best way to do this but it does make 0 and max value both work
	    mappedVal |= ((1 << (to-from)) - 1);
	  }
	return mappedVal;
		
      }
  }

  eAnalogReference analog_reference = AR_DEFAULT;

  void analogReference(eAnalogReference ulMode)
  {
    analog_reference = ulMode;
  }


  uint32_t analogInit(void)
  {
#if defined(ADC_COUNT)
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_ADC0, true);
    /* Base the ADC configuration on the default setup. */
    ADC_Init_TypeDef       init  = ADC_INIT_DEFAULT;

    /* Initialize timebases */
    init.timebase = ADC_TimebaseCalc(0);
    init.prescale = ADC_PrescaleCalc(400000, 0);
	
    ADC_Init(ADC0, &init);
#endif
	
  }

  //**************************************************************************
  // * @brief ADC0 interrupt handler. Simply clears interrupt flag.
  // *************************************************************************


  uint32_t analogRead(uint32_t ulPin)
  {
#if defined(ADC_COUNT)
    uint32_t ulValue = 0;
#if defined(_ADC_SINGLECTRL_INPUTSEL_MASK)
    ADC_SingleInput_TypeDef ulChannel;
#elif defined(_ADC_SINGLECTRL_POSSEL_MASK)
	ADC_PosSel_TypeDef ulChannel;
#endif
    static int init = 0;
    if (ulPin < A0)
      ulPin += A0;

    ulChannel = adcChannelNum[ulPin] ;

    if(!init)
      {
	analogInit();
	init = 1;
      }
	
#if defined(_ADC_SINGLECTRL_INPUTSEL_MASK)
    switch ( adcChannel[ulPin] )
      {
	// Handling ADC 12 bits channels
      case EM_ADC0 :
      case EM_ADC1 :
      case EM_ADC2 :
      case EM_ADC3 :
      case EM_ADC4 :
      case EM_ADC5 :
      case EM_ADC6 :
      case EM_ADC7 :
      case EM_ADC8 :
      case EM_ADC9 :
      case EM_ADC10 :
      case EM_ADC11 :
	{
		#endif
	  ADC_InitSingle_TypeDef sInit = ADC_INITSINGLE_DEFAULT;
	
	  sInit.reference = adcRefVDD;
	  //sInit.reference = adcRef2V5;
	  sInit.acqTime   = adcAcqTime32;
	
#if defined(_ADC_SINGLECTRL_INPUTSEL_MASK)
	  sInit.input     = ulChannel;
#endif
	 
#if defined(_ADC_SINGLECTRL_POSSEL_MASK)
	  sInit.posSel = ulChannel;
#endif
	  
	  ADC_InitSingle(ADC0, &sInit);
		
	  /* Start one ADC sample */
	  ADC_IntClear(ADC0, ADC_IF_SINGLE);
	  ADC_Start(ADC0, adcStartSingle);
			
	  while(!(ADC0->STATUS & ADC_STATUS_WARM))		
	    {}
			
			
	  while (!(ADC_IntGet(ADC0) & ADC_IF_SINGLE))
	    {
	      /* Just wait for an interrupt to wake us up (DMA interrupts occur */
	      /* regularly). Thus, we don't need to enable ADC interrupt. */
	      EMU_EnterEM1();
	    }
			
			
	  ulValue = ADC_DataSingleGet(ADC0);
	  ulValue = mapResolution(ulValue, ADC_RESOLUTION, _readResolution);
#if defined(_ADC_SINGLECTRL_INPUTSEL_MASK)
	  break;
	}
	// Compiler could yell because we don't handle DAC pins
      default :
	ulValue=0;
	break;
      }
#endif
    return ulValue;
#endif
  }


  /*
    static void TC_SetCMR_ChannelA(Tc *tc, uint32_t chan, uint32_t v)
    {
    tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xFFF0FFFF) | v;
    }

    static void TC_SetCMR_ChannelB(Tc *tc, uint32_t chan, uint32_t v)
    {
    tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xF0FFFFFF) | v;
    }
  */
  static uint8_t PWMEnabled = 0;
  static uint8_t pinEnabled[PINS_COUNT];
  static uint8_t TCChanEnabled[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  void analogOutputInit(void) {
    uint8_t i;
    for (i=0; i<PINS_COUNT; i++)
      pinEnabled[i] = 0;
  }

  // Right now, PWM output only works on the pins with
  // hardware support.  These are defined in the appropriate
  // pins_*.c file.  For the rest of the pins, we default
  // to digital output.
  void analogWrite(uint32_t ulPin, uint32_t ulValue) {

    //uint32_t attr = g_APinDescription[ulPin].ulPinAttribute;

    
		
#if defined(EFM32TG) || defined(EFM32WG840)

if (adcChannel[ulPin] != NO_ADC) {
      EAnalogChannel channel = adcChannel[ulPin];
      if (channel == EM_DAC0 || channel == EM_DAC1) {
			
			
	uint32_t chDACC = ((channel == EM_DAC0) ? 0 : 1);
	uint32_t *chDACDATA = ((channel == EM_DAC0) ? &DAC0->CH0DATA : &DAC0->CH1DATA);
			
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_DAC0, true);
		
		
	DAC0->BIASPROG = 0x0;

	//DAC_Enable(DAC0, 0, true);
	//DAC_Enable(DAC0, 1, true);

	DAC_Init_TypeDef init = DAC_INIT_DEFAULT;

	init.refresh      = dacRefresh8;
	//init.reference    = dacRef2V5;
	init.reference    = dacRefVDD;
	init.outMode      = dacOutputPinADC;
	//init.outMode      = dacOutputDisable;

	//init.convMode     = dacConvModeSampleHold;
	init.convMode     = dacConvModeContinuous;
	init.prescale     = 0x0;

	//init.prescale     = 0x0;
	init.ch0ResetPre  = 0;
	init.outEnablePRS = 0;
	init.sineEnable   = 0;
	init.diff         = 0;

	DAC_Init(DAC0, &init);

	DAC_InitChannel_TypeDef initChannel = DAC_INITCHANNEL_DEFAULT;
	initChannel.refreshEnable = true;
	initChannel.enable = true;
	initChannel.prsEnable = false;
	DAC_InitChannel(DAC0, &initChannel, chDACC);

	//DAC_Enable(DAC0, chDACC, true);
	
	
	*chDACDATA = mapResolution(ulValue, _writeResolution, DACC_RESOLUTION);
	return;
      }
	  }
#else if defined(EFM32GG12B110F1024GQ64)
	
		//Currently only support 1 VDAC channel. There are two available. 
		//The OPA[0], VDAC0, and a few other 0s below would need to change to support dual dacs
		OPAMP_OutMode_TypeDef channel = vdacChannelNum[ulPin];
		if (channel != 0) 
		{
			//CMU_ClockEnable(cmuClock_HFPER, true);
			CMU_ClockEnable(cmuClock_VDAC0, true);


			VDAC_Init_TypeDef init = VDAC_INIT_DEFAULT;

			
			// Set reference to internal 2.5V low noise reference
			init.reference = vdacRef2V5;
  
			init.asyncClockMode = true;
		    // Calculate the VDAC clock prescaler value resulting in a 1 MHz VDAC clock
			init.prescaler = VDAC_PrescaleCalc(1000000, false, 0);

			VDAC_Init(VDAC0, &init);

			VDAC_InitChannel_TypeDef initChannel = VDAC_INITCHANNEL_DEFAULT;

			initChannel.enable = true;
		
			
			VDAC_InitChannel(VDAC0, &initChannel, 0);

						
			VDAC0->OPA[0].OUT &= ~(VDAC_OPA_OUT_MAINOUTEN | VDAC_OPA_OUT_ALTOUTEN);

			VDAC0->OPA[0].OUT |= VDAC_OPA_OUT_APORTOUTEN + channel;

			
		    // Enable DAC channel 0. See readme.txt or Datasheet for VDAC0_OUT0 pin location.
			//if((channel == EM_VDAC0))
			{
				VDAC_Enable(VDAC0, 0, true);
			}
			
			/*else
			{
				// Enable DAC channel 0. See readme.txt or Datasheet for VDAC0_OUT0 pin location.
				VDAC_Enable(VDAC0, 1, true);
			}*/
			
			VDAC0->CH0DATA = ulValue;//mapResolution(ulValue, _writeResolution, VDACC_RESOLUTION);
			return;
		}

#endif 
    

#if defined(EFM32WG842) || defined(EFM32WG840) || defined(EFM32G232)

    if (pwmChannel[ulPin] != 0) {

		
      ulValue = mapResolution(ulValue, _writeResolution, PWM_RESOLUTION);

		
      uint32_t chan = pwmChannel[ulPin];
		
		
      if (!PWMEnabled) {
	// PWM Startup code
	CMU_ClockEnable(cmuClock_HFPER, true);
	if(chan < 32)
	  {
	    CMU_ClockEnable(cmuClock_TIMER0, true);
	  }
	else if(chan < 64)
	  {
	    CMU_ClockEnable(cmuClock_TIMER1, true);
	  }
	else if(chan < 96)
	  {
	    CMU_ClockEnable(cmuClock_TIMER2, true);
	  }
	else 
	  {
#if TIMER_COUNT > 3
	    CMU_ClockEnable(cmuClock_TIMER3, true);
#endif
	  }
	//PWMEnabled = 1;
      }
      TIMER_TypeDef *timer = TIMER0;
		
      if(chan < 32)
	{
	  timer = TIMER0;
	}
      else if(chan < 64)
	{
	  timer = TIMER1;
	}else if(chan < 96)
	{
	  timer = TIMER2;
	}
      else 
	{
#if TIMER_COUNT > 3
	  timer = TIMER3;
#endif
			
	}
		
		
      if (!pinEnabled[ulPin]) 
	{
	  // Setup PWM for this pin
	  GPIO_PinModeSet( dPorts[ulPin], dPins[ulPin],
			   gpioModePushPull, 0 );
			
			
	  //setup the CC output for the timer
	  TIMER_InitCC_TypeDef timer_init = TIMER_INITCC_DEFAULT;
	  timer_init.mode = timerCCModePWM;
	  timer_init.cofoa = timerOutputActionSet;
	  timer_init.cmoa = timerOutputActionSet;
	  timer_init.coist = true;
				
	  int value = (1 << PWM_RESOLUTION) - 1;
	  TIMER_TopSet(timer, value);
			
	  // take the pin location from the pin pwm channel and set the route to use it.
	  timer->ROUTE = (timer->ROUTE & ~_TIMER_ROUTE_LOCATION_MASK) | ((chan & 0x7) << _TIMER_ROUTE_LOCATION_SHIFT); 
			
	  //convert to the channel
	  chan = (chan & 0x1F) / 8;
			
	  //enable the channel in the timer
	  timer->ROUTE |= 1 << chan;
			
	  TIMER_CompareBufSet(timer, chan, 1);
	  TIMER_CompareSet(timer, chan, ulValue);
	  TIMER_InitCC(timer, chan, &timer_init);
			
	  TIMER_Init_TypeDef timerInit     = TIMER_INIT_DEFAULT;
	  TIMER_Init(timer, &timerInit);
			
			
	  TIMER_Enable(timer, true);

	  pinEnabled[ulPin] = 1;
			
	}
      //convert to the channel
      chan = (chan & 0x1F) / 8;
      TIMER_CompareSet(timer, chan, ulValue);
      return;
    }
#endif


#if 0
    if ((attr & PIN_ATTR_TIMER) == PIN_ATTR_TIMER) {
      // We use MCLK/2 as clock.
      const uint32_t TC = VARIANT_MCK / 2 / TC_FREQUENCY;

      // Map value to Timer ranges 0..255 => 0..TC
      ulValue = mapResolution(ulValue, _writeResolution, TC_RESOLUTION);
      ulValue = ulValue * TC;
      ulValue = ulValue / TC_MAX_DUTY_CYCLE;

      // Setup Timer for this pin
      ETCChannel channel = g_APinDescription[ulPin].ulTCChannel;
      static const uint32_t channelToChNo[] = { 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2 };
      static const uint32_t channelToAB[]   = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
      static const Tc *channelToTC[] = {
	TC0, TC0, TC0, TC0, TC0, TC0,
	TC1, TC1, TC1, TC1, TC1, TC1,
	TC2, TC2, TC2, TC2, TC2, TC2 };
      static const uint32_t channelToId[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 };
      uint32_t chNo = channelToChNo[channel];
      uint32_t chA  = channelToAB[channel];
      Tc *chTC = channelToTC[channel];
      uint32_t interfaceID = channelToId[channel];

      if (!TCChanEnabled[interfaceID]) {
	pmc_enable_periph_clk(TC_INTERFACE_ID + interfaceID);
	TC_Configure(chTC, chNo,
		     TC_CMR_TCCLKS_TIMER_CLOCK1 |
		     TC_CMR_WAVE |         // Waveform mode
		     TC_CMR_WAVSEL_UP_RC | // Counter running up and reset when equals to RC
		     TC_CMR_EEVT_XC0 |     // Set external events from XC0 (this setup TIOB as output)
		     TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR |
		     TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR);
	TC_SetRC(chTC, chNo, TC);
      }
      if (ulValue == 0) {
	if (chA)
	  TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR);
	else
	  TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR);
      } else {
	if (chA) {
	  TC_SetRA(chTC, chNo, ulValue);
	  TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
	} else {
	  TC_SetRB(chTC, chNo, ulValue);
	  TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET);
	}
      }
      if (!pinEnabled[ulPin]) {
	PIO_Configure(g_APinDescription[ulPin].pPort,
		      g_APinDescription[ulPin].ulPinType,
		      g_APinDescription[ulPin].ulPin,
		      g_APinDescription[ulPin].ulPinConfiguration);
	pinEnabled[ulPin] = 1;
      }
      if (!TCChanEnabled[interfaceID]) {
	TC_Start(chTC, chNo);
	TCChanEnabled[interfaceID] = 1;
      }
      return;
    }

    // Defaults to digital write
    pinMode(ulPin, OUTPUT);
    ulValue = mapResolution(ulValue, _writeResolution, 8);
    if (ulValue < 128)
      digitalWrite(ulPin, LOW);
    else
      digitalWrite(ulPin, HIGH);
#endif
  }

#ifdef __cplusplus
}
#endif
