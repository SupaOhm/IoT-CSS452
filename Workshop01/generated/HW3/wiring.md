# HW3 wiring — Homework 1 Problem 3 (Lecture Note 3, Example 4)

Source: `Lecture Note 3 - Introduction to ESP32.pdf`, slide 39.

## Diagram

```text
   +-------------------+
   |      ESP32        |
   |  (ESPino32 board) |
   |                   |
   |         GPIO 32   |------------ wire (free end, left bare to touch)
   |                   |
   +-------------------+
             ||
        Micro USB ============ your computer
                               (power + serial monitor)

   No resistor, no LED, no breadboard components.
   The free end of the wire IS the touch sensor.
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| GPIO 32 | one end of a single wire | capacitive touch pin; other end left free |
| — | — | no other connections required |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Wire | length not stated | slide 39 |

## Notes

- Slide 37 lists the ESP32 capacitive touch pins as GPIO 0, 2, 4, 12, 13, 14,
  15, 27, 32 and 33. Example 4 uses **GPIO 32**, so this task uses GPIO 32.
- Slide 38: `touchRead(pin)` returns an integer 0–1023. Not touching gives a
  **high** value; touching gives a **low** value.
- Slide 40 sample output: about 38–46 untouched, about 6–9 touched.
- No pull-up or pull-down resistor is shown or required; the pin is used as a
  capacitive sensor, not a digital input.
