/*
  Arduino Library for Analog Devices ADXL362 - Micropower 3-axis accelerometer
  go to http://www.analog.com/ADXL362 for datasheet
 
 
  License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
  to use and abuse this code however you'd like. If you find it useful
  please attribute, and SHARE-ALIKE!
 
  Created June 2012
  by Anne Mahaffey - hosted on http://annem.github.com/ADXL362
 
*/ 

#include <Arduino.h>
#include <ADXL362.h>


const bool debugSerial = 0;


ADXL362::ADXL362() {

}

//
//  begin()
//  Initial SPI setup, soft reset of device
//
void ADXL362::begin(int vddPin, int vsPin, int ssPin, SPIClass *ADXL_SPI) {

  slaveSelectPin = ssPin;
  pinMode(vddPin, OUTPUT);
  pinMode(vsPin, OUTPUT);

  //power cycle the ADXL
   digitalWrite(vddPin, LOW);
   digitalWrite(vsPin, LOW);
   delay(1000);
  
  
  
  digitalWrite(vddPin, HIGH);
  digitalWrite(vsPin, HIGH);
  
  _ADXL_SPI = ADXL_SPI;
  
  pinMode(slaveSelectPin, OUTPUT);
  _ADXL_SPI->begin();
  _ADXL_SPI->setDataMode(SPI_MODE0);	//CPHA = CPOL = 0    MODE = 0
  delay(1000);
    
  // soft reset
  SPIwriteOneRegister(0x1F, 0x52);  // Write to SOFT RESET, "R"
  delay(10);
  //  Serial.println("\n\rSoft Reset\n\r");
}

 
//
//  beginMeasure()
//  turn on Measurement mode - required after reset
// 
void ADXL362::beginMeasure() {
  byte temp = SPIreadOneRegister(0x2D);	// read Reg 2D before modifying for measure mode
  if (debugSerial) {Serial.print(  "Setting Measeurement Mode - Reg 2D before = "); Serial.print(temp); }

  // turn on measurement mode
  byte tempwrite = temp | 0x02;			// turn on measurement bit in Reg 2D
  SPIwriteOneRegister(0x2D, tempwrite); // Write to POWER_CTL_REG, Measurement Mode
  delay(10);	
  
  if (debugSerial) {
    temp = SPIreadOneRegister(0x2D);
    Serial.print(  ", Reg 2D after = "); Serial.println(temp); Serial.println();}
}


//
//  readXData(), readYData(), readZData(), readTemp()
//  Read X, Y, Z, and Temp registers
//
int ADXL362::readXData(){
  int XDATA = SPIreadTwoRegisters(0x0E);
  if (debugSerial) {Serial.print(  "XDATA = "); Serial.print(XDATA); }
}

int ADXL362::readYData(){
  int YDATA = SPIreadTwoRegisters(0x10);
  if (debugSerial) {Serial.print(  "\tYDATA = "); Serial.print(YDATA); }

}

int ADXL362::readZData(){
  int ZDATA = SPIreadTwoRegisters(0x12);
  if (debugSerial) {Serial.print(  "\tZDATA = "); Serial.print(ZDATA); }

}

int ADXL362::readTemp(){
  int TEMP = SPIreadTwoRegisters(0x14);
  if (debugSerial) {Serial.print("\tTEMP = "); Serial.print(TEMP); }
}

int sampleX, sampleY, sampleZ, sampleT;

void ADXL362::sampleXYZT(void) {
  // burst SPI read
  // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(0x0E);  // Start at XData Reg
  sampleX = _ADXL_SPI->transfer(0x00);
  sampleX = sampleX + (_ADXL_SPI->transfer(0x00) << 8);
  sampleY = _ADXL_SPI->transfer(0x00);
  sampleY = sampleY + (_ADXL_SPI->transfer(0x00) << 8);
  sampleZ = _ADXL_SPI->transfer(0x00);
  sampleZ = sampleZ + (_ADXL_SPI->transfer(0x00) << 8);
  sampleT = _ADXL_SPI->transfer(0x00);
  sampleT = sampleT + (_ADXL_SPI->transfer(0x00) << 8);
  digitalWrite(slaveSelectPin, HIGH);
}

