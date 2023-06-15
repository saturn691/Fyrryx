// Outputs the averaged readings
float get_raw_field() {
  float output=0;
  for(int i=0;i<1;i++){
    output=output+analogRead(A0);
    }
  return output/10;
}
// Finds the standard deviation from the given input array
double std_dev(double values[100], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
      sum=sum+values[i];    
    } 
    double mean = (double)sum/(double)n; 
    double square_difference = 0; 
    for (int i = 0; i < n; i++) {
        square_difference=square_difference+((values[i]-mean)*(values[i]-mean)); 
    }
    double variance=(float)square_difference/n; 
    return sqrt(variance);
}
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  // Finds the time it takes to get raw results
  float start = micros();
  get_raw_field();
  float end = micros();
  Serial.print("The execution time was ");Serial.print(end-start);Serial.print(" microseconds.");
  Serial.println("");
  // Finds the standard deviation of 500 raw values
  double values[100];
  for(int i=0;i<100;i++){
    values[i]=get_raw_field();
  }
  double standard_deviation=std_dev(values,100);
  Serial.print("The precision was ");Serial.print(standard_deviation);
  Serial.println("");
}
void loop() {
}
