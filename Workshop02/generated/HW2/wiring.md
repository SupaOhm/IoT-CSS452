# HW2 wiring — Homework 2 Problem 2 (Lecture Note 4, Example 9)

Source: `Lecture Note 4 - ESP32 - Multitasking and Deep Sleep.pdf`, slide 57.

## Diagram

```text
        Pin 3v3 of ESP32
              |
             [ ] 10K
              |
              +---------------------> GPIO 32   (ESP32)
              |
             SW        (not pressed: SW open;  pressed: SW closed)
              |
             GND  (Pin GND of ESP32)

   No LEDs and no other components in this problem.
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| 3v3 | top of 10 kΩ resistor | supply for the pull-up |
| GPIO 32 | junction of 10 kΩ and SW | ext0 wake-up source, triggered on LOW |
| GND | other side of SW | pressing pulls GPIO 32 to 0 V |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Pull-up resistor | 10 kΩ | slide 57 |
| Push button | SPST momentary (SW) | slide 57 |

## Notes

- Slide 57 repeats the standard wiring note: "by connecting the switches in this
  way, pressing the switch gives the LOW logic at the ESP32 pin." That is why
  the wake-up is configured for `LOW`.
- Slide 56 lists the pins usable for ext0 wake-up: GPIO 0, 2, 4, 12–15, 25–27,
  32–39. GPIO 32 is in that set.
- Slide 56 also notes that the pin mode does not need to be declared for an ext0
  wake-up pin, which is why there is no `pinMode()` call in the sketch.
