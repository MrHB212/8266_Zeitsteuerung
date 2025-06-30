# POST und GET Anfragen in Verbindung mit ESP8266
# Potenzieller Ersatz für HTML Variante ?

import requests
montag = "18001900"
dienstag = "18051905"
mittwoch = "18101910"
donnerstag = "18151915"
freitag = "18201920"
samstag = "18251925"
sonntag = "18301930"
requests.post("HTTP://192.168.0.77/comms", json = montag+dienstag+mittwoch+donnerstag+freitag+samstag+sonntag)
print("POST gesendet")
