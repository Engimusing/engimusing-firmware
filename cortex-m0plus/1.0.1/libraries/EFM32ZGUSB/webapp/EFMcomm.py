#!/usr/bin/env python

import os, os.path
import string
import serial
import time
import curses.ascii
import json
import threading

sport_lock = threading.Lock()

def sendCommand(str):
    with sport_lock:
        sport = getSerialPort()
        sport.write(str)
        str = sport.read(200)
        cln = ''.join([c for c in str if ord(c) > 32])
        return cln


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
    brdinfo = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
    print "------>>>> " + brdinfo + " " + str(len(brdinfo))

    tempVDD = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
    print "------>>>> " + tempVDD + " " + str(len(tempVDD))

    ledstates = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
    print "------>>>> " + ledstates + " " + str(len(ledstates))

    while(1):
        time.sleep(1)
        brdinfo = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
        print "------>>>> " + brdinfo + " " + str(len(brdinfo))

        tempVDD = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
        print "------>>>> " + tempVDD + " " + str(len(tempVDD))

        ledstates = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
        print "------>>>> " + ledstates + " " + str(len(ledstates))
