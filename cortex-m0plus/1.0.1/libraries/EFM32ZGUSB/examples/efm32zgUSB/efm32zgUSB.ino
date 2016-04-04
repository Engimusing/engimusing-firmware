#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <functional>
#include "delegate.h"


/*
  {"TOP":"EFMUSB/LED/RED/ON"}
  {"TOP":"EFMUSB/LED/RED/OFF"}
  {"TOP":"EFMUSB/LED/RED/STATUS"}

  {"TOP":"EFMUSB/LED/GREEN/ON"}
  {"TOP":"EFMUSB/LED/GREEN/OFF"}
  {"TOP":"EFMUSB/LED/GREEN/STATUS"}

  {"TOP":"EFMUSB/LED/BLUE/ON"}
  {"TOP":"EFMUSB/LED/BLUE/OFF"}
  {"TOP":"EFMUSB/LED/BLUE/STATUS"}

  {"TOP":"EFMUSB/LED/ALL/ON"}
  {"TOP":"EFMUSB/LED/ALL/OFF"}
  {"TOP":"EFMUSB/LED/ALL/STATUS"}

  {"TOP":"EFMUSB/CPUTEMP/CEL/STATUS"}
  {"TOP":"EFMUSB/CPUTEMP/CEL/INTERVAL","PLD":"time"} // seconds, zero means off

  {"TOP":"EFMUSB/CPUTEMP/FAR/STATUS"}
  {"TOP":"EFMUSB/CPUTEMP/FAR/INTERVAL","PLD":"time"} // seconds, zero means off

  {"TOP":"EFMUSB/CPUVDD/1/STATUS"}
  {"TOP":"EFMUSB/CPUVDD/1/INTERVAL","PLD":"time"} // seconds, zero means off

  {"TOP":"EFMUSB/BRDINFO"}
*/
using namespace dlgt;

static uint8_t efmusbModule[] = "home/efmusb";
uint8_t* module = efmusbModule;

class A
{
  public:
    int foo(int x) {
      return x * x;
    }
    void bar(void) {
      Serial.printf("tstish\r\n");
    }
    void simple(void)
    {
      Serial.printf("Simple\r\n");
    }
};


typedef delegate<void (*)()> ServiceDelegate;
class Service
{
  public:
    void registerDelegate(ServiceDelegate& d)
    {
      mD = &d;
    }
    void notifyDelegate()
    {
      (*mD)();
    }

  private:
    ServiceDelegate* mD;
};

typedef delegate<void (A::*)()> ServiceDelegate2;
class Service2
{
  public:
    void registerDelegate(ServiceDelegate2& d)
    {
      mD = &d;
    }
    void notifyDelegate()
    {
      (*mD)();
    }

  private:
    ServiceDelegate2* mD;
};

void myFreeFunction(void)
{
  Serial.printf("Free\r\n");
}

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin(module);
  ZGUSB.sch_temp_cel(50, module);
  ZGUSB.sch_temp_far(50, module);
  ZGUSB.sch_cpu_vdd(50, module);

  A a;
  auto d = make_delegate(&A::foo, a);
  auto e = make_delegate(&A::bar, a);
  auto f = make_delegate(&A::simple, a);
  auto g = make_delegate(&myFreeFunction);
  Serial.printf("test = %d\r\n", d(42));
  e();
  f();
  g();
  Service s;
  s.registerDelegate(g);
  s.notifyDelegate();
  Service2 t;
  t.registerDelegate(f);
  t.notifyDelegate();
  
}

void loop() {
  COMM.decode();
}

