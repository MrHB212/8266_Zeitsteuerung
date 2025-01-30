//https://werner.rothschopf.net/201802_arduino_esp8266_ntp.htm
//https://www.tutorialspoint.com/c_standard_library/time_h.htm

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <time.h>

//starte server
ESP8266WebServer server(80);

//Definiere Konstanten und Variablen
IPAddress local_ip(192,168,0,120);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
const char* ssid ="KabelBox-2BF8";
const char* pw ="82644147";
String input = "";
time_t calendar; //enthält Kalenderzeit
tm time_date;    //enthält Zeit und Datum
int stunde = 0;
int minute = 0;


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
pinMode(5, OUTPUT);
digitalWrite(5, LOW);

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
  time(&calendar); //Speichert die aktuelle Zeit
  localtime_r(&calendar, &time_date); //Speichert die aktuelle Zeit in tm-Struktur
  stunde = time_date.tm_hour+1; //UTC+1 entspricht deutsche Zeit
  minute = time_date.tm_min;
  Serial.print(stunde);
  Serial.print(":");
  Serial.print(minute);
  Serial.print("\n");
  if(minute==30){
    digitalWrite(5, HIGH);
  }
  delay(20000);
}
  

