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
  {"TOP":"SMOKE/BOARD/LEDPIN","PLD":"STATUS"}
  
  {"TOP":"SMOKE/BOARD/AUTOTEST","PLD":"START"}

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
OnOffCtrlDevice PwmPinDevice;
SimpleMqttModule PwmPinMod;
OnOffCtrlDevice TestSwitchDevice;
SimpleMqttModule TestSwitchMod;

//monitor the monitor lines to know the state of sensors attached to the MON wires
DetectorSwitchModule PGoodPinMod;
DetectorSwitchModule IoPinMod;
DetectorSwitchModule LedPinMod;

NotificationModule AutoTestEvent;

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

void setup()
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);

  PwmPinDevice.begin(8, false, HIGH);
  PwmPinMod.begin(HUB, PwmPinDevice, "SMOKE/BOARD/PWMPIN", 100000);
  
  TestSwitchDevice.begin(4, false, LOW);
  TestSwitchMod.begin(HUB, TestSwitchDevice, "SMOKE/BOARD/TESTSWITCH", 100000);
  
  PGoodPinMod.begin(HUB, 7, "SMOKE/BOARD/PGOODPIN", 10);
  IoPinMod.begin(HUB, 5, "SMOKE/BOARD/IOPIN", 10, 10);
  LedPinMod.begin(HUB, 6, "SMOKE/BOARD/LEDPIN", 1, 0);
  
  AutoTestEvent.begin(HUB, "SMOKE/BOARD", "AUTOTEST", "START");

  autoTestState = TEST_IDLE;
  autoTestStartTime = 0;

  lastAlert = 0;
}

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and receive requests
  HUB.update();
  
  if(AutoTestEvent.getState())
  {
    autoTestState = TEST_RUNNING;
    TestSwitchDevice.setState(HIGH);
    autoTestStartTime = millis();
    INTR.attachIntrCounter(6, RISING);
    INTR.read_clr_nints(6); // clear the counter
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
      ledToggleCount = INTR.read_clr_nints(6);       
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
