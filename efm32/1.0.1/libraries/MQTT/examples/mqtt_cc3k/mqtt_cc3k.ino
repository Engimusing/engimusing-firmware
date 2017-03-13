/***************************************************
  Adafruit MQTT Library CC3000 Example

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
//#include <Adafruit_SleepyDog.h>
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_CC3000.h"

/*************************** CC3000 Pins ***********************************/

#define ADAFRUIT_CC3000_IRQ   33  // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT  46  // VBAT & CS can be any digital pins.
#define ADAFRUIT_CC3000_CS    12
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "NETGEAR_ASDF5"        // cannot be longer than 32 characters!
#define WLAN_PASS       "TimothyDGeorgeLedaMShurtleff"
#define WLAN_SECURITY   WLAN_SEC_WPA2  // Can be: WLAN_SEC_UNSEC, WLAN_SEC_WEP,
                                       //         WLAN_SEC_WPA or WLAN_SEC_WPA2

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.1.3"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "username"
#define AIO_KEY         "username"

/************ Global State (you don't need to change this!) ******************/

// Setup the main CC3000 class, just like a normal CC3000 sketch.
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT);

// Setup the CC3000 MQTT class by passing in the CC3000 class and MQTT server and login details.
Adafruit_MQTT_CC3000 mqtt(&cc3000, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

// CC3000connect is a helper function that sets up the CC3000 and connects to
// the WiFi network. See the cc3000helper.cpp tab above for the source!
boolean CC3000connect(const char* wlan_ssid, const char* wlan_pass, uint8_t wlan_security);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
//Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
//Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);

  Serial.println(F("Adafruit MQTT demo"));

  //Serial.print(F("Free RAM: ")); Serial.println(getFreeRam(), DEC);

  // Initialise the CC3000 module
  Serial.print(F("\nInit the CC3000..."));
  if (!cc3000.begin())
      halt("Failed");

  //mqtt.subscribe(&onoffbutton);

  while (! CC3000connect(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Retrying WiFi"));
    delay(1000);
  }

  MQTT_connect();

  mqtt.subscribe("EFM/BOARD/LED0/CTL", 0);
}

uint32_t x=0;
uint32_t pingTime=0;
void loop() {
  // Make sure to reset watchdog every loop iteration!
  //Watchdog.reset();

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription())) {
    //if (subscription == &onoffbutton) 
    {
      Serial.print(F("Top:"));
      Serial.println((char *)subscription->lastTopic);
      Serial.print(F("PLD:"));
      Serial.println((char *)subscription->lastread);
    }
  }

  // Now we can publish stuff!
  //Serial.print(F("\nSending photocell val "));
  //Serial.print(x);
  //Serial.print("...");
  /*if (! photocell.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }*/
  if(millis() > pingTime + 1000)
  {
    pingTime = millis();
    // ping the server to keep the mqtt connection alive
    if(! mqtt.ping()) {
      Serial.println(F("MQTT Ping failed."));
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  mqtt.setServerIP(192,168,1,14);

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       if (ret < 0)
            CC3000connect(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);  // y0w, lets connect to wifi again
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}