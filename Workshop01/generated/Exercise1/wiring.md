# Exercise1 wiring — Exercise 1 (Lecture Note 3, Example 1)

Source: `Lecture Note 3 - Introduction to ESP32.pdf`, slide 26 (circuit diagram).

## Diagram

```text
        Pin 3v3 of ESP32
              |
             [ ] 10K
              |
              +---------------------> GPIO 34   (ESP32, input only)
              |
             SW        (if pressed, SW is closed)
              |
             GND  (Pin GND of ESP32)


   GPIO 17 ------------+
                       |
                    long leg
                      \ /   LED
                      ---
                    short leg
                       |
                      [ ] 330
                       |
                      GND  (Pin GND of ESP32)
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| 3v3 | top of 10 kΩ resistor | supply for the pull-up |
| GPIO 34 | junction of 10 kΩ and SW | input only; **no internal pull-up available** |
| GND | other side of SW | pressing pulls GPIO 34 to 0 V |
| GPIO 17 | LED long leg (anode) | digital output |
| GND | 330 Ω, from LED short leg (cathode) | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Pull-up resistor | 10 kΩ | slide 26 |
| LED series resistor | 330 Ω | slide 26 |
| Push button | SPST momentary (SW) | slide 26 |
| LED | polarity shown as long leg / short leg | slide 26 |

## Logic

The 10 kΩ resistor is an **external pull-up**: with the switch open, GPIO 34
sits at 3.3 V and reads HIGH. Pressing the switch closes it to GND, so the pin
reads LOW. This is why the sketch turns the LED on when `buttonState == LOW`.

The external resistor is required here: GPIO 34 is an input-only pin on the
ESP32 and has no internal pull-up to enable.
