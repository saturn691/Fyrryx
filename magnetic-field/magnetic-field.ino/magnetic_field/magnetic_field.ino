//if positive field detected, return 2
//if negative field detected, return 0
//if no field detected, return 1;
int magnetic_detection(int input_pin){
  float output = analogRead(input_pin);
  if(output>700){
    return 2;
  }
  if(output<300){
    return 0;
  }
  else{
    return 1;
  }
}
