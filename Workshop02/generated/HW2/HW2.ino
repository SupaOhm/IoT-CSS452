// HW2 — Homework 2, Problem 2  (instructor's video name: "P2")
// Task: "Do the Example 9 in Lecture Note 4."
//   The serial monitor shows that ESP32 is in the deep sleep.
//   Pressing the switch (SW) wakes ESP32 up.
//
// Circuit (Lecture Note 4, Example 9, slide 57):
//   3v3 --- 10K --+--- GPIO 32
//                 |
//                 SW --- GND     (pressing closes SW, giving LOW at the pin)
//   No LEDs in this problem.
//
// ext0 wakes the board when GPIO 32 goes LOW, i.e. when SW is pressed.
//
// Board: ThaiEasyElec's ESPino32. Serial baud 115200.

RTC_DATA_ATTR int bootCount = 0;

void setup(){
  // Declare the ext0 wake up - use GPIO32
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_32,LOW);

  // Tasks to do before going to deep sleep
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("ESP32 will enter the deep sleep in 10 s.");
  delay(10000);

  //Go to sleep now
  Serial.println("... Now, in the deep sleep mode.");
  esp_deep_sleep_start();
  Serial.println("This sentence will never be printed.");
}

void loop(){
  //ESP32 will never come here.
}
