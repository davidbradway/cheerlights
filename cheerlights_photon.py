# -*- coding: utf-8 -*-
"""
Should be run on a computer, lights are connected to Photon
@author: bradway
"""

import serial
import time
import requests

# I'm going to use a var to check if I've seen the color before
lastcolor = 'black'
color = lastcolor

# Read the thingspeak feed to get the current color
while True:
    try:
        color = requests.get('http://api.thingspeak.com/channels/1417/field/1/last.json').json()['field1']
    except:
        pass
    if color != lastcolor:
        #New color, do stuff
        print(cheerlights)
        lastcolor = color
    time.sleep(16)

