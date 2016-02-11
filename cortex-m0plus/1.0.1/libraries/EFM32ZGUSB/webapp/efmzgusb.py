import os, os.path
import string
import serial
import time
import curses.ascii
import json

import cherrypy

def get_xml_line(sport, str):
        sport.write(str)
        cnt = 0
        timeout = 5
        str = ""
        mustend = time.time() + timeout
        while time.time() < mustend:
            if sport.inWaiting() > 0:
                c = sport.read()
                if cnt > 1 and c == '\n':
                    break
                if curses.ascii.isgraph(c) != 0:
                    cnt = cnt + 1
                    str = ''.join((str, c))
        if cnt < 1:
            if time.time() > mustend:
                print "timed out waiting for line"
                str = "time out waiting for response"
            else:
                print "some other error"
                str = "response error"
        return str

def getSerialPort():
    s = serial.Serial(port="/dev/ttyUSB0",
        baudrate=115200, 
        bytesize=8,
        parity='N',
        stopbits=1,
        timeout=5,
        xonxoff=0,
        rtscts=0)
    if(s.isOpen() == False):
        s.open()

    if(s.isOpen() == True):
        print "----->>> /dev/ttyUSB0 Open"
    return s

class App(object):
    @cherrypy.expose
    def index(self):
        return open('index.html')

    @cherrypy.expose
    @cherrypy.tools.json_out()
    def getBoardInfo(self):
        s = getSerialPort()
        print "----->>> get board name called"
        xml = {}
        xml = get_xml_line(s,"{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
        print "------>>>> " + xml
        return json.loads(xml)


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

"""
[/]
tools.staticdir.root = "/home/site"

[/style.css]
tools.staticfile.on = True
tools.staticfile.filename = "/home/site/style.css"
"""
