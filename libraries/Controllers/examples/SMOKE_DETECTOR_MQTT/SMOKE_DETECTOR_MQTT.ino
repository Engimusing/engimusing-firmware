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
/* Example for how to setup the MQTT client for the Smoke Detector Controller Engimusing board
 *  This board is intended to be connected up to a smoke detector to allow for remote
 *  alarm detection and testing. 
 *  See ADD LINK HERE WHEN IT IS EXISTS for more 
 *  information about the board.
 */

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif
 
//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <OnOffCtrlDevice.h>
#include <TMP102Device.h>
#include <Wire.h>

extern INTRClass INTR;

/*
  SMOKE Commands:
  {"TOP":"SMOKE/BOARD/PWMPIN/CTL","PLD":"ON"}
  {"TOP":"SMOKE/BOARD/PWMPIN/CTL","PLD":"OFF"}
  {"TOP":"SMOKE/BOARD/PWMPIN/CTL","PLD":"STATUS"}
  
  {"TOP":"SMOKE/BOARD/TESTSWITCH/CTL","PLD":"ON"}
  {"TOP":"SMOKE/BOARD/TESTSWITCH/CTL","PLD":"OFF"}
  {"TOP":"SMOKE/BOARD/TESTSWITCH/CTL","PLD":"STATUS"}
  
  {"TOP":"SMOKE/BOARD/PGOODPIN","PLD":"STATUS"}
  {"TOP":"SMOKE/BOARD/IOPIN","PLD":"STATUS"}
  {"TOP":"SMOKE/BOARD/SmokeLEDPin","PLD":"STATUS"}
  
  {"TOP":"SMOKE/BOARD/AUTOTEST","PLD":"START"}

  {"TOP":"SMOKE/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"SMOKE/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"SMOKE/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"SMOKE/BOARD/TMP102/CTL","PLD":"STATUS"}
  
  SMOKE Responses
  Sent when smoke is actually detected
  {"TOP":"SMOKE/BOARD/ALERT","PLD":"SMOKEDETECTED"}

  Results of the auto test
  
  {"TOP":"SMOKE/BOARD/TESTRESULT/CODE","PLD":"0"} Passed
  {"TOP":"SMOKE/BOARD/TESTRESULT/CODE","PLD":"1"} IO early low
  {"TOP":"SMOKE/BOARD/TESTRESULT/CODE","PLD":"2"} IO never high
  {"TOP":"SMOKE/BOARD/TESTRESULT/CODE","PLD":"3"} IO low timeout 

  # is between 0 and about 12 should be between 9-12 if the detector is working correctly
  {"TOP":"SMOKE/BOARD/TESTRESULT/LEDCOUNT","PLD":"#"} 

  Time in milliseconds the IO pin was on during the test. 
  Should be between 8000-11000 
  {"TOP":"SMOKE/BOARD/TESTRESULT/IOHIGHTIME","PLD":"#"}
  
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class definitions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtrlDevice TestSwitchDevice;
SimpleMqttModule TestSwitchMod;

//monitor the monitor lines to know the state of sensors attached to the MON wires
DetectorSwitchModule IoPinMod;
DetectorSwitchModule SmokeLEDPinMod;

NotificationModule AutoTestEvent;

TMP102Device TMP102;
SimpleMqttModule TMP102MqttMod;

OnOffCtlModule LEDCtrl;

enum AutoTestState
{
  TEST_IDLE = 0,
  TEST_RUNNING = 1,
  TEST_FINAL_CHECK = 2
};

AutoTestState autoTestState;
uint32_t autoTestStartTime;
int32_t ioPinHighTime;
uint8_t ledToggleCount;

enum TestResults
{
    TEST_PASSED,
    TEST_FAILED_EARLY_IO_LOW,
    TEST_FAILED_IO_NEVER_HIGH,
    TEST_FAILED_IO_LOW_CHECK_TIMEOUT
};
uint32_t testResultCode;

uint32_t lastAlert;

uint32_t SmokeLEDPin = 8;
uint32_t ControllerLEDPin = 12;
uint32_t BDINPin = 2;
uint32_t BEN1Pin = 3;
uint32_t BEN2Pin = 11;

void setup()
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  TestSwitchDevice.begin(4, false, LOW);
  TestSwitchMod.begin(HUB, TestSwitchDevice, "SMOKE/BOARD/TESTSWITCH", 100000);
  
  IoPinMod.begin(HUB, 5, "SMOKE/BOARD/IOPIN", 10, 10);
  SmokeLEDPinMod.begin(HUB, SmokeLEDPin, "SMOKE/BOARD/SmokeLEDPin", 1, 0);

  TMP102.begin(Wire1, 0, true);
  TMP102MqttMod.begin(HUB, TMP102, "SMOKE/BOARD/TMP102", 1000);

  LEDCtrl.begin(HUB, ControllerLEDPin, "SMOKE/BOARD/LED", HIGH);
  
  AutoTestEvent.begin(HUB, "SMOKE/BOARD", "AUTOTEST", "START");
  autoTestState = TEST_IDLE;
  autoTestStartTime = 0;

  //initialize the piezo driver pins.
  pinMode(BDINPin, OUTPUT);
  digitalWrite(BDINPin, LOW); 
  pinMode(BEN1Pin, OUTPUT);
  digitalWrite(BEN1Pin, LOW); 
  pinMode(BEN2Pin, OUTPUT);
  digitalWrite(BEN2Pin, LOW); 
  
  lastAlert = 0;
}

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and receive requests
  HUB.update();
  
  if(AutoTestEvent.getState())
  {

/* Working piezo driver code.
    //turn on the piezo driver to the 1x voltage level.
    digitalWrite(BEN1Pin, LOW); 
    digitalWrite(BEN2Pin, HIGH);
   
    int start = millis(); 
    int i = 0;

    //toggle the DIN pin to set the tone
    // Run for 10 seconds.
    while(millis() < start + 10000)
    {
      digitalWrite(BDINPin, HIGH);
      delayMicroseconds(200); // 2.5Khz frequency
      digitalWrite(BDINPin, LOW); 
      delayMicroseconds(200);
      i++;
    }
    
    digitalWrite(BEN1Pin, LOW); 
    digitalWrite(BEN2Pin, LOW); 
 */   
