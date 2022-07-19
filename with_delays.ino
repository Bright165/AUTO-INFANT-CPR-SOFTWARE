 /*MIT License

Copyright (c) 2022 Bright165

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
/*DESIGN OF A NEONATAL CHEST COMPRESSION DEVICE TO AID IN INFANT CPR
 */
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "uCD2FJlH9DFMAfGjx0_4oiSQKXaG5_NH" //Enter your blynk auth token

WidgetLCD lcd1(V3);


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "BEESWAX";//Enter your WIFI name
char pass[] = "0244177265";//Enter your WIFI password


int SV = D2; // pin for Solenoid valve 
int ONE_CYCLE = 30; // standard number for compression per cycle
int NOC; // number of compressions at a given time
int activate; // signal to start compression
int LED = D4; // pin for in-built LED
int disable = 0;
  
BLYNK_WRITE(V1) {

 int DET1 = 600; // delay time for dual extension
 int RT1 = 200; // delay time for retracting after extension
 int ET1 = 400; // delay time for extension after retracting
 
activate = param.asInt();

  switch(activate)
  {
    case 0:
    Blynk.virtualWrite(V1,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();
      break;
    
    
    case 1:
    lcd1.clear();
    lcd1.print(0, 0, "COMPRESSING");
    lcd1.print(0, 1, "STAND CLEAR");
    
    for (NOC=1;NOC<=ONE_CYCLE;NOC=NOC+1)
   {
   digitalWrite(SV, HIGH); 
   delay(RT1); 
   digitalWrite(SV, LOW);
   delay(ET1);  
   
    if(activate==0)
  {
   Blynk.virtualWrite(V1,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();  
   break;
  }  
   }
   
    lcd1.clear();
    lcd1.print(0, 0, "CYCLE COMPLETED");
    lcd1.print(0, 1, "BEGIN R.BREATHS");
    
 digitalWrite(LED, LOW); // BLINK LED for 3 seconds to alert for 2 rescue breaths
 delay(1000);  
 digitalWrite(LED, HIGH);
 delay(1000);  
 digitalWrite(LED, LOW);
 delay(1000);
 digitalWrite(LED, HIGH);
 delay(1000);
 digitalWrite(LED, LOW); 
 delay(1000);  
 digitalWrite(LED, HIGH);
 lcd1.clear();
 break;
    
  }
  }

  BLYNK_WRITE(V2) {

 int DET2 = 500; // delay time for dual extension
 int RT2 = 200; // delay time for retracting after extension
 int ET2 = 300; // delay time for extension after retracting
 
activate = param.asInt();

  switch(activate)
  {
    case 0:
    Blynk.virtualWrite(V2,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();
      break;
     
     
    case 1:
    lcd1.clear();
    lcd1.print(0, 0, "COMPRESSING");
    lcd1.print(0, 1, "STAND CLEAR");
     
  
    for (NOC=1;NOC<=ONE_CYCLE;NOC=NOC+1)
   {
    
   digitalWrite(SV, HIGH); 
   delay(RT2); 
   digitalWrite(SV, LOW);
   delay(ET2);    
   
    if(activate==0)
  {
    Blynk.virtualWrite(V2,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();  
   break;
  }
   }
    lcd1.clear();
    lcd1.print(0, 0, "CYCLE COMPLETED");
    lcd1.print(0, 1, "BEGIN R.BREATHS");
    
 digitalWrite(LED, LOW); // BLINK LED for 3 seconds to alert for 2 rescue breaths
 delay(1000);  
 digitalWrite(LED, HIGH);
 delay(1000);  
 digitalWrite(LED, LOW);
 delay(1000);
 digitalWrite(LED, HIGH);
 delay(1000);
 digitalWrite(LED, LOW); 
 delay(1000);  
 digitalWrite(LED, HIGH);
 lcd1.clear();
 break;
  
  }
  }

 BLYNK_WRITE(V0) {

 int DET3 = 750; // delay time for dual extension
 int RT3 = 200; // delay time for retracting after extension
 int ET3 = 550; // delay time for extension after retracting
 
activate = param.asInt();

  switch(activate)
  {
    case 0:
    Blynk.virtualWrite(V0,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();
      break;
     
    case 1:
    lcd1.clear();
    lcd1.print(0, 0, "COMPRESSING");
    lcd1.print(0, 1, "STAND CLEAR");
     
  
    for (NOC=1;NOC<=ONE_CYCLE;NOC=NOC+1)
   {
    
   digitalWrite(SV, HIGH); 
   delay(RT3); 
   digitalWrite(SV, LOW);
   delay(ET3);    
   
    if(activate==0)
  {
    Blynk.virtualWrite(V0,disable);
    digitalWrite(SV, LOW);
    lcd1.clear();  
   break;
  }
   }
    lcd1.clear();
    lcd1.print(0, 0, "CYCLE COMPLETED");
    lcd1.print(0, 1, "BEGIN R.BREATHS");
    
 digitalWrite(LED, LOW); // BLINK LED for 3 seconds to alert for 2 rescue breaths
 delay(1000);  
 digitalWrite(LED, HIGH);
 delay(1000);  
 digitalWrite(LED, LOW);
 delay(1000);
 digitalWrite(LED, HIGH);
 delay(1000);
 digitalWrite(LED, LOW); 
 delay(1000);  
 digitalWrite(LED, HIGH);
 lcd1.clear();
 break;
  
  }
  }
  
   BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  
  Blynk.syncVirtual(V1); 
  Blynk.syncVirtual(V2);  
}      
  
 
      
      
void setup() {
  pinMode(SV, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
}

void loop() {
  Blynk.run();
}
