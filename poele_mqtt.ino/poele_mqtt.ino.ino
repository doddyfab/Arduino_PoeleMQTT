/*
  Gestion poêle à granulé contact sec
  avec : 
     - Wemos D1 mini (ESP8266)
     - 1 relais 
     - 1 led du statut de l'alimentation
     - 1 led du statut du relais

  Le programme ecoute sur un topic MQTT et se déclenche en fonction de la valeur reçue
 
  Source :     https://www.sla99.fr
  Basé sur :   https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
  Date : 2019-10-13

  Changelog : 
  13/10/2019  v1    version initiale

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid =               "xxxxx";
const char* password =           "xxxxx";
const char* mqtt_server =        "xxxxx";
const int   mqtt_port =          1883;
const char* mqtt_user =          "user";
const char* mqtt_password =      "password";
char* topic_poele =              "maison/salon/poele";

WiFiClient espClient;
PubSubClient client(espClient);

#define  relayPin  4    //D2
#define  ledPin    16   //D0

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
  }

}

void reconnect(char* topic) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_password)) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect(topic_poele);
  }
  client.loop();
}
