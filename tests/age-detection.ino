void setup() {
  pinMode(5, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Declaration of variables
  unsigned long total = 0;
  unsigned long start = micros();
  unsigned long first = 0;
  unsigned long second = 0;
  bool detect = 0;

  // Find the age
  while (detect == 0 && total < 1000000) {
    if (digitalRead(5) == LOW) {
      first = micros();
      delayMicroseconds(800);
      start = micros();
      while (total < 8000 && detect == 0) {
        if (digitalRead(5) == LOW) {
          second = micros();
          detect = 1;
        }
        total = micros() - start;
      }
    } else {
      detect = 0;
      total = micros() - start;
    }
  }
  int difference = second - first;
  // Return the age
  if (detect) {
    Serial.print("The age of the alien is ");
    Serial.println(difference/10);
  } else {
    Serial.println("Counting failed");
  }
}
