#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>  
#include "Pzem.h"

char auth[] = "YheyDPOxSeTVWIXO1MVxOg6W73fPtCo4";
char ssid[] = "ardinista";
char pass[] = "ardiasta";
int roling = 0;

int rMax,sMax,tMax,bzr;

SoftwareSerial pzemSerial(D1, D2); // (RX,TX)   
Pzem R(3, pzemSerial);
Pzem S(2, pzemSerial);
Pzem T(1, pzemSerial);
BlynkTimer timer;
BlynkTimer timer2;

void pzemRead(){
  R.baca();
  S.baca();
  T.baca();
}


void myTimerEvent(){
  if (roling==0){
    R.baca();
    Blynk.virtualWrite(V1 , R.getTegangan());  
    Blynk.virtualWrite(V2 , R.getArus());
    Blynk.virtualWrite(V3 , R.getWatt());
    Blynk.virtualWrite(V4 , R.getKwh());
    Blynk.virtualWrite(V5 , R.getFrekuensi());
    Blynk.virtualWrite(V6 , R.getPowerFaktor());
    Blynk.virtualWrite(V7 , R.getAlarm());
    // Please don't send more that 10 values per second.
  }
  if(roling==1){
    S.baca();
    Blynk.virtualWrite(V8 , S.getTegangan());  
    Blynk.virtualWrite(V9 , S.getArus());
    Blynk.virtualWrite(V10 , S.getWatt());
    Blynk.virtualWrite(V11 , S.getKwh());
    Blynk.virtualWrite(V12 , S.getFrekuensi());
    Blynk.virtualWrite(V13 , S.getPowerFaktor());
    Blynk.virtualWrite(V14 , S.getAlarm());
    // Please don't send more that 10 values per second.
    
  }
  if(roling==2){
    T.baca();
    Blynk.virtualWrite(V15 , T.getTegangan());  
    Blynk.virtualWrite(V16 , T.getArus());
    Blynk.virtualWrite(V17 , T.getWatt());
    Blynk.virtualWrite(V18 , T.getKwh());
    Blynk.virtualWrite(V19 , T.getFrekuensi());
    Blynk.virtualWrite(V20 , T.getPowerFaktor());
    Blynk.virtualWrite(V21 , T.getAlarm());
    // Please don't send more that 10 values per second.
    Serial.println( R.getTegangan());
    Serial.println( R.getArus());
    Serial.println( R.getWatt());
    Serial.println( R.getKwh());    
    Serial.println( R.getFrekuensi());
    Serial.println( R.getPowerFaktor());
  }
  if(++roling==3)roling=0;
  bzr=0;
  if(R.getWatt()>rMax){
    digitalWrite(D5,HIGH);
    bzr++;
  }
  else{
    digitalWrite(D5,LOW);
  }

  if(S.getWatt()>rMax){
    digitalWrite(D6,HIGH);
    
    bzr++;
  }
  else{
    digitalWrite(D6,LOW);
  }

  if(T.getWatt()>rMax){
    digitalWrite(D7,HIGH);
    
    bzr++;
    
  }
  else{
    digitalWrite(D7,LOW);
  }

  if(bzr>0){
    digitalWrite(D8,HIGH);
  }
  else{
    digitalWrite(D8,LOW);
  }
}


BLYNK_WRITE(V22){
  rMax = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V23){
  sMax= param.asInt(); // assigning incoming value from pin V1 to a variable

}
BLYNK_WRITE(V24){
  tMax = param.asInt(); // assigning incoming value from pin V1 to a variable

}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pzemSerial.begin(9600);
  timer.setInterval(1000L, myTimerEvent);
  timer2.setInterval(100L, pzemRead);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
