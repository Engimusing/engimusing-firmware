#!/usr/bin/python

import time
import sys

def wait_until(s, ch, timeout):
    mustend = time.time() + timeout
    while time.time() < mustend:
        if s.inWaiting() > 0:
            c = s.read()
            if (c == ch):
                return True
                sys.stdout.write(ch)
                c = 0
                return False


def checkAck(s):
    n = [0 for i in range(32)]
    i = 0
    ACK = chr(0x06)
    NAK = chr(0x21)
    mustend = time.time() + 2
    while time.time() < mustend:
        if s.inWaiting() > 0:
            ch = s.read()
            if (ch == ACK):
                return True
            if (ch == NAK):
                print "NAK received"
                sys.stdout.write(ch)
                return False
            if (ch == '@'):
                print "CRC Error received"
                sys.stdout.write(ch)
                return False
            else:
                n[i] = ch
                i = i + 1
    print "Timeout waiting for ACK"
    print n
    return False
