const int potPin = A0; //Potentiometer pin

// Variable for storing the potentiometer value
int Value = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading potentiometer value
  Value = analogRead(potPin);
  Serial.println(Value);
  delay(1000);
}