int ADXL362::get_sampleX(void) {
  return sampleX;
}

int ADXL362::get_sampleY(void) {
  return sampleY;
}

int ADXL362::get_sampleZ(void) {
  return sampleZ;
}

int ADXL362::get_sampleT(void) {
  return sampleT;
}


void ADXL362::readXYZTData(int XData, int YData, int ZData, int Temperature){
  
  // burst SPI read
  // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(0x0E);  // Start at XData Reg
  XData = _ADXL_SPI->transfer(0x00);
  XData = XData + (_ADXL_SPI->transfer(0x00) << 8);
  YData = _ADXL_SPI->transfer(0x00);
  YData = YData + (_ADXL_SPI->transfer(0x00) << 8);
  ZData = _ADXL_SPI->transfer(0x00);
  ZData = ZData + (_ADXL_SPI->transfer(0x00) << 8);
  Temperature = _ADXL_SPI->transfer(0x00);
  Temperature = Temperature + (_ADXL_SPI->transfer(0x00) << 8);
  digitalWrite(slaveSelectPin, HIGH);

  if (debugSerial) {
    Serial.print("X = ");
    Serial.print((int16_t)XData,DEC);
    Serial.print(" Y = ");
    Serial.print((int16_t)YData,DEC);
    Serial.print(" Z = ");
    Serial.print((int16_t)ZData,DEC);
    Serial.print(" T = ");
    Serial.println((int16_t)Temperature,DEC);
  }

}


void ADXL362::readHAB_XYZTData(void) {
  
int XData, YData, ZData, Temperature;

  // burst SPI read
  // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
  digitalWrite(slaveSelectPin, LOW);

  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(0x0E);  // Start at XData Reg
  XData = _ADXL_SPI->transfer(0x00);
  XData = XData + (_ADXL_SPI->transfer(0x00) << 8);
  YData = _ADXL_SPI->transfer(0x00);
  YData = YData + (_ADXL_SPI->transfer(0x00) << 8);
  ZData = _ADXL_SPI->transfer(0x00);
  ZData = ZData + (_ADXL_SPI->transfer(0x00) << 8);
  Temperature = _ADXL_SPI->transfer(0x00);
  Temperature = Temperature + (_ADXL_SPI->transfer(0x00) << 8);

  Serial.print("ADXL362;");
  Serial.print((int16_t)XData,DEC);
  Serial.print(";");
  Serial.print((int16_t)YData,DEC);
  Serial.print(";");
  Serial.print((int16_t)ZData,DEC);
  Serial.print(";");
  Serial.print((int16_t)Temperature,DEC);
  Serial.println(";");

  digitalWrite(slaveSelectPin, HIGH);
}


void ADXL362::setupDCActivityInterrupt(int threshold, byte time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x20, threshold);
  SPIwriteOneRegister(0x22, time);

  // turn on activity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x01);     // turn on bit 1, ACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written

  if (debugSerial) {
    Serial.print("DC Activity Threshold set to ");  	Serial.print(SPIreadTwoRegisters(0x20));
    Serial.print(", Time threshold set to ");  		Serial.print(SPIreadOneRegister(0x22)); 
    Serial.print(", ACT_INACT_CTL Register is ");  	Serial.println(ACT_INACT_CTL_Reg, HEX);
  }
}

void ADXL362::setupACActivityInterrupt(int threshold, byte time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x20, threshold);
  SPIwriteOneRegister(0x22, time);
  
  // turn on activity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);  // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x03);     // turn on bit 2 and 1, ACT_AC_DCB, ACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);       // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);       // Verify properly written

  if (debugSerial) {  
    Serial.print("AC Activity Threshold set to ");  	Serial.print(SPIreadTwoRegisters(0x20));
    Serial.print(", Time Activity set to ");  		Serial.print(SPIreadOneRegister(0x22));  
    Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
  }
}

