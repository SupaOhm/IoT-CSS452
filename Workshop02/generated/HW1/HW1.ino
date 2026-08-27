// HW1 — Homework 2, Problem 1  (instructor's video name: "P1")
// Task: "Do the Example 5 in Lecture Note 4."
//   The serial monitor shows which core is running.
//   LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
//   LED2 is on if we press the switch "SW"; otherwise, LED2 is off.
//
// TimerLED  is pinned to Core 0, SwitchLED is pinned to Core 1, so the two tasks
// run on different cores simultaneously (Lecture Note 4, slide 34).
//
// Circuit (Lecture Note 4, slide 34 - same circuit as Example 1):
//   3v3 --- 10K --+--- GPIO 34 (input only, no internal pull-up)
//                 |
//                 SW --- GND     (pressing closes SW, giving LOW at the pin)
//   GPIO 16 --- LED1 long leg / short leg --- 330 --- GND
//   GPIO 17 --- LED2 long leg / short leg --- 330 --- GND
//
// Board: ThaiEasyElec's ESPino32. Serial baud 115200.

// set pin numbers
const int buttonPin = 34;  // the push button pin
const int led1Pin = 16;    // the LED1 pin
const int led2Pin = 17;    // the LED2 pin

// variable for storing the pushbutton status
int buttonState = LOW;
int led1State = LOW;
int led2State = LOW;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 second

void TimerLED(void * parameter){
  for (;;) {
    Serial.print("TimerLED() running on core ");
    Serial.println(xPortGetCoreID());
    delay(100);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (led1State == LOW) {
        led1State = HIGH;
      } else {
        led1State = LOW;
      }
    }
    digitalWrite(led1Pin, led1State);
  }
  vTaskDelete(NULL);
}

void SwitchLED(void * parameter) {
  for (;;) {
    Serial.print("SwitchLED() running on core ");
    Serial.println(xPortGetCoreID());
    delay(100);
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) { // Press the switch
      digitalWrite(led2Pin, HIGH); // LED2 on
    } else {
      digitalWrite(led2Pin, LOW); // LED2 off
    }
  }
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  xTaskCreatePinnedToCore(TimerLED, "TimerLED", 1024, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(SwitchLED, "SwitchLED", 1024, NULL, 1, NULL, 1);
}

void loop() {
}
