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
/* 
  Based on code
  by Anne Mahaffey - hosted on http://annem.github.com/ADXL362
*/

#include <ADXL362Device.h>
#include <Arduino.h>

#if SPI_INTERFACES_COUNT > 0

#include <SPI.h>

void ADXL362Device::begin(int vddPin, int vsPin, int ssPin, SPIClass *adxlSpi, UARTClass *debugSerial)
{    
    myDebugSerial = debugSerial;

    mySlaveSelectPin = ssPin;
    pinMode(vddPin, OUTPUT);
    pinMode(vsPin, OUTPUT);

    //power cycle the ADXL
    digitalWrite(vddPin, LOW);
    digitalWrite(vsPin, LOW);
    delay(1000);

    digitalWrite(vddPin, HIGH);
    digitalWrite(vsPin, HIGH);

    mySpi = adxlSpi;

    pinMode(mySlaveSelectPin, OUTPUT);
    mySpi->begin();
    mySpi->setDataMode(SPI_MODE0);	//CPHA = CPOL = 0    MODE = 0
    delay(1000);

    // soft reset
    SPIwriteOneRegister(0x1F, 0x52);  // Write to SOFT RESET, "R"
    delay(10);
    
    //give the slave a slight delay so it can turn on.
    delay(500);
    int x = SPIreadTwoRegisters(0);
    beginMeasure();                      // DO LAST! enable measurement mode   
    delay(100);
}

//
//  beginMeasure()
//  turn on Measurement mode - required after reset
// 
void ADXL362Device::beginMeasure() {
  byte temp = SPIreadOneRegister(0x2D);	// read Reg 2D before modifying for measure mode
  if (myDebugSerial) {myDebugSerial->print(  "Setting Measeurement Mode - Reg 2D before = "); myDebugSerial->print(temp); }

  // turn on measurement mode
  byte tempwrite = temp | 0x02;			// turn on measurement bit in Reg 2D
  SPIwriteOneRegister(0x2D, tempwrite); // Write to POWER_CTL_REG, Measurement Mode
  delay(10);	
  
  if (myDebugSerial) {
    temp = SPIreadOneRegister(0x2D);
    myDebugSerial->print(  ", Reg 2D after = "); myDebugSerial->println(temp); myDebugSerial->println();}
}


//
//  readXData(), readYData(), readZData(), readTemp()
//  Read X, Y, Z, and Temp registers
//
int ADXL362Device::readXData(){
  int XDATA = SPIreadTwoRegisters(0x0E);
  if (myDebugSerial) {myDebugSerial->print(  "XDATA = "); myDebugSerial->print(XDATA); }
}

int ADXL362Device::readYData(){
  int YDATA = SPIreadTwoRegisters(0x10);
  if (myDebugSerial) {myDebugSerial->print(  "\tYDATA = "); myDebugSerial->print(YDATA); }

}

int ADXL362Device::readZData(){
  int ZDATA = SPIreadTwoRegisters(0x12);
  if (myDebugSerial) {myDebugSerial->print(  "\tZDATA = "); myDebugSerial->print(ZDATA); }

}

int ADXL362Device::readTemp(){
  int TEMP = SPIreadTwoRegisters(0x14);
  if (myDebugSerial) {myDebugSerial->print("\tTEMP = "); myDebugSerial->print(TEMP); }
}

void ADXL362Device::sampleXYZT(void) {
  // burst SPI read
  // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
  digitalWrite(mySlaveSelectPin, LOW);
  mySpi->transfer(0x0B);  // read instruction
  mySpi->transfer(0x0E);  // Start at XData Reg
  mySampleX = mySpi->transfer(0x00);
  mySampleX = mySampleX + (mySpi->transfer(0x00) << 8);
  mySampleY = mySpi->transfer(0x00);
  mySampleY = mySampleY + (mySpi->transfer(0x00) << 8);
  mySampleZ = mySpi->transfer(0x00);
  mySampleZ = mySampleZ + (mySpi->transfer(0x00) << 8);
  mySampleT = mySpi->transfer(0x00);
  mySampleT = mySampleT + (mySpi->transfer(0x00) << 8);
  digitalWrite(mySlaveSelectPin, HIGH);
}

int ADXL362Device::getSampleX(void) {
  return mySampleX;
}

int ADXL362Device::getSampleY(void) {
  return mySampleY;
}

int ADXL362Device::getSampleZ(void) {
  return mySampleZ;
}

int ADXL362Device::getSampleT(void) {
  return mySampleT;
}


void ADXL362Device::readXYZTData(int &xData, int &yData, int &zData, int &temperature){
  
  // burst SPI read
  // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
  sampleXYZT();
  xData = getSampleX();
  yData = getSampleY();
  zData = getSampleZ();
  temperature = getSampleT();
  if (myDebugSerial) {
    myDebugSerial->print("X = ");
    myDebugSerial->print((int16_t)xData,DEC);
    myDebugSerial->print(" Y = ");
    myDebugSerial->print((int16_t)yData,DEC);
    myDebugSerial->print(" Z = ");
    myDebugSerial->print((int16_t)zData,DEC);
    myDebugSerial->print(" T = ");
    myDebugSerial->println((int16_t)temperature,DEC);
  }

}

