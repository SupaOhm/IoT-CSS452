// set pin numbers
const int buttonPin = 34;  // the push button pin
const int led1Pin = 16;    // the LED1 pin
const int led2Pin = 17;    // the LED2 pin

// variable for storing the pushbutton status
int buttonState = LOW;
int led1State = LOW;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 second

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  // To turn on/off the LED1
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    if (led1State == LOW) {
      led1State = HIGH;
    } else {
      led1State = LOW;
    }
    digitalWrite(led1Pin, led1State);
  }

  // To turn on/off the LED2
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) { // Press the switch
    digitalWrite(led2Pin, HIGH); // LED2 on
  } else {
    digitalWrite(led2Pin, LOW); // LED2 off
  }
}
