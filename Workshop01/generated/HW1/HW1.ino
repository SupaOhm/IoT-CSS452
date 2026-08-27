// HW1 — Homework 1, Problem 1  (instructor's video name: "P1")
// Task: "Do the Example 3 in Lecture Note 3."
//   Adjust the brightness of the LED by rotating the potentiometer.
//
// Circuit (Lecture Note 3, Example 3, slide 35):
//   3v3 --- potentiometer end 1
//   GND --- potentiometer end 2
//   potentiometer wiper --- A0
//   GPIO 17 --- LED long leg / short leg --- 330 --- GND
//
// Board: ThaiEasyElec's ESPino32. Serial baud must be 115200 (Lecture Note 3, slide 19).

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
