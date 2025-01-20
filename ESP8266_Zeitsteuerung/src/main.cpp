#include <Arduino.h>
#include <ESP8266WiFi.h>



void setup() {
  //LED Kontrolleuchte
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

  //Wlan Einstellungen
  const char* ssid ="KabelBox-2BF8";
  const char* pw ="82644147";
  WiFi.begin(ssid,pw);

  
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(5, LOW);
  }
  
}
  

