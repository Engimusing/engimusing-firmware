#include "Arduino.h"
#include "test.h"
#include "timer.h"

extern TimersLP Timers;

extern LEUARTClass Serial;
static String test_help = "test01 - Timer";


void print_error(char m[], uint32_t expected, uint32_t start, uint32_t end)
{
  Serial.printf("%s  delay = %d",m,end-start);
  if((end-start) == expected) {
    Serial.println(" - PASSED\n\r");
  } else {
    Serial.println(" - FAILED\n\r");
  }
}

void test01_test(void)
{
  uint32_t start, end;

  delay(5); 
  start = millis();
  Timers.delay_ms(5);
  end = millis();
  print_error("delay_ms(5):", 5, start, end);

  start = micros();
  Timers.delay_us(3000);
  end = micros();
  print_error("delay_us(3000):", 3000, start, end);

  start = micros();
  Timers.delay_us(200);
  end = micros();
  print_error("delay_us(200):",200, start, end);

  start = micros();
  Timers.delay_us(50);
  end = micros();
  print_error("delay_us(50):",50, start, end);

  start = micros();
  Timers.delay_us(5);
  end = micros();
  print_error("delay_us(5):",5, start, end);

  start = micros();
  while(micros() < start + 5);
  end = micros();
  print_error("delay_us(5):",5, start, end);

  start = micros();
  delayMicroseconds(5);
  end = micros();
  print_error("delay_us(5):",5, start, end);

}

void test01_desc(void)
{
  Serial.println("\n\rTest 01 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test01(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test01_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test01");
    test01_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
