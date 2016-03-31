#!/usr/bin/env python

import os
import threading
import Queue
import string
import serial
import time
import json
import paho.mqtt.client as mqtt

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
                        pQos = 0;
                        pRetain = False
                        mqttp.publish(pTopic, payload=pPayload, qos=pQos, retain=pRetain)
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
    mqttc.subscribe("home/habtutor/+/+/STATUS")
    mqttc.subscribe("home/habtutor/+/+/INTERVAL")
    mqttc.subscribe("home/habtutor/+/+/CHG")
    mqttc.subscribe("home/habtutor/+/+/FREQ")
    mqttc.subscribe("home/habtutor/+/+/DURATION")

    mqttc.subscribe("home/efmusb/+/+/STATUS")
    mqttc.subscribe("home/efmusb/+/+/INTERVAL")
    mqttc.subscribe("home/efmusb/+/+/CHG")
    mqttc.subscribe("home/efmusb/+/+/FREQ")
    mqttc.subscribe("home/efmusb/+/+/DURATION")

toSerialPort_q = Queue.Queue()

def on_message(mqttc, userdata, msg):
    print("message received:" + msg.topic + " - " + str(msg.payload))

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

    mqttc = mqtt.Client(client_id="subscriber")
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
    import sys
    main(sys.argv[1:])






