import Adafruit_DHT
import time
import requests
import datetime
import sys
import os

sensor=Adafruit_DHT.DHT11
gpio=17
 
while True:
    humidity, temperature = Adafruit_DHT.read_retry(sensor, gpio)
    if humidity is not None and temperature is not None:
        now=datetime.datetime.now()
        print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
        payload={'temp':temperature , 'humidity':humidity,'date':now.strftime("%Y-%m-%d %H:%M")}
        r=requests.get("https://username.000webhostapp.com/sensor2.php", params=payload);
        print r.text
        print r.url
    else:
        print('Failed to get reading. Try again!')
        os.execv(sys.executable, ['python'] + sys.argv)
        
    time.sleep(1)
