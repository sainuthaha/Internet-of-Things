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
  
    int randnum=random(5000,9999);
        Serial.println("Send key");
        Serial.println(randnum);
        char res[4];
        sprintf(res,"%d",randnum);
        client.print(res);
        delay(10);
        while(!(client.available()));
        String c;
        if (client.available()) 
        {
         c = client.readString();
        Serial.println("Received key");
        Serial.println(c);
        }
        int b=c.toInt();
        int a=randnum;
        
        double x=(0.1*4*a*b*b)/(a*a+b*b)*10;
        double y=(0.1*4*a*a*b)/(a*a+b*b)*10;
        int Key=x*y;
        Serial.print("Key for the session: ");
        Serial.println(Key);
  
}
int count=0;
void loop()
{
   
      
      float humidity = dht.readHumidity();/* Get humidity value */
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

       //sprintf(t,"%f",temperature);
       
       desTest(temperature,Key/10);
       cipher.toCharArray(t,17);
       //sprintf(t,"%s",cipher);
       //Serial.println(t);
       client.print(t);
       //Serial.println(strlen(t));
       //sprintf(h,"%f",humidity);
       //sprintf(h,"%s",cipher);
       
       desTest(humidity,Key/10);
       cipher.toCharArray(h,17);
       //Serial.println(h);
       client.print(h);
       
       //Serial.println(strlen(h));
   
      count++;
      if(count==10)
       break;
}
void desTest(float input,int key1)
{
  /*int a=random(5000,9999);
  int b=random(5000,9999);

  long double x=(0.1*4*a*b*b)/(a*a+b*b)*10;
  long double y=(0.1*4*a*a*b)/(a*a+b*b)*10;
  int key1=x*y;
        
  Serial.println(a);
  Serial.println(b);
  Serial.print("Key for the session: ");*/
  Serial.println("key1");
  Serial.println(key1);
  char k[8];
  char ip[8];
  sprintf(ip,"%f",input);
  sprintf(k,"%d",key1);
  Serial.println(ip);
  Serial.println(k);
  byte out[8];
  byte in[] = {ip[0],ip[1],ip[2],ip[3],ip[4],ip[5],ip[6],ip[7]};
  byte key[] = {k[0],k[1],k[2],k[3],k[4],k[5],k[6],k[7]};
  
  Serial.println();
 
  
  //encrypt
  Serial.print("Encrypt...");
  unsigned long time = micros();
  des.encrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);
  int i;
  String zero="0";
  String x;
  for(i=0;i<8;i++)
  {
  if (out[i] < 0x10)
    {
      //Serial.println("hello");
      x.concat(zero);
    }
  x.concat(String(out[i],HEX));
  
  }
  cipher=x;
  cipher.toUpperCase();
  Serial.println(cipher);
  //decrypt
  for (int i = 0; i < 8; i++)
  {
    in[i] = out[i];
  }
  /*Serial.print("Decrypt...");
  time = micros();
  des.decrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);*/
  //client.print(out);
}



void printArray(byte output[])
{
  for (int i = 0; i < 8; i++)
  {
    if (output[i] < 0x10)
    {
      Serial.print("0");
    }
    Serial.print(output[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
