#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

//starte server
ESP8266WebServer server(80);

//Definiere konstante Einstellungen
IPAddress local_ip(192,168,0,120);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
const char* ssid ="KabelBox-2BF8";
const char* pw ="82644147";
long long number = 99;



//Empfange die Datei
void handleInput(){
  DynamicJsonDocument doc(76);
  number = doc.as<long long>();
  if(number == 99){
    server.send(400, "text/plain", "FEHLER");
  }else{
    server.send(200, "text/plain", "OK");
  }
}


void setup() {
//LED Kontrolleuchte
pinMode(5, OUTPUT);
digitalWrite(5, HIGH);

//mit WLAN verbinden
WiFi.begin(ssid,pw);
  if(WiFi.status() == WL_CONNECTED && WiFi.config(local_ip, gateway, subnet)){
    digitalWrite(5, LOW);
  }
  //Starte Server
  server.begin();
}

void loop() {
  server.on("/input", HTTP_POST, handleInput);
  if(number==99){
    digitalWrite(5, HIGH);
  }else{
    digitalWrite(5,LOW);
  }
  
  
}
  

