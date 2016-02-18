#!/usr/bin/env python

import os, os.path
import string
import serial
import time
import curses.ascii
import json

def reset():
    sport = getSerialPort()
    sport.sendBreak(0.25)
    print "Send Reset"
    sport.write('r')


def getSerialPort():
    s = serial.Serial(port="/dev/ttyUSB0",
        baudrate=115200, 
        bytesize=8,
        parity='N',
        stopbits=1,
        timeout=0.05,
        xonxoff=0,
        rtscts=0)
    if(s.isOpen() == False):
        s.open()

    if(s.isOpen() == True):
        return s


if __name__ == '__main__':
    reset()
