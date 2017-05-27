/*
  Cap_Sense_Test
  Used for testing the Engimusing Cap Sense board. Links the cap sensors
   to the LEDS and also blinks the A,B,C,D LEDS as well.
 */
#include "CapSenseDevice.h"

#if !defined(EFM32TG222)
#error Incorrect Board Selected! Please select Engimusing EFM32TG222 from the Tools->Board: menu.
#endif

float sensitivity[] = {1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};

CapSenseDevice devices[16];

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin 13 as an output.
  for(int i = 0; i < 16; i++)
  {
    pinMode(ledId[i], OUTPUT);
    digitalWrite(ledId[i], LOW);    // turn the LED off by making the voltage LOW
  }
  delay(2000);

  for(int i = 0; i < 16; i++)
  {
    sensitivity[i] *= 50.0;
  }

  for(int i = 0; i < 16; i++)
  {
    devices[i].begin(i, sensitivity[i]);
  }
  
  devices[0].update();
  
}

int ledIdMap[] = {2, 3, 11, 12, 41, 24, 17, 15, 14, 40, 42, 25};

int i = 0;
int ledBlinkDelay = 1000;
int lastLedBlink = 0;
int lastLed = 10;
// the loop function runs over and over again forever
void loop() {
  int led = 0;
  for(int i = 0; i < 16; i++)
  {
    
    if(sensitivity[i] > 0)
    {
      devices[i].update();
      if(devices[i].state())
      {
        digitalWrite(ledIdMap[led], HIGH);    // turn the LED off by making the voltage LOW       
        
      }
      else
      {
        digitalWrite(ledIdMap[led], LOW);    // turn the LED off by making the voltage LOW
      }
      
      led++;
      
    }
       
  }

  if(lastLedBlink + ledBlinkDelay < millis())
  {
    lastLedBlink = millis();
    // initialize digital pin 13 as an output.
    
    pinMode(ledId[lastLed], OUTPUT);
    digitalWrite(ledId[lastLed], LOW);    // turn the LED off by making the voltage LOW
    lastLed++;
    if(lastLed > 13)
    {
      lastLed = 10;
    }
    pinMode(ledId[lastLed], OUTPUT);
    digitalWrite(ledId[lastLed], HIGH);    // turn the LED off by making the voltage LOW
    
    
  }
}
