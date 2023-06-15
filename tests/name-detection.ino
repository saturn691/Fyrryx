void setup(){
  // Initialise pin modes and serial
  pinMode(0, INPUT);
  Serial.begin(600);
}
 
// Use UART to automatically decode the name
String get_name(){
  String name = Serial.readStringUntil('#');
  return name;
}

void loop(){
  // If data is available, retrieve it using get_name()
  if(Serial.available()){
    String alien = get_name();
    // Reduce noise
    if(alien.length() == 3){
      Serial.println(alien);
    }
  }
}
