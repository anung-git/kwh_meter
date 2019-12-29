#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>  
#include "Pzem.h"

char auth[] = "YheyDPOxSeTVWIXO1MVxOg6W73fPtCo4";
char ssid[] = "ardinista";
char pass[] = "ardiasta";
int roling = 0;

SoftwareSerial pzemSerial(D1, D2); // (RX,TX)   
Pzem R(2, pzemSerial);
//Pzem S(1, pzemSerial);
//Pzem T(3, pzemSerial);
BlynkTimer timer;


void myTimerEvent(){
//  if (roling==0){
    R.baca();
    Blynk.virtualWrite(V1 , R.getTegangan());  
    Blynk.virtualWrite(V2 , R.getArus());
    Blynk.virtualWrite(V3 , R.getWatt());
    Blynk.virtualWrite(V4 , R.getKwh());
    Blynk.virtualWrite(V5 , R.getFrekuensi());
    Blynk.virtualWrite(V6 , R.getPowerFaktor());
    Blynk.virtualWrite(V7 , R.getAlarm());
    // Please don't send more that 10 values per second.
//  }
//  if(roling==1){
//    S.baca();
//    Blynk.virtualWrite(V8 , S.getTegangan());  
//    Blynk.virtualWrite(V9 , S.getArus());
//    Blynk.virtualWrite(V10 , S.getWatt());
//    Blynk.virtualWrite(V11 , S.getKwh());
//    Blynk.virtualWrite(V12 , S.getFrekuensi());
//    Blynk.virtualWrite(V13 , S.getPowerFaktor());
//    Blynk.virtualWrite(V14 , S.getAlarm());
//    // Please don't send more that 10 values per second.
//    
//  }
//  if(roling==2){
//    T.baca();
//    Blynk.virtualWrite(V15 , T.getTegangan());  
//    Blynk.virtualWrite(V16 , T.getArus());
//    Blynk.virtualWrite(V17 , T.getWatt());
//    Blynk.virtualWrite(V18 , T.getKwh());
//    Blynk.virtualWrite(V19 , T.getFrekuensi());
//    Blynk.virtualWrite(V20 , T.getPowerFaktor());
//    Blynk.virtualWrite(V21 , T.getAlarm());
//    // Please don't send more that 10 values per second.
//  }
//  if(++roling==3)roling=0;
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pzemSerial.begin(9600);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
