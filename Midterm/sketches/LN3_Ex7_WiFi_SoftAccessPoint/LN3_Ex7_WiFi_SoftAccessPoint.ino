#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("Your_SSID", "Your_Password");
  if(result == true) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
  }
}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
