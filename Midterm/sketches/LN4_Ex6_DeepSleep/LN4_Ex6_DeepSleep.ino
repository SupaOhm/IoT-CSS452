void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor
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
