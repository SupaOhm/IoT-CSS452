# P3 wiring — Homework 2 Problem 3

Source: `CSS452 - Homework 2.pdf`, Problem 3 diagram (page 1). This is
Example 5's circuit with one switch added.

## Diagram

```text
   Pin 3v3 of ESP32
     |          |
    [ ] 10K    [ ] 10K
     |          |
     +--> GPIO 34    +--> GPIO 26
     |               |
    SW              SW1        (pressing closes the switch, giving LOW)
     |               |
    GND             GND   (Pin GND of ESP32)


   GPIO 16 ------+                     GPIO 17 ------+
                 |                                   |
              long leg                            long leg
                \ /  LED1                           \ /  LED2
                ---                                 ---
              short leg                          short leg
                 |                                   |
                [ ] 330                             [ ] 330
                 |                                   |
                GND                                 GND
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| 3v3 | top of both 10 kΩ resistors | supply for both pull-ups |
| GPIO 34 | junction of its 10 kΩ and SW | input only; controls LED2 |
| GPIO 26 | junction of its 10 kΩ and SW1 | **new**; pin-change interrupt → deep sleep |
| GND | other side of SW and of SW1 | pressing pulls the pin to 0 V |
| GPIO 16 | LED1 long leg (anode) | timing task, Core 0 |
| GPIO 17 | LED2 long leg (anode) | switch task, Core 1 |
| GND | 330 Ω from each LED short leg | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Pull-up resistors | 10 kΩ × 2 | Homework 2 Problem 3 diagram |
| LED series resistors | 330 Ω × 2 | Homework 2 Problem 3 diagram |
| Push buttons | SPST momentary × 2 (SW, SW1) | Homework 2 Problem 3 diagram |

## Difference from P1

Only SW1 and its 10 kΩ pull-up on GPIO 26 are new. Everything else is the
Example 5 circuit unchanged, so you can add one switch to the P1 breadboard
rather than rebuilding it.

## Notes

- Both switches are wired the same way, so both read HIGH at rest and LOW when
  pressed. The interrupt on SW1 therefore triggers on `FALLING`.
- Slide 14 of Lecture Note 4: every GPIO except GPIO6–GPIO11 can be an interrupt
  pin, so GPIO 26 is valid.
- GPIO 26 needs the external pull-up shown in the diagram; no internal pull-up
  is assumed.
