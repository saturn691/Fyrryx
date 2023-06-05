// Uncomment lines 131-132 for testing in main.ino

#include <headers/magnetic-field.h>

// Return -1 if the magnetic field is down, 0 if none, 1 if up
int getMagneticField(int magneticFieldPin) {
    float output;
    output=analogRead(magneticFieldPin);
    return output;
}