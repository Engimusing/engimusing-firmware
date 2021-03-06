///
///@file CC3000helper.h
///@brief CC3000 helper functions. Needed in order for the MqttCC3000 Port class to work correctly.
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
/// Original author of the file is Adafruit
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///
//#include <Adafruit_SleepyDog.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

//#define STATICIP

//#define SERIAL Serial1

//#define halt(s) { SERIAL.println(F( s )); while(1);  }


//uint16_t checkFirmwareVersion(void);
bool displayConnectionDetails(Adafruit_CC3000 &cc3000, UARTClass &LocalSerial);

  ///@brief Connect an Adafruit_CC3000 to a specific access point.
  ////@param [in] cc3000 CC3000 object to connect to the access point.
  ///@param [in] wlan_ssid Name of the access point to connect to
  ///@param [in] wlan_pass Password to use to connect to the access point.
  ///@param [in] wlan_security Type of security the access point uses.
  ///@param [in] LocalSerial Serial port to use for printouts
  ///@return returns true if the connection succeeded else return false
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


///@brief Tries to read the IP address and other connection details
///@param [in] cc3000 CC3000 to get the IP address and other connection details from
///@param [in] LocalSerial Serial port to print out the details on.
///@return True if the IP address could be determined and printed.
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
