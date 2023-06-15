#ifndef _RECEIVER_h
#define _RECEIVER_h

#include <Arduino.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <string>
#include <unordered_map>

#define BUFFER_SIZE 255
#define WIRE_BUFFER_SIZE 32
#define CALIBRATE_FUNCTION 0

class Receiver {
private:
    int address;

    std::unordered_map<std::string, double> decodeJSON(const char* jsonString);
public:
    WiFiUDP udp;

    Receiver(int address) : address(address) {};
    
    void wireSetup();
    std::unordered_map<std::string, double> handleUDPPacket();
    void sendUDPPacket(std::string name, int age, int magnetic_field);
    void handleWirePacket();
    void sendWirePacket(int message);
};

#endif