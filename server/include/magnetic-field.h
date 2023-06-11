#ifndef _MAGNETIC_FIELD_h
#define _MAGNETIC_FIELD_h

#include <Arduino.h>
// Place any other includes here

int getMagneticField(int magneticFieldPin, float min_max[2]);
void calibrate(int magneticFieldPin, float (& min_max)[2]);
float getRawField(int magneticFieldPin);

#endif