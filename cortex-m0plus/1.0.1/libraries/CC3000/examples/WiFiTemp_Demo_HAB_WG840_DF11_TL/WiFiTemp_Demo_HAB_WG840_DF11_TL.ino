/***************************************************
  This is an example for the Adafruit CC3000 Wifi Breakout & Shield

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried, Kevin Townsend and Phil Burgess for
  Adafruit Industries.  BSD license, all text above must be included
  in any redistribution
 ****************************************************/

/*
This example queries an NTP time server to get the current "UNIX time"
(seconds since 1/1/1970, UTC (GMT)), then uses the Arduino's internal
timer to keep relative time.  The clock is re-synchronized roughly
once per day.  This minimizes NTP server misuse/abuse.

The RTClib library (a separate download, and not used here) contains
functions to convert UNIX time to other formats if needed.
*/

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

#define SERIAL Serial

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   33  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  46
#define ADAFRUIT_CC3000_CS    12 // B8
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed but DI

// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2


#define WLAN_SSID       "ExampleSSID"        // cannot be longer than 32 characters!
#define WLAN_PASS       "PASSWORDhere"

#define WLAN_SECURITY   WLAN_SEC_WPA2

Adafruit_CC3000_Client client;

const unsigned long
  connectTimeout  = 15L * 1000L, // Max time to wait for server connection
  responseTimeout = 15L * 1000L; // Max time to wait for data from server
int
  countdown       = 0;  // loop() iterations until next time server query
unsigned long
  lastPolledTime  = 0L, // Last value retrieved from time server
  sketchTime      = 0L; // CPU milliseconds since last server query

int led = 13;

void setup(void)
{
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  delay(1000);
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  delay(2000);
  SERIAL.begin(115200);
  SERIAL.println(F("Hello, CC3000!\n")); 

  displayDriverMode();
  SERIAL.println(F("displayDriverMode\n")); 
  
  SERIAL.println(F("\nInitialising the CC3000 ..."));
  if (!cc3000.begin()) {
    SERIAL.println(F("Unable to initialise the CC3000! Check your wiring?"));
    for(;;);

  digitalWrite(led, HIGH);

  }
SERIAL.println(F("\Post init the CC3000 ..."));
  
  wlan_stop();

}


// To reduce load on NTP servers, time is polled once per roughly 24 hour period.
// Otherwise use millis() to estimate time since last query.  Plenty accurate.
void loop(void) {
  char sentText[64]; 
  int idx = 0;
  
  SERIAL.println("Starting Loop");
  
  memset(sentText, 0, sizeof(sentText));
  
  memcpy(sentText, "Temp:17", sizeof("Temp:17"));
  idx += sizeof("Temp:17") - 1;
  
  //if(idx > sizeof("Temp:") - 1)
  {
       sendText(sentText, idx+1);
       SERIAL.println(sentText);
  }
  
  delay(10000); // Pause 1 second
}
