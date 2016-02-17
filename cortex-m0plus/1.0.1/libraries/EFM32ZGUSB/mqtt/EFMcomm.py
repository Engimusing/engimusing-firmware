#!/usr/bin/env python

import os, os.path
import string
import serial
import time
import curses.ascii
import json
import threading
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish

sport_lock = threading.Lock()


def on_message(client, userdata, msg):
    print(msg.topic+" " + str(msg.payload))
    with sport_lock:
        s = getSerialPort()
        m = "{\"TOP\":\"" + msg.topic + "\""
        if len(str(msg.payload)):
            pld = ",\"PLD\":\"" + msg.payload + "\"}"
            m = m.join(pld)
        s.write(m)

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

    mqttc = mqtt.Client()
    mqttc.connect("localhost",1883,60)
    mqttc.on_message = on_message
    mqttc.loop_start()
    mqttc.subscribe("home/livingroom/#", qos=0)
    publish.single("/home/livingroom/switch1", payload="on")
    while 1:
        with sport_lock:
            s = getSerialPort()
            n = s.read(200)
        if len(n):
            print n

    mqttc.loop_stop()
    mqttc.disconnect()







    brdinfo = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
    print "------>>>> " + brdinfo + " " + str(len(brdinfo))

    tempVDD = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
    print "------>>>> " + tempVDD + " " + str(len(tempVDD))

    ledstates = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
    print "------>>>> " + ledstates + " " + str(len(ledstates))

    print "\r\nTest MQTT\r\n"
    mqttc = mqtt.Client()
    mqttc.connect("localhost",1883,60)
    mqttc.loop_start()

    brdinfo = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"BRDINFO\"}")
    (result,mid)=mqttc.publish("efmusb/brdinfo",brdinfo,2,True)

    while 1:
        tempVDD = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"TEMPVDD\"}")
        (result,mid)=mqttc.publish("efmusb/tempvdd",tempVDD,2)
        ledstates = sendCommand("{\"MOD\":\"EFMUSB\", \"TYP\":\"LEDR\", \"IID\":\"ALL\"}")
        (result,mid)=mqttc.publish("efmusb/ledstates",ledstates,2)
        time.sleep(1)

    mqttc.loop_stop()
    mqttc.disconnect()

# publish(topic, payload=None, qos=0, retain=False)
