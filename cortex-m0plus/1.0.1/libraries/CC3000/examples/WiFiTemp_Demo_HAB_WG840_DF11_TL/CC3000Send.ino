
#define SERIAL Serial

/**************************************************************************/
/*!
    @brief  Displays the driver mode (tiny of normal), and the buffer
            size if tiny mode is not being used

    @note   The buffer size and driver mode are defined in cc3000_common.h
*/
/**************************************************************************/
void displayDriverMode(void)
{
  #ifdef CC3000_TINY_DRIVER
    SERIAL.println(F("CC3000 is configure in 'Tiny' mode"));
  #else
    SERIAL.print(F("RX Buffer : "));
    SERIAL.print(CC3000_RX_BUFFER_SIZE);
    SERIAL.println(F(" bytes"));
    SERIAL.print(F("TX Buffer : "));
    SERIAL.print(CC3000_TX_BUFFER_SIZE);
    SERIAL.println(F(" bytes"));
  #endif
}

/**************************************************************************/
/*!
    @brief  Tries to read the CC3000's internal firmware patch ID
*/
/**************************************************************************/
uint16_t checkFirmwareVersion(void)
{
  uint8_t major, minor;
  uint16_t version;
  
#ifndef CC3000_TINY_DRIVER  
  if(!cc3000.getFirmwareVersion(&major, &minor))
  {
    SERIAL.println(F("Unable to retrieve the firmware version!\r\n"));
    version = 0;
  }
  else
  {
    SERIAL.print(F("Firmware V. : "));
    SERIAL.print(major); SERIAL.print(F(".")); SERIAL.println(minor);
    version = major; version <<= 8; version |= minor;
  }
#endif
  return version;
}

/**************************************************************************/
/*!
    @brief  Tries to read the 6-byte MAC address of the CC3000 module
*/
/**************************************************************************/
void displayMACAddress(void)
{
  uint8_t macAddress[6];
  
  if(!cc3000.getMacAddress(macAddress))
  {
    SERIAL.println(F("Unable to retrieve MAC Address!\r\n"));
  }
  else
  {
    SERIAL.print(F("MAC Address : "));
    cc3000.printHex((byte*)&macAddress, 6);
  }
}


/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    SERIAL.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    SERIAL.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    SERIAL.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    SERIAL.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    SERIAL.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    SERIAL.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    SERIAL.println();
    return true;
  }
}

void enableWifi()
{
  /*uint16_t firmware = checkFirmwareVersion();
  if ((firmware != 0x113) && (firmware != 0x118)) {
    SERIAL.println(firmware);
    SERIAL.println(0x113);
    SERIAL.println(0x118);
    SERIAL.println(F("Wrong firmware version!"));
    //for(;;);
  }*/
  
  //displayMACAddress();
  
  /*SERIAL.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    SERIAL.println(F("Failed!"));
    while(1);
  }*/
  wlan_start(0);
  
  /* Attempt to connect to an access point */
  char *ssid = WLAN_SSID;             /* Max 32 chars */
  SERIAL.print(F("\nAttempting to connect to ")); SERIAL.println(ssid);
  
  /* NOTE: Secure connections are not available in 'Tiny' mode! */
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    SERIAL.println(F("Failed!"));
    while(1);
  }

  SERIAL.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
  SERIAL.println(F("Request DHCP"));
  while (!cc3000.checkDHCP()) {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  /* Display the IP address DNS, Gateway, etc. */  
  while (!displayConnectionDetails()) {
    if(!cc3000.checkConnected())
    {
      if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) 
      {
        SERIAL.println(F("Failed!"));
      }
      
      SERIAL.println(F("Request DHCP"));
      while (!cc3000.checkDHCP()) {
        delay(100); // ToDo: Insert a DHCP timeout!
      }
    }
    delay(1000);
  }
}


// Disconnect from wireless network and shut down the CC3000.
void disableWifi() {
  // Disconnect from the AP if connected.
  // This might not be strictly necessary, but I found
  // it was sometimes difficult to quickly reconnect to
  // my AP if I shut down the CC3000 without first
  // disconnecting from the network.
  SERIAL.println(F("CC3000 shut down.A")); 
  if (cc3000.checkConnected()) {
    cc3000.disconnect();
  }
  SERIAL.println(F("CC3000 shut down.B")); 
  // Wait for the CC3000 to finish disconnecting before
  // continuing.
  /*while (cc3000.checkConnected()) {
    delay(100);
  }*/
  
  // Shut down the CC3000.
  wlan_stop();
  
  SERIAL.println(F("CC3000 shut down.")); 
}

void sendText(char *buf, int size)
{

	enableWifi();
  //uint8_t       buf[48];
  unsigned long ip, startTime, t = 0L;
   ip = 3232235790; 
  if(1)//
  //if(cc3000.getHostByName("192.168.1.14", &ip))
  {

    SERIAL.println(F("\r\nAttempting connection..."));
    startTime = millis();
    do {
      
      client = cc3000.connectTCP(ip, 25152);
      if(!client.connected())
      {
        delay(1000);
        client.close();
      }
    } while((!client.connected()) &&
            ((millis() - startTime) < connectTimeout));

    if(client.connected()) {
      SERIAL.print(F("connected!\r\nIssuing request..."));


      client.write(buf, size);
    
      while(client.available()) {
        client.read(buf, sizeof(buf));
      }
      
      client.close();
    }
    
    
  }
  disableWifi();
}