/* This didn't seem to work for whatever reason. It requires the pitches.h header file to compile.
 *  See toneMelody example.
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    //tone(2, melody[thisNote],noteDuration);
    tone(BDINPin, 10, 5000);//noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = 5000;//noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BDINPin);
  }
    digitalWrite(BEN1Pin, LOW); 
    digitalWrite(BEN2Pin, LOW); 
    
  */
    //Setup the auto test
    autoTestState = TEST_RUNNING;
    TestSwitchDevice.setState(HIGH);
    autoTestStartTime = millis();
    INTR.attachIntrCounter(SmokeLEDPin, RISING);
    INTR.read_clr_nints(SmokeLEDPin); // clear the counter
    ioPinHighTime = -1;
    testResultCode = TEST_FAILED_IO_NEVER_HIGH;
  }

  if(autoTestState == TEST_IDLE)
  {
    if(!IoPinMod.switchState() && lastAlert + 1000 < millis())
    {
      lastAlert = millis();
      HUB.sendMessage("SMOKE/BOARD", "ALERT", "SMOKEDETECTED");
    }
  }

  if(autoTestState == TEST_RUNNING)
  {
    if(!IoPinMod.switchState() && ioPinHighTime < 0)
    {
        ioPinHighTime = millis();
        testResultCode = TEST_PASSED;
    }
    else if(IoPinMod.switchState())
    {
        testResultCode = TEST_FAILED_EARLY_IO_LOW;
    }
       
    if(autoTestStartTime + 10000 < millis())
    {
      ledToggleCount = INTR.read_clr_nints(SmokeLEDPin);       
      TestSwitchDevice.setState(LOW);
      autoTestState = TEST_FINAL_CHECK;
    }
  }
  
  if(autoTestState == TEST_FINAL_CHECK)
  {
    if(IoPinMod.switchState())
    {
        autoTestState = TEST_IDLE;
    }
    else if(autoTestStartTime + 11000 < millis())
    {
        testResultCode = TEST_FAILED_IO_LOW_CHECK_TIMEOUT;
    }
    
    if(autoTestState == TEST_IDLE)
    {
        HUB.sendMessage("SMOKE/BOARD/TESTRESULT", "CODE", testResultCode);
        HUB.sendMessage("SMOKE/BOARD/TESTRESULT", "LEDCOUNT", ledToggleCount);
        HUB.sendMessage("SMOKE/BOARD/TESTRESULT", "IOHIGHTIME", millis() - ioPinHighTime);
    }
    
  }

  
  
}
