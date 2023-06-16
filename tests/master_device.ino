#include <Wire.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(600);
  while (!Serial);
  Wire.begin();
  Serial.println("Master Initialized!");
  Wire.beginTransmission(1);
  Wire.write(0);
  Wire.endTransmission();
}
void loop() {
  Wire.requestFrom(1, 32);
  if (Wire.available()) {
    char buffer[32]; 
    int bytesRead = Wire.readBytes(buffer, 32);
    Serial.println(buffer);
  } 
  delay(500);
}
