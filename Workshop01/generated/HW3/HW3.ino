// HW3 — Homework 1, Problem 3  (instructor's video name: "P3")
//
// Task: connect a wire to a touch pin (as in Example 4) and write code so that:
//   1) when ESP32 starts, it connects to your WiFi access point and shows its
//      IP address on the serial monitor (similar to Example 6);
//   2) thereafter, if you touch the wire, ESP32 will restart.
//
// STATUS: NEEDS CLARIFICATION — see QUESTIONS.md.
// The touch threshold below is NOT specified anywhere in the supplied material.
//
// Circuit (Lecture Note 3, Example 4, slide 39):
//   a plain wire from GPIO 32 (a touch-sensor pin). No other components.
//
// Board: ThaiEasyElec's ESPino32. Serial baud must be 115200 (Lecture Note 3, slide 19).
//
// TODO: replace "Your_SSID" / "Your_Password" with your own WiFi credentials.

#include <WiFi.h>

const char* ssid     = "Your_SSID";
const char* password = "Your_Password";

const int touchPin = 32;  // touch-sensor pin, per Example 4 (slide 39)

// TODO: confirm the touch threshold with the instructor.
// Lecture Note 3 gives no threshold value. Slide 40 only shows sample output:
// roughly 38-46 when the wire is NOT touched, and roughly 6-9 when it IS touched.
// The value below sits between those two observed bands but is NOT stated in
// the course material. Verify it against your own board before relying on it.
const int touchThreshold = 20;  // UNCONFIRMED - not from the supplied material

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Task 1: connect to WiFi and show the IP address (as in Example 6, slide 48)
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Task 2: read the touch pin; a LOW value means the wire is being touched
  // (slide 38: touching returns a low value, not touching returns a high value).
  int touchValue = touchRead(touchPin);
  Serial.println(touchValue);

  if (touchValue < touchThreshold) {
    Serial.println("Touched - restarting");
    ESP.restart();  // software reset (slide 43)
  }

  delay(1000);  // same 1 second sampling period as Example 4 (slide 40)
}
