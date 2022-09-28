#include <ESP8266WiFi.h>

//Sets some global variables
const char* ssid = "Blake-Hotspot";
const char* password = "blakepublic";
WiFiServer server(80);
unsigned long startMillis;
bool cycle = false;

//Setup for pins and clears all of them
void setup() {
  
  //Setup serial and all LED outputs then clears the LEDs
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  allLightsOff();

  //Using the Wifi library begin connecting to the set network and provide status updates.
  Serial.print("Connecting to ");
  Serial.println(ssid);
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

  server.begin();
  Serial.println("((( Server Started )))");
  greenLight();
  delay(500);
  allLightsOff();
}

void loop() {
  
  // Sets up a client object for connections to the webpage. Constantly checks if a request is made
  WiFiClient client = server.available();
  if (client) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN, HIGH);
    while (!client.available()) {
      delay(10);
    }
  }
  client.setTimeout(100);          

  //This section reads for inbound requests made by the web client. If any one of the endpoints is hit the corresponding code will trigger.
  String req = client.readStringUntil('\r');
  if (req.indexOf("/off") != -1) {
    cycle = false;
    allLightsOff();               
  }
  if (req.indexOf("/green") != -1) {
    cycle = false;
    greenLight();
  }
  if (req.indexOf("/yellow") != -1) {
    cycle = false;
    yellowLight();
  }
  if (req.indexOf("/red") != -1) {
    cycle = false;
    redLight();
  }
  if (req.indexOf("/cycle") != -1) {
    cycle = true;
    startMillis = millis();
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
  client.println("<!doctype html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>");
  client.println("<title>Aurdunio Stoplight</title>");
  client.println("</head>");

  client.println("<center>");
  client.println("<body>");
  client.println("<header>");
  client.println("<h1>Arduino Stoplight Lab 2</h1>");
  client.println("</header>");
  
  client.print("<h2>Red Light</h2>");
  client.print("<a href='http://");
  client.print(WiFi.localIP());
  client.print("/red' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");
  
  client.print("<h2>Yellow Light</h2>");
  client.print("<a href='http://");
  client.print(WiFi.localIP());
  client.print("/yellow' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  client.print("<h2>Green Light</h2>");
  client.print("<a href='http://");
  client.print(WiFi.localIP());
  client.print("/green' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  client.print("<h2>All Lights Off</h2>");
  client.print("<a href='http://");
  client.print(WiFi.localIP());
  client.print("/off' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");

  client.print("<h2>Cycle Light</h2>");
  client.print("<a href='http://");
  client.print(WiFi.localIP());
  client.print("/cycle' class='btn btn-block btn-lg btn-primary' role='button'><br>Turn on<br><br></a><br>");


  client.println("<span>Created by Blake Porter</span>");
  client.println("</body>");
  client.println("</center>");
  client.println("</html>");
}

//These functions directly control the lights so that the loop can call these at any time to change the light that is on.
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
