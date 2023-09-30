#include <WiFi.h>
#include <WebServer.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include "DHT11_ESP32.h"
const int sampleWindow = 50;

DHT11_ESP32 dht(13);
float x , y ;


const char* ssid = "Abhishek";
const char* password = "NewPassword";

WiFiMulti wifiMulti;

WebServer server(80);

int data[2];

void handleRoot() {
  String webPage = " " ;//<script> setTimeout('location.reload(true);', 1000);</script>";
  String Json;

  // Allocate JsonBuffer
  StaticJsonBuffer<1024> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
//  root["Temperature"] = data[0];
//  root["Humidity"] = data[1];
  root["Knock"] = data[0];
  root["Sound"] = data[1];


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
//  float temperature_c = dht.getTEMP();
//  float humidity = dht.getHUM();
//  Serial.println(temperature_c);
//  Serial.println(humidity);
//  data[1] = humidity ;
//  data[0] = temperature_c ;
  data[0] = read_sound(); // should return Decible value as response
  data[1] = read_knock(); // Set this value as 0 or 1 as the array is an integer array
  delay(2000);



  server.handleClient();
}
int read_knock()
{
  const int tap = 25;
  pinMode(tap, INPUT);
  y = digitalRead(tap); //read input form the Tsp Sensor
  if (y == 1)
  {
    return 1;
    delay(500);
  }
  if (y == 0)  {
    return 0;
    delay(100);
  }
}

int read_sound()
{
  unsigned int sample;
  const int SENSOR_PIN = 34;
  pinMode (SENSOR_PIN, INPUT);
  unsigned long startMillis = millis();                  // Start of sample window
  float peakToPeak = 0;                                  // peak-to-peak level

  unsigned int signalMax = 0;                            //minimum value
  unsigned int signalMin = 4095;                         //maximum value

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(SENSOR_PIN);                    //get reading from microphone
    if (sample < 4095)                                  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;                           // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;                           // save just the min levels
      }
    }
  }

  peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
  int db = map(peakToPeak, 20, 900, 49.5, 90);         //calibrate for deciBels
  /*
    Serial.print("Loudness: ");
    Serial.print(db);
    Serial.println("dB");*/

  delay(200);
  return db;
}
