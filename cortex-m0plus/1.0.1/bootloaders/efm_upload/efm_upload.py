#!/usr/bin/python

import sys
import serial
import time
import os

from calcCRC import calc_crc
from getArgs import getArgs
from tty import wait_until
from fRead import sendPackets

"""
XMODEM 128 byte blocks

    SENDER                                 RECEIVER

                                            <-- C
    SOH 01 FE Data[128] CRC CRC            -->
                                            <-- ACK
    SOH 02 FD Data[128] CRC CRC            -->
                                            <-- ACK
    SOH 03 FC Data[128] CRC CRC             -->
                                            <-- ACK
    SOH 04 FB Data[100] CPMEOF[28] CRC CRC  -->
                                            <-- ACK
    EOT                                     -->
                                            <-- ACK
"""

# Protocol bytes
SOH = chr(0x01)
STX = chr(0x02)
EOT = chr(0x04)
ACK = chr(0x06)
DLE = chr(0x10)
NAK = chr(0x15)
CAN = chr(0x18)
CRC = chr(0x43) # C


args = getArgs()  # get filename and serial port
print "Uploading {0} to {1}".format(args[0], args[1])

s = serial.Serial(port="/dev/" + args[1],
                  baudrate=115200, 
                  bytesize=8,
                  parity='N',
                  stopbits=1,
                  timeout=None,
                  xonxoff=0,
                  rtscts=0)

if(s.isOpen() == False):
    s.open()
    print "/dev/" + args[1] + " is open already"
    sys.exit(0)

print "Send Break"
s.sendBreak(0.25)
print "Send Reset"
s.write('r')

# loop waiting for question mark, send r and ' ' again after timeout
print "Send Spaces - wait for ?"

ch = 0
cnt = 10
while True:
    s.write(' ')
    if(wait_until(s, '?', 1) == True):
        break;
    else:
        cnt = cnt -1
        if cnt == 0:
            print "timed out waiting for ? after sending space"
            s.close()
            sys.exit(0)

print "? received"

print "Send u and wait for flash erase"

s.write('u')
# loop while flash erase printing ....
ch = 0
mustend = time.time() + 35
while ((ch != '.') and (time.time() < mustend)):
    ch = s.read()
    if ch == '.' or ch == '#':
        sys.stdout.write(ch)
    if(ch == '#'):
        break
    ch = 0

if ch == '#':
    print "\r\nFlash Erase Complete"
else:
    print "Flash Erase Error"
    s.close()
    sys.exit(0)


# timeout if C doesn't come
ch = 0
while ((ch != 'C') and (time.time() < mustend)):
    ch = s.read()
    print ch

if(ch == 'C'):
    print "Start transfer"
else:
    s.close()
    sys.exit(0)

if(sendPackets(s, args[0])):
    print "Send EOT"
    s.write(EOT)        # end of transmission
else:
    s.close()
    sys.exit(0)

print "Send b to boot application"
s.write('b')

print "Close Serial"
s.close()

