//#include <Adafruit_SleepyDog.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

//#define STATICIP

//#define SERIAL Serial1

//#define halt(s) { SERIAL.println(F( s )); while(1);  }


//uint16_t checkFirmwareVersion(void);
bool displayConnectionDetails(Adafruit_CC3000 &cc3000, UARTClass &LocalSerial);

boolean CC3000connect(Adafruit_CC3000 &cc3000, const char* wlan_ssid, const char* wlan_pass, uint8_t wlan_security, UARTClass &LocalSerial) {
  //Watchdog.reset();
    
  // Check for compatible firmware
  //if (checkFirmwareVersion() < 0x113)   halt("Wrong firmware version!");
  
  // Delete any old connection data on the module
  LocalSerial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles())     return false;//halt("Failed!");

#ifdef STATICIP
  LocalSerial.println(F("Setting static IP"));
  uint32_t ipAddress = cc3000.IP2U32(192, 168, 1, 23);
  uint32_t netMask = cc3000.IP2U32(255, 255, 255, 0);
  uint32_t defaultGateway = cc3000.IP2U32(192, 168, 1, 1);
  uint32_t dns = cc3000.IP2U32(8, 8, 4, 4);
  
  if (!cc3000.setStaticIPAddress(ipAddress, netMask, defaultGateway, dns)) {
    LocalSerial.println(F("Failed to set static IP!"));
    while(1);
  }
#endif

  // Attempt to connect to an access point
  LocalSerial.print(F("\nAttempting to connect to ")); 
  LocalSerial.print(wlan_ssid); LocalSerial.print(F("..."));

  //Watchdog.disable();
  // try 3 times
  if (!cc3000.connectToAP(wlan_ssid, wlan_pass, wlan_security)) {
    return false;
  }
  
  //Watchdog.enable(8000);
  LocalSerial.println(F("Connected!"));

uint8_t retries;
#ifndef STATICIP  
  /* Wait for DHCP to complete */
  LocalSerial.println(F("Requesting DHCP"));
  retries = 100;
  while (!cc3000.checkDHCP())
  {
    //Watchdog.reset();
    delay(1000);
    retries--;
    if (!retries) return false;
  }  
#endif
  /* Display the IP address DNS, Gateway, etc.  */
  retries = 10;
  while (! displayConnectionDetails(cc3000, LocalSerial)) {
    //Watchdog.reset();
    delay(1000);
    retries--;
    if (!retries) return false;
  }
  
  //Watchdog.reset();

  return true;
}


/**************************************************************************/
/*!
    @brief  Tries to read the CC3000's internal firmware patch ID
*/
/**************************************************************************/
/*uint16_t checkFirmwareVersion(void)
{
  uint8_t major, minor;
  uint16_t version;
  
  if(!cc3000.getFirmwareVersion(&major, &minor))
  {
    LocalSerial.println(F("Unable to retrieve the firmware version!\r\n"));
    version = 0;
  }
  else
  {
    LocalSerial.print(F("Firmware V. : "));
    LocalSerial.print(major); LocalSerial.print(F(".")); LocalSerial.println(minor);
    version = major; version <<= 8; version |= minor;
  }
  return version;
}*/


/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(Adafruit_CC3000 &cc3000, UARTClass &LocalSerial)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    LocalSerial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    LocalSerial.print(F("\r\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    LocalSerial.print(F("\r\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    LocalSerial.print(F("\r\nGateway: ")); cc3000.printIPdotsRev(gateway);
    LocalSerial.print(F("\r\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    LocalSerial.print(F("\r\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    LocalSerial.println();
    return true;
  }
}
