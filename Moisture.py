#!/usr/bin/python
import RPi.GPIO as GPIO 
import time import smtplib
def callback(channel): 
      server = smtplib.SMTP(’yourmail@gmail.com’, 587)
      server.starttls() server.login("yourmail@gmail.com", "phonenumber") 
if GPIO.input(channel): 
      print "low moisture" msg="low moisture,needs watering" 
      server.sendmail("mail1@gmail.com", "mail2@gmail.com", msg) 

else: 
      print "moderate" msg="moisture level okay" 
      server.sendmail("mail1.com", "mail2@gmail.com", msg) 
      server.quit()
GPIO.setmode(GPIO.BCM)
channel = 17 
 
GPIO.setup(channel, GPIO.IN)
GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300)
GPIO.add_event_callback(channel, callback)

while True: 
    time.sleep(0.1)
