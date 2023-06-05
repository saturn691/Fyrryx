#ifndef _RECEIVER_h
#define _RECEIVER_h

#include <Arduino.h>
#include <WiFiUdp.h>
#include <headers/ArduinoJson.h>
#include <string>
#include <unordered_map>

class Receiver {
public:
    WiFiUDP udp;
    
    std::unordered_map<std::string, double> handleUDPPacket();
    std::unordered_map<std::string, double> decodeJSON(const char* jsonString);
    void sendUDPPacket(std::string name, int age, int magnetic_field); 
};

#endif