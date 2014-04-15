# -*- coding: utf-8 -*-
"""
Created on Tue Dec 10 08:55:05 2013

@author: bradway
"""

import serial
import time
import requests
#import json

# Setup serial connection to arduino
# Uncomment line below if ISPC
DEVICE = 'COM3'
# Uncomment line below if ISLINUX
#DEVICE = '/dev/ttyACM0'
BAUD = 9600
arduino = serial.Serial(DEVICE, BAUD)

# I'm going to use a var to check if I've seen the color before
color = 'black'
cheerlights = color

# Read the thingspeak feed to get the current color
while True:
    try:
        resp = requests.get('http://api.thingspeak.com/channels/1417/field/1/last.json')
        data = resp.json()
        cheerlights = data['field1']
    except:
        pass
    if cheerlights != color:
        #New color, do stuff
        arduino.write(str(cheerlights))
        #for c in cheerlights:
        #    arduino.write(c)
        print cheerlights
        color = cheerlights
    time.sleep(16)
