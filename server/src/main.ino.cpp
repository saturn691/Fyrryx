# 1 "C:\\Users\\willi\\AppData\\Local\\Temp\\tmpj_4e61oq"
#include <Arduino.h>
# 1 "C:/Users/willi/OneDrive/Documents/Coding Projects/Fyrryx/server/src/main.ino"



#define USE_WIFI_NINA false
#define USE_WIFI101 true

#define BACK_RIGHT_MOTOR 3
#define FRONT_RIGHT_MOTOR 4
#define FRONT_LEFT_MOTOR 6
#define BACK_LEFT_MOTOR 9

#include <WiFiWebServer.h>
#include <WiFiUdp.h>
#include <headers/ArduinoJson.h>
#include <headers/receiver.h>
#include <headers/RCMovementHandler.h>

const char ssid[] = "EEERover";
const char pass[] = "exhibition";
const int groupNumber = 7;

Receiver receiver;
WiFiWebServer server(6969);
RCMovementHandler movementHandler(BACK_RIGHT_MOTOR, FRONT_RIGHT_MOTOR, FRONT_LEFT_MOTOR, BACK_LEFT_MOTOR);
std::unordered_map<std::string, double> data;
void connectToWiFi();
void setup();
void loop();
#line 27 "C:/Users/willi/OneDrive/Documents/Coding Projects/Fyrryx/server/src/main.ino"
void connectToWiFi() {
  Serial.println(F("\nStarting Web Server"));

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }


  if (groupNumber)
    WiFi.config(IPAddress(192,168,0,groupNumber+1));


  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }

  server.begin();

  Serial.print(F("Connected, IP Address @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));


  receiver.udp.begin(6969);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR, OUTPUT);
  pinMode(BACK_LEFT_MOTOR, OUTPUT);

  digitalWrite(LED_BUILTIN, 0);

  Serial.begin(9600);

  while (!Serial && millis() < 10000);
  connectToWiFi();
}


void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  std::unordered_map<std::string, double> packetData = receiver.handleUDPPacket();
  receiver.sendUDPPacket("Hello, world!", 69, 0);
  if (!packetData.empty()) {
    double x = 0.1;
    double y = 0.1;
    double gas = 0.1;

    movementHandler.move(x, y, gas);
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
  }

  Serial.println("Looping...");
}