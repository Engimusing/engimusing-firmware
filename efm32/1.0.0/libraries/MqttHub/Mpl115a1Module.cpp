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
 */

#include "Mpl115a1Module.h"

#if SPI_INTERFACES_COUNT > 0

#include <Arduino.h>


// ------------------------------- Mpl115a1Module -------------------------
void Mpl115a1Module::begin(MqttHub &hub, const char* mod, uint32_t enablePin, uint32_t powerPin, uint32_t csPin, SPIClass &spi, uint32_t updateDelay)
{
  myUpdateDelay = updateDelay;
  myCsPin = csPin;
  
  MqttModule::begin(hub, mod, true);
  

    // initialize the chip select and enable pins
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  
  
   if(powerPin > 0)
  {
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, HIGH);
  }
  
  // set the chip select inactive, select signal is CS LOW
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  
  mySpi = &spi;
  
  mySpi->begin(); 
  
  //give the slave a slight delay so it can turn on.
  delay(100);
}

void Mpl115a1Module::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
	
     sendMQTTTempData();
     sendMQTTPressureData();
	
  }
}

uint8_t Mpl115a1Module::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
        sendMQTTTempData();
        sendMQTTPressureData();
    return 1;
  }
}

void Mpl115a1Module::sendMQTTTempData()
{
    float tempC = calculateTemperatureC();
    
    myHub->sendMessage((const char*)myModule, "DEG_C", tempC);	
}

void Mpl115a1Module::sendMQTTPressureData()
{
    float kPA = calculatePressurekPa();
    
    myHub->sendMessage((const char*)myModule, "KPA", kPA);	
}


//leaving this out for now since it requires the current barometric pressure value from NWS to work
/*long Mpl115a1Module::calculateAltitudeFt(float pressure_kPa) {

  float delta;
  long altitude_ft;


  // See http://en.wikipedia.org/wiki/Barometric_formula
  // If you're a pilot you need to know what's going on here,
  // otherwise just know these steps calculate the barometric altitude (ft)
  // based on the ratio of absolute barometric pressure (psia) to the
  // altimiter setting (psia).
  delta = KPA_TO_PSIA(pressure_kPa) / INHG_TO_PSIA( NWS_BARO );
  //altitude_ft = (1 - pow(delta, (1 / 5.25587611))) / 0.0000068756;
  altitude_ft = 0;
  return altitude_ft;
}*/


float Mpl115a1Module::calculateTemperatureC() {

  unsigned int uiTadc;
  unsigned char uiTH, uiTL;

  unsigned int temperature_counts = 0;

  writeRegister(0x22, 0x00);  // Start temperature conversion
  delay(2);                   // Max wait time is 0.7ms, typ 0.6ms

  // Read pressure
  uiTH = readRegister(TEMPH);
  uiTL = readRegister(TEMPL);

  uiTadc = (unsigned int) uiTH << 8;
  uiTadc += (unsigned int) uiTL & 0x00FF;

  // Temperature is a 10bit value
  uiTadc = uiTadc >> 6;

  // -5.35 counts per °C, 472 counts is 25°C
  return 25 + (uiTadc - 472) / -5.35;
}


