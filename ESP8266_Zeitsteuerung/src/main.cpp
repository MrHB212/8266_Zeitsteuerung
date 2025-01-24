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
String input = "";


//Empfange die Datei
void handleInput(){
    String body = server.arg("plain");
    input = server.arg("plain");
    Serial.println("JSON Vorgang wurde ausgeführt.");
    Serial.println(input);
    server.send(200);
    Serial.println("Anfrage angekommen");
}


void setup() {
Serial.begin(9600);
//LED Kontrolleuchte
//pinMode(5, OUTPUT);
//digitalWrite(5, HIGH);

//mit WLAN verbinden
WiFi.begin(ssid,pw);
while(WiFi.status() != WL_CONNECTED){
  Serial.println("Warte auf WLAN");
  delay(1000);
  }
  Serial.println(WiFi.localIP());
  digitalWrite(5, LOW);
  delay(2000);

//Starte Server
server.on("/comms", HTTP_POST, handleInput);
delay(2000);
server.begin();
Serial.println("Server gestartet");
}

void loop() {
  server.handleClient();
  
}
  

