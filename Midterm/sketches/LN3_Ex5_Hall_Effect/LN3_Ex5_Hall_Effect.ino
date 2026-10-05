void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Hall Effect Test");
}

void loop() {
  Serial.println(hallRead());  // Read the hall effect
  delay(1000);
}