float Mpl115a1Module::calculatePressurekPa() {

  // See Freescale document AN3785 for detailed explanation
  // of this implementation.

  signed char sia0MSB, sia0LSB;
  signed char sib1MSB, sib1LSB;
  signed char sib2MSB, sib2LSB;
  signed char sic12MSB, sic12LSB;
  signed char sic11MSB, sic11LSB;
  signed char sic22MSB, sic22LSB;
  signed int sia0, sib1, sib2, sic12, sic11, sic22, siPcomp;
  float decPcomp;
  signed long lt1, lt2, lt3, si_c11x1, si_a11, si_c12x2;
  signed long si_a1, si_c22x2, si_a2, si_a1x1, si_y1, si_a2x2;
  unsigned int uiPadc, uiTadc;
  unsigned char uiPH, uiPL, uiTH, uiTL;

  writeRegister(0x24, 0x00);      // Start Both Conversions
  //writeRegister(0x20, 0x00);    // Start Pressure Conversion
  //writeRegister(0x22, 0x00);    // Start temperature conversion
  delay(2);                       // Max wait time is 1ms, typ 0.8ms

  // Read pressure
  uiPH = readRegister(PRESH);
  uiPL = readRegister(PRESL);
  uiTH = readRegister(TEMPH);
  uiTL = readRegister(TEMPL);

  uiPadc = (unsigned int) uiPH << 8;
  uiPadc += (unsigned int) uiPL & 0x00FF;
  uiTadc = (unsigned int) uiTH << 8;
  uiTadc += (unsigned int) uiTL & 0x00FF;

  // Placing Coefficients into 16-bit Variables
  // a0
  sia0MSB = readRegister(A0MSB);
  sia0LSB = readRegister(A0LSB);
  sia0 = (signed int) sia0MSB << 8;
  sia0 += (signed int) sia0LSB & 0x00FF;

  // b1
  sib1MSB = readRegister(B1MSB);
  sib1LSB = readRegister(B1LSB);
  sib1 = (signed int) sib1MSB << 8;
  sib1 += (signed int) sib1LSB & 0x00FF;

  // b2
  sib2MSB = readRegister(B2MSB);
  sib2LSB = readRegister(B2LSB);
  sib2 = (signed int) sib2MSB << 8;
  sib2 += (signed int) sib2LSB & 0x00FF;

  // c12
  sic12MSB = readRegister(C12MSB);
  sic12LSB = readRegister(C12LSB);
  sic12 = (signed int) sic12MSB << 8;
  sic12 += (signed int) sic12LSB & 0x00FF;

  // c11
  sic11MSB = readRegister(C11MSB);
  sic11LSB = readRegister(C11LSB);
  sic11 = (signed int) sic11MSB << 8;
  sic11 += (signed int) sic11LSB & 0x00FF;

  // c22
  sic22MSB = readRegister(C22MSB);
  sic22LSB = readRegister(C22LSB);
  sic22 = (signed int) sic22MSB << 8;
  sic22 += (signed int) sic22LSB & 0x00FF;

  // Coefficient 9 equation compensation
  uiPadc = uiPadc >> 6;
  uiTadc = uiTadc >> 6;

  // Step 1 c11x1 = c11 * Padc
  lt1 = (signed long) sic11;
  lt2 = (signed long) uiPadc;
  lt3 = lt1*lt2;
  si_c11x1 = (signed long) lt3;

  // Step 2 a11 = b1 + c11x1
  lt1 = ((signed long)sib1)<<14;
  lt2 = (signed long) si_c11x1;
  lt3 = lt1 + lt2;
  si_a11 = (signed long)(lt3>>14);

  // Step 3 c12x2 = c12 * Tadc
  lt1 = (signed long) sic12;
  lt2 = (signed long) uiTadc;
  lt3 = lt1*lt2;
  si_c12x2 = (signed long)lt3;

  // Step 4 a1 = a11 + c12x2
  lt1 = ((signed long)si_a11<<11);
  lt2 = (signed long)si_c12x2;
  lt3 = lt1 + lt2;
  si_a1 = (signed long) lt3>>11;

  // Step 5 c22x2 = c22*Tadc
  lt1 = (signed long)sic22;
  lt2 = (signed long)uiTadc;
  lt3 = lt1 * lt2;
  si_c22x2 = (signed long)(lt3);

  // Step 6 a2 = b2 + c22x2
  lt1 = ((signed long)sib2<<15);
  lt2 = ((signed long)si_c22x2>1);
  lt3 = lt1+lt2;
  si_a2 = ((signed long)lt3>>16);

  // Step 7 a1x1 = a1 * Padc
  lt1 = (signed long)si_a1;
  lt2 = (signed long)uiPadc;
  lt3 = lt1*lt2;
  si_a1x1 = (signed long)(lt3);

  // Step 8 y1 = a0 + a1x1
  lt1 = ((signed long)sia0<<10);
  lt2 = (signed long)si_a1x1;
  lt3 = lt1+lt2;
  si_y1 = ((signed long)lt3>>10);

  // Step 9 a2x2 = a2 * Tadc
  lt1 = (signed long)si_a2;
  lt2 = (signed long)uiTadc;
  lt3 = lt1*lt2;
  si_a2x2 = (signed long)(lt3);

  // Step 10 pComp = y1 + a2x2
  lt1 = ((signed long)si_y1<<10);
  lt2 = (signed long)si_a2x2;
  lt3 = lt1+lt2;

  // Fixed point result with rounding
  //siPcomp = ((signed int)lt3>>13);
  siPcomp = lt3/8192;

  // decPcomp is defined as a floating point number
  // Conversion to decimal value from 1023 ADC count value
  // ADC counts are 0 to 1023, pressure is 50 to 115kPa respectively
  decPcomp = ((65.0/1023.0)*siPcomp)+50;

  return decPcomp;
}


unsigned int Mpl115a1Module::readRegister(byte thisRegister) {

  byte result = 0;

  // select the MPL115A1
  digitalWrite(myCsPin, LOW);

  // send the request
  mySpi->transfer(thisRegister | MPL115A1_READ_MASK);
  result = SPI.transfer(0x00);
  
  // deselect the MPL115A1
  digitalWrite(myCsPin, HIGH);

  return result;  
}


void Mpl115a1Module::writeRegister(byte thisRegister, byte thisValue) {

  // select the MPL115A1
  digitalWrite(myCsPin, LOW);
  delay(10);
  // send the request
  mySpi->transfer(thisRegister & MPL115A1_WRITE_MASK);
  mySpi->transfer(thisValue);

  // deselect the MPL115A1
  digitalWrite(myCsPin, HIGH);
}


#endif
