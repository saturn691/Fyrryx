#ifndef _RECEIVER_h
#define _RECEIVER_h

#include <Arduino.h>
#include <WiFiUdp.h>
#include <headers/ArduinoJson.h>

class Receiver {
public:
    WiFiUDP udp;
    
    void handleUDPPacket();
    void decodeJSON(const char* jsonString);
};

#endif