# P3 wiring — Homework 3 Problem 3 (three LEDs)

Source: `CSS452 - Homework 3.pdf`, Problem 3 schematic (page 1). This circuit is
given by the homework itself, **not** by Lecture Note 5 — the lecture's Section 3
uses GPIO 26 and 27, the homework uses GPIO 16, 17 and 32.

## Diagram

```text
   GPIO 16 ------+           GPIO 17 ------+           GPIO 32 ------+
                 |                         |                         |
              long leg                  long leg                  long leg
                \ /  LED1                 \ /  LED2                 \ /  LED3
                ---                       ---                       ---
              short leg                 short leg                 short leg
                 |                         |                         |
                [ ] 330                   [ ] 330                   [ ] 330
                 |                         |                         |
                GND                       GND                       GND
                        (all three to Pin GND of ESP32)
```

## Pin table

| ESP32 pin | Connects to | Web page button |
| --- | --- | --- |
| GPIO 16 | LED1 long leg (anode) | `GPIO 16 - State …` |
| GPIO 17 | LED2 long leg (anode) | `GPIO 17 - State …` |
| GPIO 32 | LED3 long leg (anode) | `GPIO 32 - State …` |
| GND | 330 Ω from each LED short leg | — |

## Components

| Part | Value | Source |
| --- | --- | --- |
| LED series resistors | 330 Ω each | Homework 3 Problem 3 schematic |
| LEDs | 3 × standard indicator LED | Homework 3 Problem 3 schematic |

## Difference from Exercise1

Same topology, one more LED, different pins:

| | `Exercise1` (Section 3) | `P3` (Homework 3) |
| --- | --- | --- |
| LED1 | GPIO 26 | GPIO 16 |
| LED2 | GPIO 27 | GPIO 17 |
| LED3 | — | GPIO 32 |

All three homework pins are ordinary output-capable GPIOs, so `pinMode(…,
OUTPUT)` and `digitalWrite()` work on each exactly as they do on GPIO 26/27.

## Not part of the circuit

The three buttons are on the web page, not on the breadboard. The ESP32 and the
browser must be on the same Wi-Fi network (Lecture Note 5, slides 40 and 43).
