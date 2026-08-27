# HW1 wiring — Homework 1 Problem 1 (Lecture Note 3, Example 3)

Source: `Lecture Note 3 - Introduction to ESP32.pdf`, slide 35 (circuit diagram).

## Diagram

```text
   Pin 3v3 of ESP32
         |
         +-------+
                 |
            [potentiometer]
                 |<--- wiper ------------> A0   (ESP32 analog input)
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
| 3v3 | potentiometer outer terminal | reference top of the divider |
| GND | potentiometer other outer terminal | reference bottom |
| A0 | potentiometer wiper (middle) | reads 0–4095 over 0–3.3 V |
| GPIO 17 | LED long leg (anode) | PWM output via channel 0 |
| GND | 330 Ω, from LED short leg (cathode) | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Potentiometer | value not stated in the material | slide 35 |
| LED series resistor | 330 Ω | slide 35 |

## Notes

- Slide 28: the 0–3.3 V input on an analog pin maps to integers 0–4095, which is
  why the sketch maps `0..4095` to the 8-bit duty range `0..255`.
- Slide 32: GPIO 17 is within the listed PWM-capable pins (GPIO 0–19, 21–23,
  25–27, 32–33).
- The potentiometer's resistance value is not given anywhere in the supplied
  material, so none is asserted here.
