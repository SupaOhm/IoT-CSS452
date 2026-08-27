# HW1 wiring — Homework 2 Problem 1 (Lecture Note 4, Example 5)

Source: `Lecture Note 4 - ESP32 - Multitasking and Deep Sleep.pdf`, slide 34
("the same circuit as shown in Example 3"), identical to slides 4, 9, 15 and 24.

## Diagram

```text
        Pin 3v3 of ESP32
              |
             [ ] 10K
              |
              +---------------------> GPIO 34   (ESP32, input only)
              |
             SW        (not pressed: SW open;  pressed: SW closed)
              |
             GND  (Pin GND of ESP32)


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
| 3v3 | top of 10 kΩ resistor | supply for the pull-up |
| GPIO 34 | junction of 10 kΩ and SW | read by the `SwitchLED` task on Core 1 |
| GND | other side of SW | pressing pulls GPIO 34 to 0 V |
| GPIO 16 | LED1 long leg (anode) | driven by the `TimerLED` task on Core 0 |
| GPIO 17 | LED2 long leg (anode) | driven by the `SwitchLED` task on Core 1 |
| GND | 330 Ω from each LED short leg | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Pull-up resistor | 10 kΩ | slide 34 (via Example 3, slide 24) |
| LED series resistors | 330 Ω each | slide 34 |
| Push button | SPST momentary (SW) | slide 34 |

The wiring is unchanged from Exercise 2. Only the software differs: the two jobs
become FreeRTOS tasks pinned to separate cores.
