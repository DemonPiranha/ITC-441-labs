// This is code for a Ultrasonic sensor Module

#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <HCSR04.h> // include the Ultrasonic sensor library "HCSR04 ultrasonic sensor by gamegine v2.0.3"
#include <MedianFilterLib.h> // Midian Filter Lib by Luis Llamas

//Sets some global variables
const char* ssid = "Blake-Hotspot";
const char* password = "blakepublic";
WiFiServer server(80);
IPAddress local_IP(192, 168, 157, 185);
IPAddress dns(192, 168, 91, 254);
IPAddress gateway(192, 168, 91, 254);
IPAddress subnet(255, 255, 255, 0);
long rawUltraDistance;
int change = 0;
bool state = false;

HCSR04 ultraSonic(D1, D2);  //Class for HCSR04 sets (trig pin , echo pin)
MedianFilter<int> medianFilter(5); // Sets up Median Filter Object

// MQTT configs
const char* mqtt_server = "192.168.157.117";
const char* mqtt_topic = "garage_system";
const char* clientID = "ultrasonic1";

// Sets up the Wifi and MQTT client
WiFiClient wifiClient;
PubSubClient MQTTclient(wifiClient);

//Setup for pins, clears all of them, starts MQTT connection.
void setup() {

  //Setup serial and all LED outputs then clears the LEDs off
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

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
  MQTTclient.setCallback(ReceivedMessage);
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

  // Tells the MQTT client code to do what it needs to do  
  MQTTclient.loop();  

  // Each time the loop repeats ultraDistance will be set to the distance received from the sensor
  rawUltraDistance = ultraSonic.dist();
  delay(60);

  //Filters the raw distance data to have a smoother data stream 
  int filteredUltraDistance = medianFilter.AddValue(rawUltraDistance);

  //If the distance is farther than 55cm and the Garage is open
  if (filteredUltraDistance > 55 && state == true) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 1){
    }
    else {
      Serial.print(filteredUltraDistance);
      Serial.println(" cm");
      MQTTclient.publish(mqtt_topic, "green");
      change = 1;
    }
  }
  //If the distance is between 50cm and 22cm and the Garage is open
  else if (filteredUltraDistance <= 50 && filteredUltraDistance >= 22 && state == true) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 2){
    }
    else {
      Serial.print(filteredUltraDistance);
      Serial.println(" cm");
      MQTTclient.publish(mqtt_topic, "yellow");
      change = 2;
    }
  }
  //If the distance is between 20cm and 12cm and the Garage is open
  else if (filteredUltraDistance <= 20 && filteredUltraDistance >= 12 && state == true) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 3){
    }
    else {
      Serial.print(filteredUltraDistance);
      Serial.println(" cm");
      MQTTclient.publish(mqtt_topic, "red");
      change = 3;
    }
  }
  //If the distance is closer than 10 cm and the Garage is open
  else if (filteredUltraDistance <= 10 && state == true) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 4){
    }
    else {
      change = 4;
      MQTTclient.publish(mqtt_topic, "tooClose");
    }
  }

}


//MQTT message handler. Used by the callback function to receive messages from MQTT
void ReceivedMessage(char* topic, byte* payload, unsigned int payloadLength) {

  // Convert the char* topic to a String
  String topicFull = (String)topic;
  String message = "";
  // Convert the payload to a usable String by iterating through each character to create the full message string
  for (int i = 0; i < payloadLength; i++) {
    message += (char)payload[i];
  }
  //Serial.println(message);

  //Checks if the topic received matches the one originally subscribed to.
  //Then it parses the inputs of the message and triggers the events required that match the command.
  if (topicFull == (String)mqtt_topic) {
    // If the garage door sensor is open activate the ultrasonic sensor
    if (message == "open") {
      Serial.println("open");
      state = true;
    // If the garage door sensor is closed deactivate the ultrasnoinc sensor and prevent it from sending commands
    } else if (message == "closed"){
      Serial.println("closed");
      state = false;
    }
  }
}
