/**************************************************************************

******************************************************************************/

#include "config.h"


extern const uint32_t bootloader_size;

volatile uint32_t flashSize;	//flashSize is the size of the flash in Bytes

void printEntryMessages(void)
{
  uint32_t *pnum = ((uint32_t *) 0x00FE081FCUL);
  uint32_t family  = (DEVINFO->PART & DEVINFO_PART_DEVICE_FAMILY_MASK) >> DEVINFO_PART_DEVICE_FAMILY_SHIFT;
  uint32_t partnum =  pnum[0] & DEVINFO_PART_DEVICE_NUMBER_MASK;

  printf1("\r\nEFM32ZGUSB V0.0.3\r\n");

  printf1("ChipID: %x%x\r\n",DEVINFO->UNIQUEH,DEVINFO->UNIQUEL);

  if ((family == DEVINFO_PART_DEVICE_FAMILY_ZG) && (partnum == 222) && (flashSize == 32768)) {
    printf1("EFM32ZG222F32\r\n\n");
  } else {
    printf1("Wrong Gecko\r\n\n");
  }
}

// Helper function to print flash write verification using CRC
// The start of the block to calculate CRC of.
// The end of the block. This byte is not included in the checksum.
void verify(uint32_t start, uint32_t end)
{
  printf1("\r\nCRC: %x\r\n",CRC_calc((void *) start, (void *) end));
}

//Reset the EFM32
void reset(void)
{
  printf1("Reset Received\r\n");
  for(volatile int i = 0; i < 100000; i++);
  SCB->AIRCR = 0x05FA0004;  // Write to the Application Interrupt/Reset Command Register to reset
}

uint8_t led_cycle(void)
{
  static int ledcnt = 0;
  static int boot_cntr = 0;

  ledAllOff();

  if(ledcnt == 0) {
    //ledRedOn();
  } else if(ledcnt == 1) {
    ledGreenOn();
  } else if(ledcnt == 2) {
    ledBlueOn();
  } else if(ledcnt == 3) {
    ledRedOn();
  } else if(ledcnt == 4) {
    ledcnt = 0;
  }
  ledcnt++;
  return boot_cntr++;
}

void delay(int dtime)
{
  int cnt;

  cnt = 0;
  for(;;) {
    WDOG_Feed();
    EMU_EnterEM1();
    if(getRTCint()) {
      cnt++;
      clearRTCint();
    }
    if(cnt > dtime) break;
  }
}


void SystemInit(void)
{
}


int main(void)
{
  uint8_t  c = 0;

  // Find the size of the flash. DEVINFO->MSIZE is the size in KB so left shift by 10.
  flashSize = ((DEVINFO->MSIZE & DEVINFO_MSIZE_FLASH_MASK) >> DEVINFO_MSIZE_FLASH_SHIFT) << 10;

  io_init();
  //  initWdog();

  FLASH_init();  // Initialize flash for writing
  printEntryMessages();
  initRTC();

  // Wait to allow operator to type a <SPACE> to enter the bootloader
  // If timeout boot the application
  //loop until either the RTC timeouts or one of the UART ports receives a ' '
  while (1) {
    WDOG_Feed();
    EMU_EnterEM1();
    if(getRTCint()) {
      if(led_cycle() > 10) {
	NVIC_DisableIRQ(RTC_IRQn);   //disable the RTC interrupt
	BOOT_boot();
      }
      clearRTCint();
    }
    //receive any characters on the UART's  
    //check to see which port received the ' '
    if(SERIAL_check_rxByte() == ' ') {
      printf1("%");
      break;
    }
  }
  initRTC();
  // The main command loop
  while (1) {
    EMU_EnterEM1();
    WDOG_Feed();
    c = SERIAL_check_rxByte();    // Retrieve new character
    if (c != 0) {   // Echo
      SERIAL_txByte(c);
    }
    if(c != 0) {
      switch (c) {
      case 'u':    // Upload command
	XMODEM_download(bootloader_size, flashSize);
	break;
      case 't':    // Write to user page
	XMODEM_download(XMODEM_USER_PAGE_START, XMODEM_USER_PAGE_END);
	break;
      case 'b':    // Boot into new program
	BOOT_boot();
	break;
      case 'e':    // Check application valid
	checkForValidApp(flashSize);
	break;
      case 'v':    // Verify content by calculating CRC of entire flash
	verify(0, flashSize);
	break;
      case 'V':    // Verify content by calculating CRC of the bootloader
	verify(0, bootloader_size - 1);
	break;
      case 'c':    // Verify content by calculating CRC of application area
	verify(bootloader_size, flashSize);
	break;
      case 'n':    // Verify content by calculating CRC of user page.
	verify(XMODEM_USER_PAGE_START, XMODEM_USER_PAGE_END);
	break;
      case 'm':    // Verify content by calculating CRC of lock page
	verify(XMODEM_LOCK_PAGE_START, XMODEM_LOCK_PAGE_END);
	break;
      case 'r':    // Reset command
	reset();
	break;
      case 'l':
	led_cycle();
	break;
      default:
	printf1("\r\n?\r\n");
      }
    }
  }
}





