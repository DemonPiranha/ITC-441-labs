// This is code for a Reed sensor Module

#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

//Sets some global variables
const char* ssid = "Blake-Hotspot";
const char* password = "blakepublic";
WiFiServer server(80);
IPAddress local_IP(192, 168, 157, 186);
IPAddress dns(192, 168, 91, 254);
IPAddress gateway(192, 168, 91, 254);
IPAddress subnet(255, 255, 255, 0);
int change = 0;

// MQTT configs
const char* mqtt_server = "192.168.157.117";
const char* mqtt_topic = "garage_system";
const char* clientID = "reedSensor";

// Sets up the Wifi and MQTT client
WiFiClient wifiClient;
PubSubClient MQTTclient(wifiClient);


//Setup for pins, starts wifi, and makes MQTT connection.
void setup() {

  //Setup serial and all LED outputs then clears the LEDs
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, INPUT_PULLUP);

  //Sets the static IP to the set variables
  if (!WiFi.config(local_IP, dns, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  //Using the Wifi library, begin connecting to the set network, and provide status updates.
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println();
  Serial.println("(( WiFi connected ))");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP());

  // Connect to MQTT Broker
  MQTTclient.setServer(mqtt_server, 1883);
  if (MQTTclient.connect(clientID)) {
    MQTTclient.subscribe(mqtt_topic);
    Serial.println("Connected to MQTT Broker!");
    delay(500);
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.print("MQTT State: ");
  Serial.print(MQTTclient.state());
}

void loop() {

  // Sets up a client object that sets this device as a client. Let's MQTT do it's loop.
  MQTTclient.loop();

  // Prints the value of the D1 pin for debugging
  Serial.println(digitalRead(D1));

  // Reads the Reed sensor value and sends an open or closed command.
  // The garage door is open when the circuit open and closed when the circuit is closed.
  if (digitalRead(D1) == 0) {
    if (change == 1) {

    } else {
      // This repetition ensures that all devices receive the command.
      MQTTclient.publish(mqtt_topic, "closed");
      delay(100);
      MQTTclient.publish(mqtt_topic, "closed");
      delay(100);
      MQTTclient.publish(mqtt_topic, "closed");
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      change = 1;
    }
  }
  else {
    if (change == 2) {

    } else {
      // This repetition ensures that all devices receive the command.
      MQTTclient.publish(mqtt_topic, "open");
      delay(100);
      MQTTclient.publish(mqtt_topic, "open");
      delay(100);
      MQTTclient.publish(mqtt_topic, "open");
      delay(100);
      digitalWrite(LED_BUILTIN, LOW); 
      change = 2;
    }
  }

}
