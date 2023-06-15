#include <Wire.h>
#include <ArduinoJson.h>

// Stores all logic to determine the magnetic field direction
class magnetic_detection{
  public:
    // Constructor, assigns the pin
    magnetic_detection(int pin_in){
      pin=pin_in;
      pinMode(pin, INPUT);
    }
    
    // Gets an average of the field
    float get_raw_field() {
      float output=0;
      for(int i=0;i<80;i++){
        output=output+analogRead(pin);
      }
      return output/80;
    }
    
    // Calibrates the sensor
    void calibrate(){
      float min_value=1023;
      float max_value=0;
      for(int i=0;i<200;i++){
        float magnetic_field=get_raw_field();
        if(magnetic_field<min_value){
          min_value=magnetic_field;
        }
          if(magnetic_field>max_value){
            max_value=magnetic_field;
          }
        }
        min_max[0]=min_value;
        min_max[1]=max_value;
      }
  
    // Outputs the magnetic field direction when called
    int result(){
      float magnetic_field=get_raw_field();
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
  
  private:
    float min_max[2];
    int pin;
};

// Stores all logic to find the age
class age_detection{
  public:
    // Constructor, assigns the pin
    age_detection(int pin_in){
      pin=pin_in;
      pinMode(pin, INPUT);
    }
    
    // Detects whether an alien is pulsating
    bool detect_age(){
      while (total < 1000000) {
        if (digitalRead(pin) == LOW) {
          first = micros();
          delayMicroseconds(800);
          start = micros();
          while (total < 8000) {
            if (digitalRead(pin) == LOW) {
              second = micros();
              return true;
            }
            total = micros() - start;
          }
        } 
        else {
          total = micros() - start;
        }
      }
      return false;
    }
    
    // Outputs the age when called
    int result(){
      if(detect_age()){
        int tmp=second-first;
        total=0;
        start=micros();
        first=0;
        second=0;
        return tmp/10;
      }
      else{
        return 0;
      }
    }
  
  private:
    unsigned long total = 0;
    unsigned long start = micros();
    unsigned long first = 0;
    unsigned long second = 0;
    int pin;
};

// Stores all logic to find the name
class name_detection{
  public:
    // Constructor, assignt the pin
    name_detection(int pin_in){
      pin=pin_in;
      pinMode(pin,INPUT);
    }

    String result(){
        String name=Serial.readStringUntil('#');
        if(name.length()==3){
          return name;
        }   
    }

  private:
    int pin;
};

age_detection age(5);
magnetic_detection magnet(A0);
name_detection name(0);

char buffer[32];

void send_data(){
  Wire.write(buffer);
}

void run_calibration(int master_input){
  input = Wire.read();
  if (input==0){
    magnet.calibrate();
  }
}

int encodeToASCII(const String& input) {
    int encodedValue = 0;
    
    for (char c : input) {
        encodedValue = (encodedValue * 1000) + static_cast<int>(c);
    }
    
    return encodedValue;
}

void setup() {
  pinMode(0, INPUT);
  Serial.begin(600);
  Wire.begin(1);
  Wire.onReceive(run_calibration);
  Wire.onRequest(send_data);
}

void loop() {
  DynamicJsonDocument data(32);

  String name_output;
  if(Serial.available()){
    name_output=name.result();
  }
  else{
    name_output="No";
  }
  
  
  data["N"]=encodeToASCII(name_output);
  data["A"]=age.result();
  data["M"]=magnet.result();
  serializeJson(data,buffer,sizeof(buffer));
}
