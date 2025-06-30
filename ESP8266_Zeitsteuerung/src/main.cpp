//Ausarbeitung der Methode wie die eingehenden Daten verarbeitet werden sollen
/*
---Tag---       An Aus
Montag      : 0800 0830
Diesntag    : 0700 0800 
Mittwoch    : 1200 1250
Donnerstag  : 0945 1025
Freitag     : 1100 1110
Samstag     : 0900 1200
Sonntag     : 0900 1200
*/
#include <time.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

String eingabe  = "";
int zeiten[14];
int verschiebung = 1;
int flag = 0;

time_t kalender;
tm zeiten_tm;
int stunde = 0;
int minute = 0;
int sekunde = 0;
int A = 0;

//Rechnet den String der Zeiten in integer um und trennt sie
//0 = 48, 9 = 57 Zeichen als int (alternativ einfach - '0')
//ACHTUNG: String endet und beginnt mit ""
void splitstring(){
    for(int b=0; b!=14; ++b){
      zeiten[b] = (eingabe[verschiebung] - '0') * 1000 +
                  (eingabe[verschiebung+1] - '0') * 100 +
                  (eingabe[verschiebung+2] - '0') * 10 +
                  (eingabe[verschiebung+3] - '0');
    verschiebung +=4;
    Serial.println(zeiten[b]);
    }
  }

//Empfange die Datei
void handleInput(){
    String body = server.arg("plain");
    eingabe = server.arg("plain");
    Serial.println("JSON Vorgang wurde ausgeführt.");
    Serial.println(eingabe);
    server.send(200);
    Serial.println("Anfrage angekommen");
    A = 1;
    splitstring();
}

//Setzt die aktuelle Uhrzeit
  void gettime(){
    time(&kalender); 
    localtime_r(&kalender, &zeiten_tm);
    stunde = zeiten_tm.tm_hour + 1;
    minute = zeiten_tm.tm_min;
    sekunde = zeiten_tm.tm_sec;
    Serial.print(stunde);
    Serial.print(":");
    Serial.println(minute);
  }


 void setup(){
    pinMode(5, OUTPUT);
    Serial.begin(9600);
    WiFi.begin("KabelBox-2BF8", "82644147");
    while(WiFi.status() != WL_CONNECTED){
      Serial.println("Verbinde...");
      delay(1000);
    }
    Serial.println("WLAN verbunden");
    Serial.println(WiFi.localIP());
    gettime();
    server.on("/comms", HTTP_POST, handleInput);
    delay(2000);
    server.begin();
    Serial.println("Server gestartet");
 }



 void loop() {
  //Macht eine Schleife bis eine Eingabe getätigt wurde
  while(A != 1){
    Serial.println("Warte auf eingabe");
    delay(10000);
    server.handleClient();
  }
  delay(1000);
  ++sekunde;
  if(sekunde >= 60){
    sekunde = 0;
    ++minute;
  }
  if (minute >= 60) {
    minute = 0;
    ++stunde;
  }
  if (stunde >= 24){
    stunde = 0;
  }

  Serial.print(stunde);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(sekunde);

  for(int i = 0; i!=12; i +=2){
    //Anschalten
    if(stunde*100+minute == zeiten[i]){
      digitalWrite(5, HIGH);
      break;
    }
    //Ausschalten
    if(stunde*100+minute == zeiten[i+1]){
      digitalWrite(5, LOW);
      break;
    }
  }
 }

 void test(){
  while(A != 1){
    Serial.println("Warte auf eingabe");
    delay(10000);
    server.handleClient();
  }
  delay(100000);
 }