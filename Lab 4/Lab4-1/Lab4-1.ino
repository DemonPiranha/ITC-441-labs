// This is code for a Stoplight Module

#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

//Sets some global variables
const char* ssid = "Blake-Hotspot";
const char* password = "blakepublic";
WiFiServer server(80);
IPAddress local_IP(192, 168, 157, 184);
IPAddress dns(192, 168, 91, 254);
IPAddress gateway(192, 168, 91, 254);
IPAddress subnet(255, 255, 0, 0);
unsigned long startMillis;
bool cycle = false;
bool tooClose = false;

// MQTT configs
const char* mqtt_server = "192.168.157.117";
const char* mqtt_topic = "garage_system";
const char* clientID = "stoplight";

// Sets up the Wifi and MQTT client
WiFiClient wifiClient;
PubSubClient MQTTclient(wifiClient);

//Setup for pins, clears all of them, starts MQTT connection.
void setup() {
  
  //Setup serial and all LED outputs then clears the LEDs off
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  allLightsOff();

  //Sets Static IP for this device.
  if (!WiFi.config(local_IP, dns, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  //Using the Wifi library begin connecting to the set network and provide status updates.
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  redLight();
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  yellowLight();
  delay(100);
  Serial.println();
  Serial.println("(( WiFi connected ))");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());

  //Starts the http server
  server.begin();
  Serial.println("((( Server Started )))");

  // Connect to MQTT Broker
  MQTTclient.setServer(mqtt_server, 1883);
  MQTTclient.setCallback(ReceivedMessage);
  if (MQTTclient.connect(clientID)) {
    MQTTclient.subscribe(mqtt_topic);
    greenLight();
    delay(500);
    allLightsOff();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    redLight();
  }
  Serial.print("MQTT State: ");
  Serial.print(MQTTclient.state());
}

void loop() {
  
  //Sets up a client object for connections to the webpage. Constantly checks if a request is made
  WiFiClient wifiClient = server.available();
  if (wifiClient) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN, HIGH);
    while (!wifiClient.available()) {
      delay(10);
    }
  }
  wifiClient.setTimeout(100);

  // Tells the MQTT client code to do what it needs to do  
  MQTTclient.loop();     

  //This section reads for inbound requests made by the web client. If any one of the endpoints is hit the corresponding code will trigger.
  String req = wifiClient.readStringUntil('\r');
  if (req.indexOf("/off") != -1) {
    cycle = false;
    tooClose = false;
    allLightsOff();               
  }
  if (req.indexOf("/green") != -1) {
    cycle = false;
    tooClose = false;
    greenLight();
  }
  if (req.indexOf("/yellow") != -1) {
    cycle = false;
    tooClose = false;
    yellowLight();
  }
  if (req.indexOf("/red") != -1) {
    cycle = false;
    tooClose = false;
    redLight();
  }
  if (req.indexOf("/cycle") != -1) {
    cycle = true;
    tooClose = false;
    startMillis = millis();
  }
  if (req.indexOf("/tooClose") != -1) {
    cycle = false;
    tooClose = true;
  }

  if (tooClose == true){
    yellowLight();
    delay(150);
    redLight();
    delay(150);
  }
  
  //Checks if the program is in cycle mode and plays the appropriate light pattern.
  if (cycle == true){
    if ((millis() - startMillis) < 5000 ){
      greenLight();
    }
    if ((millis() - startMillis) > 5000 && (millis() - startMillis) < 8000 ){
      yellowLight();
    }
    if ((millis() - startMillis) > 8000 && (millis() - startMillis) < 13000 ){
      redLight();
    }
    if ((millis() - startMillis) > 13000){
      startMillis = millis();
    }
  }

  //These client.print commands print out the html for the webpage and ultimately generates the page. This allows for the page to be served and interacted with in real time.
  wifiClient.println("<!doctype html>");
  wifiClient.println("<html>");
  wifiClient.println("<head>");
  wifiClient.println("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>");
  wifiClient.println("<title>Aurdunio Stoplight</title>");
  wifiClient.println("</head>");

  wifiClient.println("<center>");
  wifiClient.println("<body>");
  wifiClient.println("<header>");
  wifiClient.println("<h1>Arduino Stoplight Lab 2</h1>");
  wifiClient.println("</header>");
  
  wifiClient.print("<h2>Red Light</h2>");
  wifiClient.print("<a href='http://");
  wifiClient.print(WiFi.localIP());
  wifiClient.print("/red' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");
  
  wifiClient.print("<h2>Yellow Light</h2>");
  wifiClient.print("<a href='http://");
  wifiClient.print(WiFi.localIP());
  wifiClient.print("/yellow' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  wifiClient.print("<h2>Green Light</h2>");
  wifiClient.print("<a href='http://");
  wifiClient.print(WiFi.localIP());
  wifiClient.print("/green' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  wifiClient.print("<h2>All Lights Off</h2>");
  wifiClient.print("<a href='http://");
  wifiClient.print(WiFi.localIP());
  wifiClient.print("/off' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  wifiClient.print("<h2>Cycle Light</h2>");
  wifiClient.print("<a href='http://");
  wifiClient.print(WiFi.localIP());
  wifiClient.print("/cycle' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");


  wifiClient.println("<span>Created by Blake Porter</span>");
  wifiClient.println("</body>");
  wifiClient.println("</center>");
  wifiClient.println("</html>");
}

//These functions directly contol the lights so that the loop can call these at anytime to change the light that is on.
void allLightsOff() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
}

void greenLight() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
}

void yellowLight() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
}

void redLight() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
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

  //Checks if the topic received matches the one originally subscribed to.
  //Then it parses the inputs of the message and triggers the events required that match the command.
  if (topicFull == (String)mqtt_topic) {
    if (message == "green") {
      Serial.println("green");
      cycle = false;
      tooClose = false;
      greenLight();
    } else if (message == "yellow") {
      Serial.println("yellow");
      cycle = false;
      tooClose = false;
      yellowLight();
    } else if (message == "red") {
      Serial.println("red");
      cycle = false;
      tooClose = false;
      redLight();
    } else if (message == "cycle") {
      Serial.println("cycle");
      cycle = true;
      tooClose = false;
      startMillis = millis();
    }
    else if (message == "tooClose") {
      Serial.println("tooClose");
      cycle = false;
      tooClose = true;
    }
    else if (message == "allOff" || message == "closed") {
      delay(200);
      Serial.println("allOff");
      cycle = false;
      tooClose = false;
      allLightsOff();
    }
  }
}
