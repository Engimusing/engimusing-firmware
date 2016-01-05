#ifndef _EFMUSB_TESTH_
#define _EFMUSB_TESTH_

#include "Arduino.h"

void parse_cmd(String);

void test01(uint8_t);
void test02(uint8_t);
void test03(uint8_t);
void test04(uint8_t);
void test05(uint8_t);
void test06(uint8_t);
void test07(uint8_t);

#define TESTHELP    (0x00)
#define DESCRIPTION (0x01)
#define RUNTEST     (0x02)

#endif


