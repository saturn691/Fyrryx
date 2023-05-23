#include <headers/receiver.h>

void Receiver::handleUDPPacket() {
// Recieve and process UDP packets
int packetSize = udp.parsePacket();
if (packetSize) {
    char buffer[255];
    int len = udp.read(buffer, sizeof(buffer));
    if (len > 0) {
    buffer[len] = '\0'; // Add null-terminator to create a valid C-string
    
    // Process the received data as needed
    Serial.print("Received data: ");
    Serial.println(buffer);

    // Send a "pong" if pinged
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write("Pong!");
    udp.endPacket();
    }
}
}

void Receiver::decodeJSON(const char* jsonString) {
    // Create a StaticJsonDocument to hold the JSON data
    // Adjust the capacity based on the size of your JSON data
    // Use StaticJsonDocument to minimize dynamic memory allocation
    // The capacity is specified in bytes
    StaticJsonDocument<200> jsonDocument;

    // Deserialize the JSON string into the JsonDocument
    DeserializationError error = deserializeJson(jsonDocument, jsonString);

    // Check if parsing succeeded
    if (error) {
        Serial.print(F("JSON parsing failed! Error code: "));
        Serial.println(error.c_str());
        return;
    }

    // Access the values in the JSON document
    double movement = jsonDocument["Movement"];
    double turning = jsonDocument["Turning"];
    double gas = jsonDocument["Gas"];
    double reverse = jsonDocument["Reverse"];
    int boost = jsonDocument["Boost"];
    int brake = jsonDocument["Brake"];

    // Do something with the extracted values
    Serial.print(F("Movement: "));
    Serial.println(movement);
    Serial.print(F("Turning: "));
    Serial.println(turning);
    Serial.print(F("Gas: "));
    Serial.println(gas);
    Serial.print(F("Reverse: "));
    Serial.println(reverse);
    Serial.print(F("Boost: "));
    Serial.println(boost);
    Serial.print(F("Brake: "));
    Serial.println(brake);
}
