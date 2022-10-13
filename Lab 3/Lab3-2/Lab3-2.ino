#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "HCSR04.h" // include the Ultrasonic sensor library "HCSR04 ultrasonic sensor by gamegine v2.0.3"

//Sets some global variables
const char* ssid = "Blake-Hotspot";
const char* password = "blakepublic";
WiFiServer server(80);
IPAddress local_IP(192, 168, 91, 185);
IPAddress dns(192, 168, 91, 254);
IPAddress gateway(192, 168, 91, 254);
IPAddress subnet(255, 255, 255, 0);
String serverName = "http://192.168.91.184";   // IP address path of server device
long ultraDistance;
int change = 0;
HCSR04 ultraSonic(D1, D2);  //Class for HCSR04 sets (trig pin , echo pin)


//Setup for pins and clears all of them
void setup() {

  //Setup serial and all LED outputs then clears the LEDs
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  //Sets the static IP to the set variables
  if (!WiFi.config(local_IP, dns, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  //Using the Wifi library, begin connecting to the set network, start webserver and provide status updates.
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

  server.begin();
  Serial.println("((( Server Started )))");
}

void loop() {

  // Sets up a client object that sets this device as a client. http is also set as a HTTPClient
  WiFiClient client;
  HTTPClient http;

  //Serial.println(change);
  Serial.print(ultraDistance);
  Serial.println(" cm");
  int httpResponseCode;

  //each time the loop repeats ultraDistance will be set to the distance received from the sensor
  ultraDistance = ultraSonic.dist();
  delay(60);

  //If the distance is farther than 55cm
  if (ultraDistance > 55) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 1){
    }
    else {
      Serial.print(ultraDistance);
      Serial.println(" cm");
      http.begin(client, serverName + "/green");
      httpResponseCode = http.GET();
      change = 1;
    }
  }
  //If the distance is between 50cm and 22cm
  else if (ultraDistance <= 50 && ultraDistance >= 22) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 2){
    }
    else {
      Serial.print(ultraDistance);
      Serial.println(" cm");
      http.begin(client, serverName + "/yellow");
      httpResponseCode = http.GET();
      change = 2;
    }
  }
  //If the distance is between 20cm and 12cm
  else if (ultraDistance <= 20 && ultraDistance >= 12) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 3){
    }
    else {
      Serial.print(ultraDistance);
      Serial.println(" cm");
      http.begin(client, serverName + "/red");
      httpResponseCode = http.GET();
      change = 3;
    }
  }
  //If the distance is closer than 10 cm
  else if (ultraDistance <= 10) {
    //If the distance is still within the range then nothing will happen so that http requests are not sent unnecessarily.
    if(change == 4){
    }
    else {
      http.begin(client, serverName + "/tooClose");
      httpResponseCode = http.GET();
      change = 4;
    }
  }

}
