#include <SPI.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);
#include<DES.h>
DES des;
char ssid[] = "sainu";           
char pass[] = "sainu123";            

String cipher;
const char* host = "192.168.43.114";  // IP serveur - Server IP
const int   port = 3000;
int c=0;     
WiFiClient client;
void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println();

  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to wifi");
  
 if (!client.connect(host, port))
  {
  Serial.println("connection failed");
  Serial.println("wait 5 sec...");
  delay(5000);
  
  }
  
   
  
}
int count=0;
void loop()
{
   
    for(int i=0;i<10;i++)
    {   float humidity = dht.readHumidity();/* Get humidity value */
          float temperature = dht.readTemperature();/* Get temperature value */
         if (isnan(humidity) || isnan(temperature) )
        {
         Serial.println("Failed to read from DHT sensor!");
         break;
      
    }
       Serial.print("\t");
       Serial.print(humidity, 1);
       Serial.print("\t\t");
       Serial.print(temperature, 1);
       Serial.print("\n");
       char t[16];
       char h[16];

       sprintf(t,"%f",temperature);
       
      
       client.print(t);
      
       sprintf(h,"%f",humidity);
      
       client.print(h);
       
      
   
    }
}
