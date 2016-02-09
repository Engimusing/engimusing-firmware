import os, os.path
import string
import serial
import time

import cherrypy

class StringGenerator(object):
    @cherrypy.expose
    def index(self):
        td = time.time()
        return str(td)
        #return open('index.html')


if __name__ == '__main__':
    cherrypy.quickstart(StringGenerator())

