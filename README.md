# Arduino_PoeleMQTT
Gestion d'un poele à granulé avec un ESP8266, un relais et MQTT

Gestion poêle à granulé contact sec avec : 
+ Wemos D1 mini (ESP8266)
+ 1 relais 
+ 1 led du statut de l'alimentation
+ 1 led du statut du relais

Le programme ecoute sur un topic MQTT et se déclenche en fonction de la valeur reçue
 
Source :     https://www.sla99.fr
  
Basé sur :   https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
