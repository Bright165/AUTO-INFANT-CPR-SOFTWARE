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

int port = 8080;
int Latch;
int Flag;

#define LatchRelay D4 //  GPIO12 or D6

BlynkTimer timer;

int COMPRESSION_ID1;
int  COMPRESSION_ID2;
int  COMPRESSION_ID3;
int Retract_ID;
int message1_ID;
int message2_ID1;
int message2_ID2;
int message2_ID3;

int cycle_A1_ID;
int cycle_A2_ID;
int cycle_A3_ID;
int cycle_A4_ID;
int cycle_A5_ID;

int cycle_B1_ID;
int cycle_B2_ID;
int cycle_B3_ID;
int cycle_B4_ID;
int cycle_B5_ID; 

int cycle_C1_ID;
int cycle_C2_ID;
int cycle_C3_ID;
int cycle_C4_ID;
int cycle_C5_ID; 

  
void setup() {
  pinMode(LatchRelay, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  Blynk.connect();

  timer.setInterval(5000L, take_sensor_reading);
  COMPRESSION_ID1 = timer.setTimer(750L, COMPRESSION, 30);
  COMPRESSION_ID2 = timer.setTimer(600L, COMPRESSION, 30);
  COMPRESSION_ID3 = timer.setTimer(500L, COMPRESSION, 30);
  
  Retract_ID = timer.setTimeout(250L, Retract);
  message1_ID = timer.setTimeout(20L, message1);
  message2_ID1 = timer.setTimeout(22500L, message2);
  message2_ID2 = timer.setTimeout(18000L, message2); 
  message2_ID3 = timer.setTimeout(15000L, message2); 

  cycle_A1_ID = timer.setTimeout(20L, cycle_A1);
  cycle_A2_ID = timer.setTimeout(26500L, cycle_A1);
  cycle_A3_ID = timer.setTimeout(53000L, cycle_A1);
  cycle_A4_ID = timer.setTimeout(79500L, cycle_A1);
  cycle_A5_ID = timer.setTimeout(106000L, cycle_A1);
  
  cycle_B1_ID = timer.setTimeout(20L, cycle_B1); 
  cycle_B2_ID = timer.setTimeout(22000L, cycle_B1);
  cycle_B3_ID = timer.setTimeout(44000L, cycle_B1);
  cycle_B4_ID = timer.setTimeout(66000L, cycle_B1);
  cycle_B5_ID = timer.setTimeout(88000L, cycle_B1);

  cycle_C1_ID = timer.setTimeout(20L, cycle_C1);
  cycle_C2_ID = timer.setTimeout(19000L, cycle_C1);
  cycle_C3_ID = timer.setTimeout(38000L, cycle_C1);
  cycle_C4_ID = timer.setTimeout(57000L, cycle_C1);
  cycle_C5_ID = timer.setTimeout(76000L, cycle_C1);

    timer.deleteTimer(COMPRESSION_ID1);
    timer.deleteTimer(COMPRESSION_ID2);
    timer.deleteTimer(COMPRESSION_ID3);
    timer.deleteTimer(Retract_ID);
    timer.deleteTimer(message1_ID); 
    timer.deleteTimer(message2_ID1); 
    timer.deleteTimer(message2_ID2);
    timer.deleteTimer(message2_ID3);

    timer.deleteTimer(cycle_A1_ID); 
    timer.deleteTimer(cycle_A2_ID); 
    timer.deleteTimer(cycle_A3_ID);
    timer.deleteTimer(cycle_A4_ID);
    timer.deleteTimer(cycle_A5_ID);   
    
    timer.deleteTimer(cycle_B1_ID); 
    timer.deleteTimer(cycle_B2_ID); 
    timer.deleteTimer(cycle_B3_ID);
    timer.deleteTimer(cycle_B4_ID);
    timer.deleteTimer(cycle_B5_ID);   

    timer.deleteTimer(cycle_C1_ID); 
    timer.deleteTimer(cycle_C2_ID); 
    timer.deleteTimer(cycle_C3_ID);
    timer.deleteTimer(cycle_C4_ID);
    timer.deleteTimer(cycle_C5_ID);   
  
}

  BLYNK_WRITE(V0)  // Virtual button on V0 to activate chest compressions
{   
  Latch = param.asInt();
  if (Latch == 1 && Flag == 0) {
    Flag = 1;  // Keeps from allowing button press more then once while relay activated
    timer.setTimeout(20L, cycle_A1);
    timer.setTimeout(26500L, cycle_A1);
    timer.setTimeout(53000L, cycle_A1);
    timer.setTimeout(79500L, cycle_A1);
    timer.setTimeout(106000L, cycle_A1);    
    
  } else{ 
            
             timer.deleteTimer(COMPRESSION_ID1);
             timer.deleteTimer(COMPRESSION_ID2);
             timer.deleteTimer(COMPRESSION_ID3);
             timer.deleteTimer(Retract_ID);
             timer.deleteTimer(message1_ID); 
             timer.deleteTimer(message2_ID1); 
             timer.deleteTimer(message2_ID2);
             timer.deleteTimer(message2_ID3);
            
             timer.deleteTimer(cycle_A1_ID); 
             timer.deleteTimer(cycle_A2_ID); 
             timer.deleteTimer(cycle_A3_ID); 
             timer.deleteTimer(cycle_A4_ID); 
             timer.deleteTimer(cycle_A5_ID); 
             lcd1.clear();                                                                                                                                                                                                                                                                                                        //timer.disable(blinkMyLEDon_ID);
             Retract();                                   
  }
}  // END Blynk Function

BLYNK_WRITE(V1)  // Virtual button on V0 to activate chest compressions
{   
  Latch = param.asInt();
  if (Latch == 1 && Flag == 0) {
     // Keeps from allowing button press more then once while relay activated
    timer.setTimeout(20L, cycle_B1);
    timer.setTimeout(22000L, cycle_B1);
    timer.setTimeout(44000L, cycle_B1);
    timer.setTimeout(66000L, cycle_B1);
    timer.setTimeout(88000L, cycle_B1);
    
  } else{ 
            
            timer.deleteTimer(COMPRESSION_ID1);
            timer.deleteTimer(COMPRESSION_ID2);
            timer.deleteTimer(COMPRESSION_ID3);
            timer.deleteTimer(Retract_ID);
            timer.deleteTimer(message1_ID); 
            timer.deleteTimer(message2_ID1); 
            timer.deleteTimer(message2_ID2);
            timer.deleteTimer(message2_ID3); 
            timer.deleteTimer(cycle_B1_ID); 
            timer.deleteTimer(cycle_B2_ID); 
            timer.deleteTimer(cycle_B3_ID);
            timer.deleteTimer(cycle_B4_ID);
            timer.deleteTimer(cycle_B5_ID);
            lcd1.clear();                                                                                                                                                                                                                                                                                                        //timer.disable(blinkMyLEDon_ID);
            Retract();                                   
  }
}  // END Blynk Function


BLYNK_WRITE(V2)  // Virtual button on V0 to activate chest compressions
{   
  Latch = param.asInt();
  if (Latch == 1 && Flag == 0) {
    Flag = 1;  // Keeps from allowing button press more then once while relay activated
    timer.setTimeout(20L, cycle_C1);
    timer.setTimeout(19000L, cycle_C1);
    timer.setTimeout(38000L, cycle_C1);
    timer.setTimeout(57000L, cycle_C1);
    timer.setTimeout(76000L, cycle_C1);
    
  } else{ 
            
           timer.deleteTimer(COMPRESSION_ID1);
           timer.deleteTimer(COMPRESSION_ID2);
           timer.deleteTimer(COMPRESSION_ID3);
           timer.deleteTimer(Retract_ID);
           timer.deleteTimer(message1_ID); 
           timer.deleteTimer(message2_ID1); 
           timer.deleteTimer(message2_ID2);
           timer.deleteTimer(message2_ID3);; 
           timer.deleteTimer(cycle_C1_ID); 
           timer.deleteTimer(cycle_C2_ID); 
           timer.deleteTimer(cycle_C3_ID); 
           timer.deleteTimer(cycle_C4_ID); 
           timer.deleteTimer(cycle_C5_ID); 
            lcd1.clear();                                                                                                                                                                                                                                                                                                        //timer.disable(blinkMyLEDon_ID);
            Retract(); 
                                             
  }
}  // END Blynk Function



void COMPRESSION(){
  
  digitalWrite(LatchRelay, HIGH); // Turn ON RELAY to extend stroke
  timer.setTimeout(250L, Retract);  // Run RELAY OFF routine once in 250ms second to retract the stroke
}  // END Function

void Retract(){
  digitalWrite(LatchRelay, LOW); // Turn OFF RELAY TO STOP COMPRESSION(triggered LOW)
  Flag = 0;  // reset flag after relay disables
}  // END Function

void message1(){
    lcd1.clear();
    lcd1.print(0, 0, "COMPRESSING");
    lcd1.print(0, 1, "STAND CLEAR");
}

void message2(){
    lcd1.clear();
    lcd1.print(0, 0, "CYCLE COMPLETED");
    lcd1.print(0, 1, "BEGIN R.BREATHS");
}

void cycle_A1(){
   timer.setTimeout(20L, message1);
   timer.setTimer(750L, COMPRESSION, 30); //Initiate compression and retraction 30 times
   timer.setTimeout(22500L, message2);
}



void cycle_B1(){
   timer.setTimeout(20L, message1);
   timer.setTimer(600L, COMPRESSION, 30); //Initiate compression and retraction 30 times
   timer.setTimeout(18000L, message2);
}

void cycle_C1(){
   timer.setTimeout(20L, message1);
   timer.setTimer(500L, COMPRESSION, 30); //Initiate compression and retraction 30 times
   timer.setTimeout(15000L, message2);
}



void take_sensor_reading(){
  //nothing to see here
}

void loop() {
  Blynk.run();
  timer.run(); // This keeps checking the timers to see if then need to be processed
}
