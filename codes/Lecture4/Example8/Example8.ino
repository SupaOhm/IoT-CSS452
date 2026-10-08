#define Threshold 40 // higher value, higer sensitivity
RTC_DATA_ATTR int bootCount = 0;

void callback(){
  //placeholder callback function
}
void setup(){
  // Declare the touch wake up - use GPIO32 (TOUCH9)
  touchAttachInterrupt(32, callback, Threshold);
  esp_sleep_enable_touchpad_wakeup();

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
