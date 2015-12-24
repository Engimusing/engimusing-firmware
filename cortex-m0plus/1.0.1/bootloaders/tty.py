#!/usr/bin/python

import time

def wait_until(s, ch, timeout):
    mustend = time.time() + timeout
    while time.time() < mustend:
        if (s.read() == ch): return True
    return False

def checkAck(s):
    ACK = chr(0x06)
    mustend = time.time() + 2
    while time.time() < mustend:
        if (s.read() == ACK): return True
    return False
