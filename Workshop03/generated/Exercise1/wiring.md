# Exercise1 wiring — Exercise 3 (Lecture Note 5, Section 3)

Source: `Lecture Note 5 - ESP32 - Web Servers and Clients.pdf`, slide 52
(the same circuit is drawn on slides 45, 47, 48 and 49).

No input hardware is used. The buttons that switch the LEDs are on the web page,
not on the breadboard.

## Diagram

```text
   GPIO 26 ------+                     GPIO 27 ------+
                 |                                   |
              long leg                            long leg
                \ /  LED1                           \ /  LED2
                ---                                 ---
              short leg                          short leg
                 |                                   |
                [ ] 330                             [ ] 330
                 |                                   |
                GND                                 GND
              (Pin GND of ESP32)          (Pin GND of ESP32)
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| GPIO 26 | LED1 long leg (anode) | driven by the `/26/on` and `/26/off` URLs |
| GPIO 27 | LED2 long leg (anode) | driven by the `/27/on` and `/27/off` URLs |
| GND | 330 Ω from each LED short leg | LED current limit |

## Components

| Part | Value | Source |
| --- | --- | --- |
| LED series resistors | 330 Ω each | slide 52 |
| LEDs | 2 × standard indicator LED | slide 52 |

Both LEDs are driven HIGH to light. `setup()` sets GPIO 26 and GPIO 27 to
`OUTPUT` and writes them `LOW`, so both start dark and the page opens showing
`State off` with an ON button for each.

## Not part of the circuit

The web page needs no wiring, but the demo does need a network: the ESP32 and
the phone or computer running the browser must be on the **same Wi-Fi network**
(Lecture Note 5, slides 40 and 43). USB supplies power and carries the serial
output that prints the ESP32's IP address.
