#include "Arduino.h"
#include "test.h"

String inputString = "";         // a string to hold incoming data

static int pins[8] = {2, 3, 4, 5, 6, 7, 8, 10};

#define PINS_TO_TEST    8
#define LED_DELAY  200


void setup() {
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  // reserve 200 bytes for the inputString:
  inputString.reserve(16);
  inputString = "";

  Serial.begin(115200);

  Serial.println("\n\r\n\rGPIO - Unit Test Framework" );
}

void printHelp(void)
{
  Serial.println("Tests:");
   Serial.print("  "); test01(TESTHELP); Serial.println();
   Serial.print("  "); test02(TESTHELP); Serial.println();
   Serial.print("  "); test03(TESTHELP); Serial.println();
   Serial.print("  "); test04(TESTHELP); Serial.println();
   Serial.print("  "); test05(TESTHELP); Serial.println();
   Serial.print("  "); test06(TESTHELP); Serial.println();
   Serial.print("  "); test07(TESTHELP); Serial.println();
   Serial.println();
}

void delay_tty(int dly)
{
  static int charCnt = 0;

  for(int i = 0; i < dly; i++) {
    delay(1);
    if (Serial.available()) {
      char c = (char)Serial.read(); // get the new byte:
      if( ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9'))) {
  Serial.print(c);
  inputString += c;             // add it to the inputString:
  charCnt++;
      } else {
  if((charCnt > 0) && (charCnt < 16)) {
    parse_cmd(inputString);
  } else {
    Serial.print("\n\rBad Command: "); Serial.println(inputString);
  }
  charCnt = 0;
  inputString = "";
      }
    }
  }
}

void loop() {
  digitalWrite(13, LOW);   // turn the LED on (LOW is the voltage level)
  delay_tty(500);          // wait for a second
  digitalWrite(13, HIGH);  // turn the LED off by making the voltage HIGH
  delay_tty(500);          // wait for a second

  digitalWrite(14, LOW);   // turn the LED on (LOW is the voltage level)
  delay_tty(500);          // wait for a second
  digitalWrite(14, HIGH);  // turn the LED off by making the voltage HIGH
  delay_tty(500);          // wait for a second

  digitalWrite(15, LOW);   // turn the LED on (LOW is the voltage level)
  delay_tty(500);          // wait for a second
  digitalWrite(15, HIGH);  // turn the LED off by making the voltage HIGH
  delay_tty(500);          // wait for a second
}

void parse_cmd(String str)
{
  if(str == "help") {printHelp();}
  else if(str == "t1") {test01(RUNTEST);}
  else if(str == "t2") {test02(RUNTEST);}
  else if(str == "t3") {test03(RUNTEST);}
  else if(str == "t4") {test04(RUNTEST);}
  else if(str == "t5") {test05(RUNTEST);}
  else if(str == "t6") {test06(RUNTEST);}
  else if(str == "t7") {test07(RUNTEST);}

  else if(str == "d1") {test01(DESCRIPTION);}
  else if(str == "d2") {test02(DESCRIPTION);}
  else if(str == "d3") {test03(DESCRIPTION);}
  else if(str == "d4") {test04(DESCRIPTION);}
  else if(str == "d5") {test05(DESCRIPTION);}
  else if(str == "d6") {test06(DESCRIPTION);}
  else if(str == "d7") {test07(DESCRIPTION);}

  else {Serial.print("\n\rBad Command: "); Serial.println(str);}
}