void ADXL362Device::setupDCActivityInterrupt(int threshold, byte time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x20, threshold);
  SPIwriteOneRegister(0x22, time);

  // turn on activity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x01);     // turn on bit 1, ACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written

  if (myDebugSerial) {
    myDebugSerial->print("DC Activity Threshold set to ");  	myDebugSerial->print(SPIreadTwoRegisters(0x20));
    myDebugSerial->print(", Time threshold set to ");  		myDebugSerial->print(SPIreadOneRegister(0x22)); 
    myDebugSerial->print(", ACT_INACT_CTL Register is ");  	myDebugSerial->println(ACT_INACT_CTL_Reg, HEX);
  }
}

void ADXL362Device::setupACActivityInterrupt(int threshold, byte time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x20, threshold);
  SPIwriteOneRegister(0x22, time);
  
  // turn on activity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x03);     // turn on bit 2 and 1, ACT_AC_DCB, ACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written

  if (myDebugSerial) {  
    myDebugSerial->print("AC Activity Threshold set to ");  	myDebugSerial->print(SPIreadTwoRegisters(0x20));
    myDebugSerial->print(", Time Activity set to ");  		myDebugSerial->print(SPIreadOneRegister(0x22));  
    myDebugSerial->print(", ACT_INACT_CTL Register is ");  myDebugSerial->println(ACT_INACT_CTL_Reg, HEX);
  }
}

void ADXL362Device::setupDCInactivityInterrupt(int threshold, int time){
  // Setup motion and time thresholds
  SPIwriteTwoRegisters(0x23, threshold);
  SPIwriteTwoRegisters(0x25, time);

  // turn on inactivity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value 
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x04);      // turn on bit 3, INACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written

  if (myDebugSerial) {
    myDebugSerial->print("DC Inactivity Threshold set to ");  myDebugSerial->print(SPIreadTwoRegisters(0x23));
    myDebugSerial->print(", Time Inactivity set to ");  myDebugSerial->print(SPIreadTwoRegisters(0x25));
    myDebugSerial->print(", ACT_INACT_CTL Register is ");  myDebugSerial->println(ACT_INACT_CTL_Reg, HEX);
  }
}


void ADXL362Device::setupACInactivityInterrupt(int threshold, int time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x23, threshold);
  SPIwriteTwoRegisters(0x25, time);
 
  // turn on inactivity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x0C);      // turn on bit 3 and 4, INACT_AC_DCB, INACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written

  if (myDebugSerial) {
    myDebugSerial->print("AC Inactivity Threshold set to ");  myDebugSerial->print(SPIreadTwoRegisters(0x23));
    myDebugSerial->print(", Time Inactivity set to ");  myDebugSerial->print(SPIreadTwoRegisters(0x25)); 
    myDebugSerial->print(", ACT_INACT_CTL Register is ");  myDebugSerial->println(ACT_INACT_CTL_Reg, HEX);
  }
}

// Basic SPI routines to simplify code
// read and write one register

byte ADXL362Device::SPIreadOneRegister(byte regAddress){
  byte regValue = 0;
  
  digitalWrite(mySlaveSelectPin, LOW);
  mySpi->transfer(0x0B);  // read instruction
  mySpi->transfer(regAddress);
  regValue = mySpi->transfer(0x00);
  digitalWrite(mySlaveSelectPin, HIGH);

  return regValue;
}

void ADXL362Device::SPIwriteOneRegister(byte regAddress, byte regValue){
  
  digitalWrite(mySlaveSelectPin, LOW);
  mySpi->transfer(0x0A);  // write instruction
  mySpi->transfer(regAddress);
  mySpi->transfer(regValue);
  digitalWrite(mySlaveSelectPin, HIGH);
}

int ADXL362Device::SPIreadTwoRegisters(byte regAddress){
  int twoRegValue = 0;
  
  digitalWrite(mySlaveSelectPin, LOW);
  mySpi->transfer(0x0B);  // read instruction
  mySpi->transfer(regAddress);  
  twoRegValue = mySpi->transfer(0x00);
  twoRegValue = twoRegValue + (mySpi->transfer(0x00) << 8);
  digitalWrite(mySlaveSelectPin, HIGH);

  return twoRegValue;
}

void ADXL362Device::SPIwriteTwoRegisters(byte regAddress, int twoRegValue){
  
  byte twoRegValueH = twoRegValue >> 8;
  byte twoRegValueL = twoRegValue;
  
  digitalWrite(mySlaveSelectPin, LOW);
  mySpi->transfer(0x0A);  // write instruction
  mySpi->transfer(regAddress);  
  mySpi->transfer(twoRegValueL);
  mySpi->transfer(twoRegValueH);
  digitalWrite(mySlaveSelectPin, HIGH);
}


Device::ValueStruct ADXL362Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        sampleXYZT(); //sample all the values at once when the first value is read.
        output.type = Device::TypeInt;
        output.value.integer = getSampleX();
        output.name = "SAMPLE_X";
    }
    else if(index == 1)
    {
        output.type = Device::TypeInt;
        output.value.integer = getSampleY();
        output.name = "SAMPLE_Y";
    }
    else if(index == 2)
    {
        output.type = Device::TypeInt;
        output.value.integer = getSampleZ();
        output.name = "SAMPLE_Z";
    }
    else if(index == 3)
    {
        output.type = Device::TypeInt;
        output.value.integer = getSampleT();
        output.name = "TEMP";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float ADXL362Device::numValues()
{
    return 4; 
}
#endif

