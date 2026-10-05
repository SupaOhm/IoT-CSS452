const int touchPin = 32;  // touch-sensor pin
const int ledPin = 17;    // the LED pin

// TODO: set from your own readings. The lecture gives no threshold;
// slide 40 only shows about 38-46 untouched and 6-9 touched.
const int Threshold = 20;

int Value = 0;

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Value = touchRead(touchPin);
  Serial.println(Value);
  if (Value < Threshold) {
    // touching the wire returns a low value
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}
