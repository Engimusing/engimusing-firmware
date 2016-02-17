#!/usr/bin/env python

import os, os.path
import string
import serial
import time
import curses.ascii
import json
import cherrypy
import EFMcomm as efm


class App(object):
    @cherrypy.expose
    def index(self):
        return open('index.html')

    @cherrypy.expose
    @cherrypy.tools.json_out()
    def getBoardInfo(self):
        print "----->>> get board name called"
        brdinfo = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
        print "------>>>> " + brdinfo + " " + str(len(brdinfo))
        return json.loads(brdinfo)

    @cherrypy.expose
    @cherrypy.tools.json_out()
    def getTempVDD(self):
        print "----->>> get temp vdd called"
        tempVDD = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
        print "------>>>> " + tempVDD + " " + str(len(tempVDD))
        return json.loads(tempVDD)

    @cherrypy.expose
    @cherrypy.tools.json_out()
    def getLEDstates(self):
        print "----->>> get LED states called"
        ledstates = efm.sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
        print "------>>>> " + ledstates + " " + str(len(ledstates))
        return json.loads(ledstates)

if __name__ == '__main__':
    print "----->>> Server Started"
    conf = {
         '/': {
             'tools.sessions.on': True,
             'tools.staticdir.root': os.path.abspath(os.getcwd())
         },
         '/scripts': {
             'tools.staticdir.on': True,
             'tools.staticdir.dir': 'scripts'
         }
     } 
    print conf

    cherrypy.quickstart(App(), '/', conf)

