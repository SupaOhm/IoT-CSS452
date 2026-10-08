const int potPin = A0; //Potentiometer pin
const int ledPin = 17;  // LED pin

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

// Variable for storing the potentiometer value
int potValue = 0;
int ledValue = 0;

void setup() {
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  ledValue = map(potValue, 0, 4095, 0, 255);

  // changing the LED brightness with PWM
  ledcWrite(ledChannel, ledValue);
}
