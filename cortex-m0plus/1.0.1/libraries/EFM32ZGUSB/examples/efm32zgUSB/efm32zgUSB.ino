#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>

/*
{"CPUID":"24353a02522fa331", "ADDR":"01"}   // set address to 01 for cpuid
{"CPUID":"24353a02522fa331", "MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "ON"} // CPUID is target
{"ADDR":"01", "MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "ON"} // address 01 is target

// following are targeted to the first (or only) device in a chain
{"MOD":"EFMUSB", "TYP":"LED", "IID":"RED","ACT":"ON"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"RED", "ACT":"OFF"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"GREEN", "ACT":"ON"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"GREEN", "ACT":"OFF"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"BLUE", "ACT":"ON"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"BLUE", "ACT":"OFF"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"ALL", "ACT":"ON"}
{"MOD":"EFMUSB", "TYP":"LED", "IID":"ALL", "ACT":"OFF"}

{"MOD":"EFMUSB", "TYP":"LEDR", "IID":"RED"}
{"MOD":"EFMUSB", "TYP":"LEDR", "IID":"GREEN"}
{"MOD":"EFMUSB", "TYP":"LEDR", "IID":"BLUE"}
{"MOD":"EFMUSB", "TYP":"LEDR", "IID":"ALL"}

{"MOD":"EFMUSB", "TYP":"CPUTEMP"}
{"MOD":"EFMUSB", "TYP":"CPUVDD"}
{"MOD":"EFMUSB", "TYP":"BRDINFO"}
{"MOD":"EFMUSB", "TYP":"BRDNAME"}
{"MOD":"EFMUSB", "TYP":"BLVER"}
{"MOD":"EFMUSB", "TYP":"CHIPID"}
{"MOD":"EFMUSB", "TYP":"CPUTYPE"}
{"MOD":"EFMUSB", "TYP":"FLASHSIZE"}
{"MOD":"EFMUSB", "TYP":"SRAMSIZE"} */

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
}

void loop() {
  COMM.decode();
}

