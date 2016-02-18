#!/usr/bin/env python

import os, os.path
import string
import serial
import time
import curses.ascii
import json
import cherrypy
import EFMcomm as efm



def getBoardInfo():
    print "----->>> get board name called"
    brdinfo = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
    print "------>>>> " + brdinfo + " " + str(len(brdinfo))
    #return json.loads(brdinfo)
    return brdinfo

def getTempVDD():
    print "----->>> get temp vdd called"
    tempVDD = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
    print "------>>>> " + tempVDD + " " + str(len(tempVDD))
    #return json.loads(tempVDD)
    return tempVDD

def getLEDstates():
    print "----->>> get LED states called"
    ledstates = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
    print "------>>>> " + ledstates + " " + str(len(ledstates))
    #return json.loads(ledstates)
    return ledstates


if __name__ == '__main__':
    brdinfo = getBoardInfo()
    print "------>>>> " + brdinfo + " " + str(len(brdinfo))

    tempVDD = getTempVDD()
    print "------>>>> " + tempVDD + " " + str(len(tempVDD))

    ledstates = getLEDstates()
    print "------>>>> " + ledstates + " " + str(len(ledstates))

