// P1 — Exercise 1: Introduction to ESP32
// Task: "Do the Example 1 in Lecture Note 3."
//   Press the switch   -> LED on
//   Not press the switch -> LED off
//
// Circuit (Lecture Note 3, Example 1, slide 26):
//   3v3 --- 10K --+--- GPIO 34 (input only, no internal pull-up)
//                 |
//                 SW --- GND        (pressing closes SW, so pressed reads LOW)
//   GPIO 17 --- LED long leg / short leg --- 330 --- GND
//
// Board: ThaiEasyElec's ESPino32. Serial baud must be 115200 (Lecture Note 3, slide 19).

// set pin numbers
const int buttonPin = 34;  // the push button pin
const int ledPin =  17;    // the LED pin

// variable for storing the pushbutton status
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW
  if (buttonState == LOW) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off
    digitalWrite(ledPin, LOW);
  }
}
