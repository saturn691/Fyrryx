// Global variables
int counter=0;
float min_max[2];

// Finds the raw field
float getMagneticField(int magneticFieldPin) {
  float output=0;
  for(int i=0;i<80;i++){
    output=output+analogRead(magneticFieldPin);
  }
  return output/80;
}

// Calibration function
void calibrate(int magneticFieldPin, float (& min_max)[2]){
  float min_value=1023;
  float max_value=0;
  for(int i=0;i<500;i++){
    float magnetic_field=getMagneticField(magneticFieldPin);
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

// Outputs the final result
int get_magnetic_field(){
  float magnetic_field=getMagneticField(A0);
  if(magnetic_field>min_max[1]){
    counter++;
      return 1;
  }
  else if(magnetic_field<min_max[0]){
    counter++;
    return -1;
  }
  else{
    return 0;
  }
}

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  // Finds the time calibration took
  float calibration = millis();
  calibrate(A0, min_max);
  float calibration2 = millis();
  Serial.println("Calibration took ");Serial.print(calibration2-calibration);Serial.print("ms");
  // Finds the number of errors per second
  float time = millis();
  for(int i=0;i<5000;i++){
    get_magnetic_field();
  }
  float time2 = millis();
  Serial.println("There where ");Serial.print(counter/((time2-time)/1000));Serial.print("errors per second");
}

void loop() {
  // To find the range
  int magnetic_field=get_magnetic_field();
  Serial.println(magnetic_field);
}
