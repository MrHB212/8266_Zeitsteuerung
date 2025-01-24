# POST und GET Anfragen in Verbindung mit ESP8266
# Potenzieller Ersatz für HTML Variante ?

import requests

requests.post("HTTP://192.168.0.77/comms", json = "Test")
print("POST gesendet")
