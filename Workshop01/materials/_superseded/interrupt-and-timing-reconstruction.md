# Reconstruction: ESP32 interrupt and timing exercise

**Source status:** reconstructed from the previous conversation, not an original instructor file. Replace with the lecture PDF or assignment sheet if possible.

## Stated requirements

- LED1: switch on/off every 2 seconds using `millis()`.
- LED2: toggle using a button-triggered interrupt.
- Button: GPIO 34; external 10 kΩ pull-up to 3.3 V; button connects GPIO 34 to GND when pressed.
- LED1: GPIO 16.
- LED2: GPIO 17.
- Use an interrupt on the button's `FALLING` edge.
- Example names/style: `buttonPin`, `led1Pin`, `led2Pin`, `led1State`, `led2State`, `previousMillis`, `interval`, and `toggle()`.
