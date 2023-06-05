#include <headers/magnetic-field.h>

// Calibrates the Hall Effect sensor
void calibrate(int magneticFieldPin, float (& min_max)[2]){
  float min_value=1023;
  float max_value=0;
  for(int i=0;i<500;i++){
    float magnetic_field=getRawField(magneticFieldPin);
    if(magnetic_field <min_value){
      min_value=magnetic_field;
    }
    if(magnetic_field>max_value){
      max_value=magnetic_field;
    }
  }
  min_max[0]=min_value;
  min_max[1]=max_value;
}

// Gets the a noise-stabilized field value
float getRawField(int magneticFieldPin) {
  float output=0;
  for(int i=0;i<50;i++){
    output=output+analogRead(magneticFieldPin);
  }
  return output/50;
}

// Return -1 if the magnetic field is down, 0 if none, 1 if up
int getMagneticField(int magneticFieldPin, float min_max[2]) {
    float magnetic_field=getRawField(A0);
    if(magnetic_field>min_max[1]){
      return 1;
    }
    else if(magnetic_field<min_max[0]){
        return -1;
    }
    else{
        return 0;
    }
}