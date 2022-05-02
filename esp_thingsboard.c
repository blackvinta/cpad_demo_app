#include <Arduino.h>
#include "ThingsBoard.h"
#include "DHT.h"
#include <ESP8266WiFi.h>

// Digital pin connected to the DHT sensor
#define DHTPIN 14  

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)   

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold sensor readings
float temp;
float hum;

#define WIFI_AP             "Chrome Cast"
#define WIFI_PASSWORD       "krishna@0000"

#define TOKEN               "EYkuUmfQQBk3H3b0G1zA"
#define THINGSBOARD_SERVER  "192.168.8.109"

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;

void setup() 
{
  // initialize serial for debugging
  Serial.begin(SERIAL_DEBUG_BAUD);
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  InitWiFi();
  dht.begin();
}

void loop() 
{
  delay(10000);

  if (WiFi.status() != WL_CONNECTED) 
  {
    reconnect();
  }

  if (!tb.connected()) 
  {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) 
    {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Sending data...");

  // Uploads new telemetry to ThingsBoard using MQTT
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  tb.sendTelemetryInt("Humidity", hum); 
  tb.sendTelemetryInt("Temperature", temp);
  tb.loop();
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() 
{
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) 
  {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
