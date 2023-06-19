/**************************************************************************************************************************************
Fyrryx UDP/Wire Protocol

Data is encoded into JSON format before sending/recieving, except for pings ("ping" is answered by "pong").
JSON will look something like this: {"key1":"value1","key2":"value2"}.
To encode/decode in python, "json" is used
To encode/decode in CPP, "ArduinoJson.h" is used (located in /headers/ArduinoJson.h)
 ***************************************************************************************************************************************/
#include <receiver.h>

void Receiver::wireSetup() {
    Wire.begin();
    sendWirePacket(CALIBRATE_FUNCTION);
    Serial.println("Wire Initialized");
}

std::unordered_map<std::string, double> Receiver::handleUDPPacket() {
    
    // Recieve and process UDP packets
    std::unordered_map<std::string, double> data = {};

    int packetSize = udp.parsePacket();
    if (packetSize) {
        char buffer[BUFFER_SIZE]; 
        int len = udp.read(buffer, sizeof(buffer));
        if (len > 0) {
            buffer[len] = '\0'; // Add null-terminator to create a valid C-string
            
            // Process the received data as needed
            if (buffer[0] == '{') {
                data = decodeJSON(buffer);
                Serial.println(buffer);
            }
            else {
                Serial.print("Received data: ");
                Serial.println(buffer);
            }

            // Send a "pong" when data is received
            udp.beginPacket(udp.remoteIP(), udp.remotePort());
            udp.write("pong");
            udp.endPacket();
            
        }
    }

    return data;
}

std::unordered_map<std::string, double> Receiver::decodeJSON(const char* jsonString) {
    // Create a StaticJsonDocument to hold the JSON data with a capacity of 200 bytes
    // Use StaticJsonDocument to minimize dynamic memory allocation
    StaticJsonDocument<200> jsonDocument;

    // Deserialize the JSON string into the JsonDocument
    DeserializationError error = deserializeJson(jsonDocument, jsonString);
    
    // Create an unordered map to store the JSON values
    std::unordered_map<std::string, double> jsonData;

    // Check if parsing succeeded
    if (error) {
        Serial.print(F("JSON parsing failed! Error code: "));
        Serial.println(error.c_str());
        return jsonData;
    }

    // Access the values in the JSON document and store them in the unordered map
    for (const auto& kv : jsonDocument.as<JsonObject>()) {
        if (kv.value().is<double>()) {
            std::string key = kv.key().c_str();
            double value = kv.value().as<double>();
            jsonData[key] = value;
        }
    }

    // Return the unordered map
    return jsonData;
}

std::string Receiver::decodeFromASCII(int encodedValue) {
    std::string decodedString;
    
    while (encodedValue > 0) {
        int asciiValue = encodedValue % 1000;
        decodedString = static_cast<char>(asciiValue) + decodedString;
        encodedValue /= 1000;
    }
    
    return decodedString;
}

void Receiver::sendUDPPacket(std::string name, int age, int magnetic_field) {
    DynamicJsonDocument jsonDoc(BUFFER_SIZE);

    jsonDoc["Name"] = name;
    jsonDoc["Age"] = age;
    jsonDoc["MagneticField"] = magnetic_field;

    char buffer[BUFFER_SIZE];
    serializeJson(jsonDoc, buffer, sizeof(buffer));

    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write(reinterpret_cast<const uint8_t*>(buffer), strlen(buffer));
    udp.endPacket();
}

std::unordered_map<std::string, double> Receiver::handleWirePacket() {
    std::unordered_map<std::string, double> data = {};
    Wire.requestFrom(address, WIRE_BUFFER_SIZE);

    if (Wire.available()) {
        char buffer[WIRE_BUFFER_SIZE];
        int bytesRead = Wire.readBytes(buffer, WIRE_BUFFER_SIZE);

         if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; 
            data = decodeJSON(buffer);
         }
    }

    return data;
}

void Receiver::sendWirePacket(int message) {
    Wire.beginTransmission(address);
    Wire.write(message);
    Wire.endTransmission();
}