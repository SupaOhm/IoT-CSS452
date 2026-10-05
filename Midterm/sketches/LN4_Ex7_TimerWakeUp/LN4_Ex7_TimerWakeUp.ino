#define TIME_TO_SLEEP 5
RTC_DATA_ATTR int bootCount = 0;

void setup(){
  // Declare the timer wake up
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*1000000);

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
