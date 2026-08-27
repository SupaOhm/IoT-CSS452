// P1 — Exercise 2: ESP32 Multitasking and Deep Sleep
// Task: "Do the Example 2 in Lecture Note 4."
//   Task 1 (timing-based): LED1 on for 2 seconds, off for 2 seconds.
//   Task 2 (event-based):  LED2 is toggled when we press and release the switch,
//                          using a pin-change interrupt.
//
// Circuit (Lecture Note 4, Example 2, slide 15 - same circuit as Example 1):
//   3v3 --- 10K --+--- GPIO 34 (input only, no internal pull-up)
//                 |
//                 SW --- GND     (pressing closes SW, giving LOW at the pin)
//   GPIO 16 --- LED1 long leg / short leg --- 330 --- GND
//   GPIO 17 --- LED2 long leg / short leg --- 330 --- GND
//
// Board: ThaiEasyElec's ESPino32.

// set pin numbers
const int buttonPin = 34;  // the push button pin
const int led1Pin = 16;    // the LED1 pin
const int led2Pin = 17;    // the LED2 pin

// variable for storing the pushbutton status
int led1State = LOW;
int led2State = LOW;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 second

void toggle() {
  led2State = !led2State;
  digitalWrite(led2Pin, led2State);
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggle, FALLING);
}

void loop() {
  // To turn on/off the LED1
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (led1State == LOW) {
      led1State = HIGH;
    } else {
      led1State = LOW;
    }
    digitalWrite(led1Pin, led1State);
  }
}
