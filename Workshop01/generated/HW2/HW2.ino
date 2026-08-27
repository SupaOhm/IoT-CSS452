// HW2 — Homework 1, Problem 2  (instructor's video name: "P2")
// Task: "Do the Example 8 in Lecture Note 3."
//   The serial monitor shows the local time every one second.
//
// No external circuit. ESP32 must reach your WiFi access point to reach the Internet.
// Board: ThaiEasyElec's ESPino32. Serial baud must be 115200 (Lecture Note 3, slide 19).
//
// TODO: replace "Your SSID" / "Your Password" with your own WiFi credentials.
//       The lecture leaves these as placeholders (slide 54); no credentials are
//       supplied anywhere in the course material.

#include <WiFi.h>
#include "time.h"

const char* ssid       = "Your SSID";
const char* password   = "Your Password";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7*3600;      // Thailand is UTC+7 (slide 57)
const int   daylightOffset_sec = 0;      // 0 for Thailand (slide 57)

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  delay(1000);
  printLocalTime();
}
