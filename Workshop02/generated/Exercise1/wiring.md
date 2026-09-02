# Exercise1 wiring — Exercise 2 (Lecture Note 4, Example 2)

Source: `Lecture Note 4 - ESP32 - Multitasking and Deep Sleep.pdf`, slide 15
(identical to the circuit on slides 4, 9, 24 and 34).

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
| GPIO 34 | junction of 10 kΩ and SW | input only; **no internal pull-up available** |
| GND | other side of SW | pressing pulls GPIO 34 to 0 V |
| GPIO 16 | LED1 long leg (anode) | timing-based task |
| GPIO 17 | LED2 long leg (anode) | event-based task, driven from the interrupt |
| GND | 330 Ω from each LED short leg | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Pull-up resistor | 10 kΩ | slide 15 |
| LED series resistors | 330 Ω each | slide 15 |
| Push button | SPST momentary (SW) | slide 15 |

## Logic

Slide 4 states it directly: "by connecting the switches in this way, pressing
the switch gives the LOW logic at the ESP32 pin." The 10 kΩ is an external
pull-up, so the pin idles HIGH and falls to 0 V on a press — which is why the
interrupt is attached on `FALLING`.

GPIO 34 is input-only and has no internal pull-up, so the external resistor is
required. Slide 14: every GPIO except GPIO6–GPIO11 can serve as an interrupt pin.
