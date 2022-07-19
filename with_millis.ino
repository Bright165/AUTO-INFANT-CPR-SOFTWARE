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
char pass[] = "";//Enter your WIFI password

int SV_State =LOW;// initial state of LED
const int SV = D2; // pin for Solenoid valve 
int ONE_CYCLE = 30; // standard number for compression per cycle
int NOC; // number of compressions at a given time
int activate; // signal to start compression
int LED = D4; // pin for in-built LED
int disable = 0;
  
BLYNK_WRITE(V1) {

 long rememberTime=0;// this is used by the code
 int DET1 = 600; // delay time for dual extension
 const long RT1 = 200; // delay time for retracting after extension
 const long ET1 = 400; // delay time for extension after retracting
 
activate = param.asInt();

  switch(activate)
  {
    case 0:
    digitalWrite(SV, LOW);
    lcd1.clear();
     
    
    
    case 1:
    lcd1.clear();
    lcd1.print(0, 0, "COMPRESSING");
    lcd1.print(0, 1, "STAND CLEAR");
    
    
   
    if( SV_State ==LOW )
 {
    if( (millis()- rememberTime) >= ET1){   
    SV_State = HIGH;// change the state of solenoid valve
    digitalWrite(SV,SV_State);// turn the solenoid valve ON or OFF
    rememberTime=millis();// remember Current millis() time
    }
 }
 else
 {   
    if( (millis()- rememberTime) >= RT1){     
    SV_State =LOW;// change the state of LED
    digitalWrite(SV,SV_State);// turn the LED ON or OFF
    rememberTime=millis();// remember Current millis() time
    }
 }
   
   
   
   
    lcd1.clear();
    lcd1.print(0, 0, "CYCLE COMPLETED");
    lcd1.print(0, 1, "BEGIN R.BREATHS");
    lcd1.clear();
 
    
  }
  }

 
   BLYNK_CONNECTED()
{

  Blynk.syncVirtual(V1);  
}      
  
 
      
      
void setup() {
  pinMode(SV, OUTPUT);
  digitalWrite(SV,SV_State);// set initial state
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
}

void loop() {
  Blynk.run();
}
