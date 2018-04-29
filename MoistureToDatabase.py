#!/usr/bin/python

import requests
import RPi.GPIO as GPIO
import time
import smtplib
import datetime
 


def callback(channel):
       
	if GPIO.input(channel):
		print "low moisture"
	   	msg="low moisture,needs watering"
	   	now=datetime.datetime.now()
                payload={'data':"low moisture",'date':now.strftime("%Y-%m-%d %H:%M")}
                r=requests.get("https://username.000webhostapp.com/1.php", params=payload);
	   	print r.text
                print r.url
	         
		
	else:
		print "moderate"
		msg="moisture level okay"
		now=datetime.datetime.now()
                payload={'data':"moderate moisture",'date':now.strftime("%Y-%m-%d %H:%M")}
                r=requests.get("https://username.000webhostapp.com/1.php", params=payload);                
                print r.text
                print r.url
                print r.text

GPIO.setmode(GPIO.BCM)
channel = 17
GPIO.setup(channel, GPIO.IN)
GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300)

GPIO.add_event_callback(channel, callback)
while True:
	
	time.sleep(0.3)











