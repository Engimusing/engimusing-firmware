"""
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
"""

#!/usr/bin/env python

import os
import threading
import Queue
import string
import serial
import time
import json
import paho.mqtt.client as mqtt
import sys

from sets import Set
subscriptions = Set()

def getSerialPort():
    s = serial.Serial(port=sys.argv[1],
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

class toSerialThread(threading.Thread):
    """ A worker thread that receives strings from the toSerialPort_q queue
        and sends them out the serial port.
    """
    def __init__(self, toSerialPort_q, serialPort):
        super(toSerialThread, self).__init__()
        self.toSerialPort_q = toSerialPort_q
        self.serialPort = serialPort
        self.stoprequest = threading.Event()

    def run(self):
        while not self.stoprequest.isSet():
            try:
                # write command string to serial port
                toSerialPortString = self.toSerialPort_q.get(True, 0.05)
                print toSerialPortString
                self.serialPort.write(toSerialPortString)
            except Queue.Empty:
                continue

    def join(self, timeout=None):
        self.stoprequest.set()
        super(toSerialThread, self).join(timeout) # asks the thread to stop


class fromSerialThread(threading.Thread):
    """ A worker thread that receives strings from the serial port and
        puts them in the fromSerialPort_q queue.
    """

    jsonStr = ""

    def __init__(self, fromSerialPort_q, serialPort):
        super(fromSerialThread, self).__init__()
        self.fromSerialPort_q = fromSerialPort_q
        self.serialPort = serialPort
        self.stoprequest = threading.Event()

    def run(self):
        while not self.stoprequest.isSet():
            fromSerialPortString = self.serialPort.read(200).translate(None, string.whitespace)
            self.jsonStr += fromSerialPortString
            if '{' in self.jsonStr:
                result = self.jsonStr.partition('{')
                self.jsonStr = result[1] + result[2]
                if '}' in self.jsonStr:
                    result = self.jsonStr.partition('}')
                    json = result[0] + result[1]
                    self.jsonStr = result[2]
                    try:
                        self.fromSerialPort_q.put((self.name, json))
                    except Queue.Full:
                        continue
            else:
                self.jsonStr = ""

    def join(self, timeout=None):
        self.stoprequest.set()
        super(fromSerialThread, self).join(timeout)


mqttp = mqtt.Client(client_id="publisher")
mqttc = mqtt.Client(client_id="subscriber")

# The callback for when the client receives a CONNACK response from the server.
def on_connectp(mqttp, userdata, rc):
    print("mqttp connected with result code "+str(rc))
    mqttp.subscribe("home/habtutor/#")


class toMQTT(threading.Thread):
    """ A worker thread that receives strings from the fromSerialPort_q queue
        and sends them to the MQTT client.
    """
    def __init__(self, fromSerialPort_q):
        super(toMQTT, self).__init__()
        self.fromSerialPort_q = fromSerialPort_q

        mqttp.on_connect = on_connectp
        mqttp.connect("localhost",1883,60)

        self.stoprequest = threading.Event()

    def run(self):
        mqttp.loop_start()
        while not self.stoprequest.isSet():
            try:
                result = self.fromSerialPort_q.get(False, 0)
                if len(result[1]) > 10:
                    dict = json.loads(result[1].rstrip())
                    pTopic  = dict['TOP']
                    if len(dict['PLD']) == 0:
                        pPayload = None
                    else:
                        pPayload = dict['PLD']
                    if pPayload != "SUB":
                        pQos = 0;
                        pRetain = False
                        mqttp.publish(pTopic, payload=pPayload, qos=pQos, retain=pRetain)
                    else:
                        subscriptions.add(str(pTopic))
                        mqttc.subscribe(str(pTopic))
            except Queue.Empty:
                continue
                mqttp.loop_stop()

    def join(self, timeout=None):
        self.stoprequest.set()
        super(toMQTT, self).join(timeout)

# The callback for when the client receives a CONNACK response from the server.
def on_connectc(mqttc, userdata, rc):
    print("mqttc connected with result code "+str(rc))
    #Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    
    # mqttc.subscribe("some/topic")
    for s in subscriptions:
        print "Subscribed to: " + s
        mqttc.subscribe(s)
    

toSerialPort_q = Queue.Queue()

def on_message(mqttc, userdata, msg):
    toStr = "{\"TOP\":\"" + msg.topic + "\""
    if len(str(msg.payload)) > 0:
        toStr += ",\"PLD\":\"" + str(msg.payload) + "\"}"
        print(toStr)
    else:
        toStr += "}"
    try:
        toSerialPort_q.put(toStr)
    except Queue.Full:
        print "toSerialPort_q full"

def main(args):


    # Create a single input and a single output queue for all threads.
    fromSerialPort_q = Queue.Queue()
    serialPort = getSerialPort()

    mqttc.on_connect = on_connectc
    mqttc.on_message = on_message
    mqttc.connect("localhost",1883,60)

    toSer    = toSerialThread(toSerialPort_q=toSerialPort_q, serialPort=serialPort)
    fromSer  = fromSerialThread(fromSerialPort_q=fromSerialPort_q, serialPort=serialPort)
    toMqtt   = toMQTT(fromSerialPort_q=fromSerialPort_q)

    toSer.start()
    fromSer.start()
    toMqtt.start()
    mqttc.loop_start()

    onoff = False
    while True:
        time.sleep(1)

    # Ask thread to die
    toSer.join(600)
    fromSer.join(600)
    toMqtt.join(600)
    mqttc.loop_stop()

if __name__ == '__main__':
    main(sys.argv[1:])
if __name__ == 'efmcomm__main__':
    main(sys.argv[1:])





