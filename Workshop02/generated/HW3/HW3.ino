// HW3 — Homework 2, Problem 3  (instructor's video name: "P3")
//
// Revise Example 5 in Lecture Note 4 by adding a second switch "SW1" on GPIO 26.
//   When ESP32 is on (as in Example 5):
//     - The serial monitor shows which core is running.
//     - LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
//     - LED2 is on if we press the switch "SW"; otherwise, LED2 is off.
//   (New) Pressing "SW1" sends the ESP32 to deep sleep, using a pin-change
//         interrupt (similar to Example 2).
//   (New) After 15 seconds the ESP32 wakes by timer wakeup (similar to Example 7).
//
// Circuit (CSS452 - Homework 2.pdf, Problem 3 diagram):
//   3v3 --- 10K --+--- GPIO 34 ;  SW  --- GND      (SW,  pressing gives LOW)
//   3v3 --- 10K --+--- GPIO 26 ;  SW1 --- GND      (SW1, pressing gives LOW)
//   GPIO 16 --- LED1 long leg / short leg --- 330 --- GND
//   GPIO 17 --- LED2 long leg / short leg --- 330 --- GND
//
// Board: ThaiEasyElec's ESPino32. Serial baud 115200.

#define TIME_TO_SLEEP 15   // wake up 15 seconds after entering deep sleep
RTC_DATA_ATTR int bootCount = 0;

// set pin numbers
const int buttonPin = 34;      // the push button pin (SW)
const int sleepButtonPin = 26; // the deep-sleep button pin (SW1)
const int led1Pin = 16;        // the LED1 pin
const int led2Pin = 17;        // the LED2 pin

// variable for storing the pushbutton status
int buttonState = LOW;
int led1State = LOW;
int led2State = LOW;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 second

// Set by the SW1 interrupt; acted on in loop(). Keeping the handler this small
// follows the taught approach of a minimal interrupt function (Example 2).
volatile bool sleepRequested = false;

void requestSleep() {
  sleepRequested = true;
}

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
  delay(1000); //Take some time to open up the Serial Monitor
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  pinMode(buttonPin, INPUT);
  pinMode(sleepButtonPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  // (New) pressing SW1 requests deep sleep, via a pin-change interrupt
  attachInterrupt(digitalPinToInterrupt(sleepButtonPin), requestSleep, FALLING);

  // (New) declare the timer wake up, before going to deep sleep
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*1000000);

  // Declare the tasks and assign the cores.
  xTaskCreatePinnedToCore(TimerLED, "TimerLED", 1024, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(SwitchLED, "SwitchLED", 1024, NULL, 1, NULL, 1);
}

void loop() {
  if (sleepRequested) {
    Serial.println("SW1 pressed ... Now, in the deep sleep mode.");
    delay(100); // let the serial output leave the buffer before the CPU powers down
    esp_deep_sleep_start();
  }
}
