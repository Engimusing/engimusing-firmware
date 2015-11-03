#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;

String inputString = "";         // a string to hold incoming data

void setup(void)
{
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(16);

  Serial.println("\n\r\n\rUnit Test Framework" );

  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
}

void printHelp(void)
{
  Serial.println("Tests:");
  delay(1);  Serial.print("  "); test01(TESTHELP); Serial.println();
  delay(1);  Serial.print("  "); test02(TESTHELP); Serial.println();
  delay(1);  Serial.print("  "); test03(TESTHELP); Serial.println();
  delay(1);  Serial.print("  "); test04(TESTHELP); Serial.println();
  delay(1);  Serial.println();
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


void loop(void)
{

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
  else if(str == "test01") {test01(RUNTEST);}
  else if(str == "test02") {test02(RUNTEST);}
  else if(str == "test03") {test03(RUNTEST);}
  else if(str == "test04") {test04(RUNTEST);}
  else if(str == "test05") {test05(RUNTEST);}
  else if(str == "test06") {test06(RUNTEST);}
  else if(str == "test07") {test07(RUNTEST);}
  else if(str == "test08") {test08(RUNTEST);}
  else if(str == "test09") {test09(RUNTEST);}
  else if(str == "test10") {test10(RUNTEST);}
  else if(str == "test11") {test11(RUNTEST);}
  else if(str == "test12") {test12(RUNTEST);}
  else if(str == "test13") {test13(RUNTEST);}
  else if(str == "test14") {test14(RUNTEST);}
  else if(str == "test15") {test15(RUNTEST);}
  else if(str == "test16") {test16(RUNTEST);}
  else if(str == "test17") {test17(RUNTEST);}
  else if(str == "test18") {test18(RUNTEST);}
  else if(str == "test19") {test19(RUNTEST);}
  else if(str == "test20") {test20(RUNTEST);}
  else if(str == "test21") {test21(RUNTEST);}
  else if(str == "test22") {test22(RUNTEST);}
  else if(str == "test23") {test23(RUNTEST);}
  else if(str == "test24") {test24(RUNTEST);}
  else if(str == "test25") {test25(RUNTEST);}
  else if(str == "test26") {test26(RUNTEST);}
  else if(str == "test27") {test27(RUNTEST);}
  else if(str == "test28") {test28(RUNTEST);}
  else if(str == "test29") {test29(RUNTEST);}
  else if(str == "test30") {test30(RUNTEST);}
  else if(str == "test31") {test31(RUNTEST);}
  else if(str == "test32") {test32(RUNTEST);}
  else if(str == "test33") {test33(RUNTEST);}
  else if(str == "test34") {test34(RUNTEST);}
  else if(str == "test35") {test35(RUNTEST);}
  else if(str == "test36") {test36(RUNTEST);}
  else if(str == "test37") {test37(RUNTEST);}
  else if(str == "test38") {test38(RUNTEST);}
  else if(str == "test39") {test39(RUNTEST);}
  else if(str == "test40") {test40(RUNTEST);}
  else if(str == "test41") {test41(RUNTEST);}
  else if(str == "test42") {test42(RUNTEST);}
  else if(str == "test43") {test43(RUNTEST);}
  else if(str == "test44") {test44(RUNTEST);}
  else if(str == "test45") {test45(RUNTEST);}
  else if(str == "test46") {test46(RUNTEST);}
  else if(str == "test47") {test47(RUNTEST);}
  else if(str == "test48") {test48(RUNTEST);}
  else if(str == "test49") {test49(RUNTEST);}

  else if(str == "desc01") {test01(DESCRIPTION);}
  else if(str == "desc02") {test02(DESCRIPTION);}
  else if(str == "desc03") {test03(DESCRIPTION);}
  else if(str == "desc04") {test04(DESCRIPTION);}
  else if(str == "desc05") {test05(DESCRIPTION);}
  else if(str == "desc06") {test06(DESCRIPTION);}
  else if(str == "desc07") {test07(DESCRIPTION);}
  else if(str == "desc08") {test08(DESCRIPTION);}
  else if(str == "desc09") {test09(DESCRIPTION);}
  else if(str == "desc10") {test10(DESCRIPTION);}
  else if(str == "desc11") {test11(DESCRIPTION);}
  else if(str == "desc12") {test12(DESCRIPTION);}
  else if(str == "desc13") {test13(DESCRIPTION);}
  else if(str == "desc14") {test14(DESCRIPTION);}
  else if(str == "desc15") {test15(DESCRIPTION);}
  else if(str == "desc16") {test16(DESCRIPTION);}
  else if(str == "desc17") {test17(DESCRIPTION);}
  else if(str == "desc18") {test18(DESCRIPTION);}
  else if(str == "desc19") {test19(DESCRIPTION);}
  else if(str == "desc20") {test20(DESCRIPTION);}
  else if(str == "desc21") {test21(DESCRIPTION);}
  else if(str == "desc22") {test22(DESCRIPTION);}
  else if(str == "desc23") {test23(DESCRIPTION);}
  else if(str == "desc24") {test24(DESCRIPTION);}
  else if(str == "desc25") {test25(DESCRIPTION);}
  else if(str == "desc26") {test26(DESCRIPTION);}
  else if(str == "desc27") {test27(DESCRIPTION);}
  else if(str == "desc28") {test28(DESCRIPTION);}
  else if(str == "desc29") {test29(DESCRIPTION);}
  else if(str == "desc30") {test30(DESCRIPTION);}
  else if(str == "desc31") {test31(DESCRIPTION);}
  else if(str == "desc32") {test32(DESCRIPTION);}
  else if(str == "desc33") {test33(DESCRIPTION);}
  else if(str == "desc34") {test34(DESCRIPTION);}
  else if(str == "desc35") {test35(DESCRIPTION);}
  else if(str == "desc36") {test36(DESCRIPTION);}
  else if(str == "desc37") {test37(DESCRIPTION);}
  else if(str == "desc38") {test38(DESCRIPTION);}
  else if(str == "desc39") {test39(DESCRIPTION);}
  else if(str == "desc40") {test40(DESCRIPTION);}
  else if(str == "desc41") {test41(DESCRIPTION);}
  else if(str == "desc42") {test42(DESCRIPTION);}
  else if(str == "desc43") {test43(DESCRIPTION);}
  else if(str == "desc44") {test44(DESCRIPTION);}
  else if(str == "desc45") {test45(DESCRIPTION);}
  else if(str == "desc46") {test46(DESCRIPTION);}
  else if(str == "desc47") {test47(DESCRIPTION);}
  else if(str == "desc48") {test48(DESCRIPTION);}
  else if(str == "desc49") {test49(DESCRIPTION);}

  else {Serial.print("\n\rBad Command: "); Serial.println(str);}
}

