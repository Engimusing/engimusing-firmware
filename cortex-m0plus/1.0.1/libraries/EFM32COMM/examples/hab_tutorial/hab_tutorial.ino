#include "Arduino.h"

#include <EFM32COMM.h>

/*
  EFMUSB Commands:
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/CPU/TMPC"}
  {"TOP":"EFMUSB/CPU/TMPF"}
  {"TOP":"EFMUSB/CPU/VDD"}

  HAB Commands:
  {"TOP":"HAB/LED/CTL","PLD":"ON"}
  {"TOP":"HAB/LED/CTL","PLD":"OFF"}
  {"TOP":"HAB/LED/CTL","PLD":"STATUS"}

  {"TOP":"HABTUTOR/SWITCH/RED"}

  {"TOP":"HABTUTOR/SWITCH/BLACK"}

  {"TOP":"HABTUTOR/SENSOR/QRE"}

  {"TOP":"HABTUTOR/SWITCH/REED"}

  {"TOP":"HAB/POT/ADC"}

  {"TOP":"HAB/BUZZER/TONE","PLD":"ON"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"OFF"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"STATUS"}
  {"TOP":"HAB/BUZZER/TONE","PLD":"F500"} // freq in Hz
  {"TOP":"HAB/BUZZER/TONE","PLD":"D200"} // duration in seconds
*/

#define SW1_PIN       2
#define POT_PIN       3
#define REEDSW_PIN    4
#define HABLED_PIN    5
#define BUZZER_PIN    6
#define SWPULL_PIN    7
#define LTSENS_PIN    8
#define SW2_PIN      10
#define GREEN_LED    13
#define BLUE_LED     14
#define RED_LED      15

momentarySwitchClass HABLTS;
momentarySwitchClass HABS1;
momentarySwitchClass HABS2;
detectorSwitchClass HABREED;
onOffCtlClass HABLED;
toneCtlClass HABBUZZ;
adcCtlClass HABPOT;
onOffCtlClass EFMREDLED;
onOffCtlClass EFMBLUELED;
onOffCtlClass EFMGREENLED;
cpuVDDClass EFMCPUVDD;
cpuTempClass EFMCPUTMP;


void setup()
{
  Serial.begin(115200);

  pinMode(SWPULL_PIN, OUTPUT);       // Switch pull up
  digitalWrite(SWPULL_PIN, HIGH);

  EFMREDLED.begin(RED_LED, "EFMUSB/RED/LED");
  EFMBLUELED.begin(BLUE_LED, "EFMUSB/BLUE/LED");
  EFMGREENLED.begin(GREEN_LED, "EFMUSB/GREEN/LED");
  EFMCPUVDD.begin("EFMUSB/CPU/VDD", 50);
  EFMCPUTMP.begin("EFMUSB/CPU/TEMP", 50, 50);

  HABLTS.begin(LTSENS_PIN, "HAB/LTSENSOR", 2);
  HABS1.begin(SW1_PIN, "HAB/SW1", 2);
  HABS2.begin(SW2_PIN, "HAB/SW2", 2);
  HABREED.begin(REEDSW_PIN, "HAB/REED", 2);
  HABLED.begin(HABLED_PIN, "HAB/LED");
  HABBUZZ.begin(BUZZER_PIN, "HAB/BUZZER");
  HABPOT.begin(POT_PIN, "HAB/POT", 50);
}

void loop()
{
  if (COMM.decode()) {
    HABREED.decode();
    HABLED.decode();
    HABBUZZ.decode();
    HABPOT.decode();
    EFMREDLED.decode();
    EFMBLUELED.decode();
    EFMGREENLED.decode();
    EFMCPUVDD.decode();
    EFMCPUTMP.decode();
  }
  HABLTS.update();
  HABS1.update();
  HABS2.update();
  HABREED.update();
  HABLED.update();
  HABBUZZ.update();
  HABPOT.update();
  EFMREDLED.update();
  EFMBLUELED.update();
  EFMGREENLED.update();
  EFMCPUVDD.update();
  EFMCPUTMP.update();
}