void ADXL362::setupDCInactivityInterrupt(int threshold, int time){
  // Setup motion and time thresholds
  SPIwriteTwoRegisters(0x23, threshold);
  SPIwriteTwoRegisters(0x25, time);

  // turn on inactivity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value 
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x04);      // turn on bit 3, INACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written

  if (debugSerial) {
    Serial.print("DC Inactivity Threshold set to ");  Serial.print(SPIreadTwoRegisters(0x23));
    Serial.print(", Time Inactivity set to ");  Serial.print(SPIreadTwoRegisters(0x25));
    Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
  }
}


void ADXL362::setupACInactivityInterrupt(int threshold, int time){
  //  Setup motion and time thresholds
  SPIwriteTwoRegisters(0x23, threshold);
  SPIwriteTwoRegisters(0x25, time);
 
  // turn on inactivity interrupt
  byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);   // Read current reg value
  ACT_INACT_CTL_Reg = ACT_INACT_CTL_Reg | (0x0C);      // turn on bit 3 and 4, INACT_AC_DCB, INACT_EN  
  SPIwriteOneRegister(0x27, ACT_INACT_CTL_Reg);        // Write new reg value 
  ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);        // Verify properly written

  if (debugSerial) {
    Serial.print("AC Inactivity Threshold set to ");  Serial.print(SPIreadTwoRegisters(0x23));
    Serial.print(", Time Inactivity set to ");  Serial.print(SPIreadTwoRegisters(0x25)); 
    Serial.print(", ACT_INACT_CTL Register is ");  Serial.println(ACT_INACT_CTL_Reg, HEX);
  }
}


void ADXL362::checkAllControlRegs(){
  //byte filterCntlReg = SPIreadOneRegister(0x2C);
  //byte ODR = filterCntlReg & 0x07;  Serial.print("ODR = ");  Serial.println(ODR, HEX);
  //byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);      Serial.print("ACT_INACT_CTL_Reg = "); Serial.println(ACT_INACT_CTL_Reg, HEX);
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(0x20);  // Start burst read at Reg 20
  Serial.println("Start Burst Read of all Control Regs - Library version 6-24-2012:");
  Serial.print("Reg 20 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 21 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 22 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 23 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 24 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 25 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 26 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 27 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 28 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 29 = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 2A = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 2B = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 2C = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 2D = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  Serial.print("Reg 2E = "); 	Serial.println(_ADXL_SPI->transfer(0x00), HEX);
  
  digitalWrite(slaveSelectPin, HIGH);
}



// Basic SPI routines to simplify code
// read and write one register

byte ADXL362::SPIreadOneRegister(byte regAddress){
  byte regValue = 0;
  
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(regAddress);
  regValue = _ADXL_SPI->transfer(0x00);
  digitalWrite(slaveSelectPin, HIGH);

  return regValue;
}

void ADXL362::SPIwriteOneRegister(byte regAddress, byte regValue){
  
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0A);  // write instruction
  _ADXL_SPI->transfer(regAddress);
  _ADXL_SPI->transfer(regValue);
  digitalWrite(slaveSelectPin, HIGH);
}

int ADXL362::SPIreadTwoRegisters(byte regAddress){
  int twoRegValue = 0;
  
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0B);  // read instruction
  _ADXL_SPI->transfer(regAddress);  
  twoRegValue = _ADXL_SPI->transfer(0x00);
  twoRegValue = twoRegValue + (_ADXL_SPI->transfer(0x00) << 8);
  digitalWrite(slaveSelectPin, HIGH);

  return twoRegValue;
}

void ADXL362::SPIwriteTwoRegisters(byte regAddress, int twoRegValue){
  
  byte twoRegValueH = twoRegValue >> 8;
  byte twoRegValueL = twoRegValue;
  
  digitalWrite(slaveSelectPin, LOW);
  _ADXL_SPI->transfer(0x0A);  // write instruction
  _ADXL_SPI->transfer(regAddress);  
  _ADXL_SPI->transfer(twoRegValueL);
  _ADXL_SPI->transfer(twoRegValueH);
  digitalWrite(slaveSelectPin, HIGH);
}
