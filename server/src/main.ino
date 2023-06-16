/**************************************************************************************************************************************
  This code is TOP SECRET and only members of Fyryyx should be able to access this
 ***************************************************************************************************************************************/
#define USE_WIFI_NINA         false
#define USE_WIFI101           true

#define BACK_RIGHT_MOTOR 3 // This is the pins that we use
#define FRONT_RIGHT_MOTOR 4
#define FRONT_LEFT_MOTOR 6
#define BACK_LEFT_MOTOR 13
#define MOTOR_ENABLE_PIN 2 
#define BUZZER_PIN 8
#define magneticFieldPin A0

#include <WiFiWebServer.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <receiver.h>
#include <RCMovementHandler.h>
#include <buzzer.h>
#include <string>

const char ssid[] = "EEERover";
const char pass[] = "exhibition";
const int groupNumber = 7; // Set your group number to make the IP address constant - only do this on the EEERover network
const int port = 6969;

Receiver receiver(1);
WiFiWebServer server(port);
RCMovementHandler movementHandler(BACK_RIGHT_MOTOR, FRONT_RIGHT_MOTOR, FRONT_LEFT_MOTOR, BACK_LEFT_MOTOR); 
ezBuzzer buzzer(BUZZER_PIN);

void connectToWiFi() {
    Serial.println(F("\nStarting Web Server"));
    // Check WiFi shield is present
    if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println(F("WiFi shield not present"));
        while (true);
    }

    // Configure the static IP address if group number is set
    if (groupNumber)
        WiFi.config(IPAddress(192,168,0,groupNumber+1));

    // attempt to connect to WiFi network
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

  	// Establish UDP connection at port 6969
  	receiver.udp.begin(6969);
    receiver.wireSetup();
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(BACK_RIGHT_MOTOR, OUTPUT);
	pinMode(FRONT_RIGHT_MOTOR, OUTPUT);
	pinMode(FRONT_LEFT_MOTOR, OUTPUT);
	pinMode(BACK_LEFT_MOTOR, OUTPUT);
	pinMode(MOTOR_ENABLE_PIN, OUTPUT);
	pinMode(magneticFieldPin, INPUT);

	digitalWrite(LED_BUILTIN, 0);

	Serial.begin(9600);

  while (!Serial && millis() < 10000);
  connectToWiFi();

	digitalWrite(MOTOR_ENABLE_PIN, 1);
	analogWrite(BACK_RIGHT_MOTOR, 128);
	analogWrite(FRONT_RIGHT_MOTOR, 128);
	analogWrite(FRONT_LEFT_MOTOR, 128);
	analogWrite(BACK_LEFT_MOTOR, 128);
}

// Call the server polling function in the main loop
void loop()
{
	if (WiFi.status() != WL_CONNECTED) {
		init();
	}

	std::unordered_map<std::string, double> packetData = receiver.handleUDPPacket();
	std::unordered_map<std::string, double> sensorData = receiver.handleWirePacket();
	
	std::string name;
	if (!name.empty()) {
		name = Receiver::decodeFromASCII(sensorData["N"]);
	}
	else name = "None";

	if (!sensorData.empty()) {
		receiver.sendUDPPacket(name, sensorData["A"], sensorData["M"]);
	}

	buzzer.loop();

	if (!packetData.empty()) {
		double x = packetData["Movement X"];
		double y = packetData["Movement Y"];
		double turning = packetData["Turning"];

		movementHandler.move(x, y, turning);
		
		if (packetData["Horn"]) {
			buzzer.beep(100,100);
		};
		if (packetData["Intro"]) {
			buzzer.playIntro(); 
		}
		if (packetData["Chorus"]) {
			buzzer.playChorus();
		}
	}
}
