#include <WiFi.h>
#include <WebServer.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include "DHT11_ESP32.h"

DHT11_ESP32 dht(13);
float x , y ;


const char* ssid = "Abhishek";
const char* password = "NewPassword";

WiFiMulti wifiMulti;

WebServer server(80);

int data[4];

void handleRoot() {
  String webPage = " " ;//<script> setTimeout('location.reload(true);', 1000);</script>";
  String Json;

  // Allocate JsonBuffer
  StaticJsonBuffer<1024> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["Temperature"] = data[0];
  root["Humidity"] = data[1];
  root["Knock"] = data[2];
  root["Sound"] = data[3];


  root.printTo(Json);  //Store JSON in String variable
  server.send(200, "text/html", Json + webPage);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

  wifiMulti.addAP(ssid, password); // Connect to Wi-Fi network

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin(); //Start web server
  Serial.println("HTTP server started");
}

void loop() {
  //Handle Client requests
  float temperature_c = dht.getTEMP();
  float humidity = dht.getHUM();
  Serial.println(temperature_c);
  Serial.println(humidity);
  data[1]= humidity ;
  data[0] = temperature_c ;
  data[2] = read_sound(); // should return Decible value as response 
  data[3] = read_knock(); // Set this value as 0 or 1 as the array is an integer array 
  delay(2000);



  server.handleClient();
}
