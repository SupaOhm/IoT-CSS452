# P2 wiring — Homework 3 Problem 2 (Lecture Note 5, Section 5.2)

Source: `Lecture Note 5 - ESP32 - Web Servers and Clients.pdf`, slide 96.

**The circuit is identical to `P1`.** If you record `P1` first, leave the
breadboard exactly as it is and only change the sketch.

## Diagram

```text
   Pin 3v3 of ESP32
         |
         +------------------+
                            |
                          .-+-.
                          |   |           ESP32
        Potentiometer     |   |<---------- A0    (wiper -> analog input)
                          |   |
                          `-+-'
                            |
         +------------------+
         |
   Pin GND of ESP32
```

The potentiometer is a three-terminal voltage divider: the two outer terminals
go to 3v3 and GND, and the middle terminal (the wiper) goes to the pin labelled
**A0**. Turning the knob sweeps the wiper voltage between 0 V and 3.3 V.

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| 3v3 | one outer potentiometer terminal | top of the divider |
| A0 | potentiometer wiper (middle terminal) | read with `analogRead(A0)` |
| GND | other outer potentiometer terminal | bottom of the divider |

## Components

| Part | Value | Source |
| --- | --- | --- |
| Potentiometer | value not stated in the material | slide 96 schematic |

The lecture never gives the potentiometer's resistance, and the sketch does not
depend on it — any common linear pot (10 kΩ is typical) divides 3.3 V the same
way. Nothing here is guessed: the schematic simply does not label it.

## About the pin name

The schematic and the code both say **A0**, and neither the lecture nor the
sketch ever gives a GPIO number for it. Wire to the pin your board labels `A0`;
the Arduino ESP32 core resolves the name for you, so no code change is needed.
If your board has no `A0` silkscreen, check its pinout before substituting a
pin — do not guess.
