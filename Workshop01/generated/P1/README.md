# P1 — Exercise 1: Introduction to ESP32

Status: READY FOR REVIEW

## Task

From `CSS452 - Exercise 1.pdf`:

> Do the Example 1 in Lecture Note 3. Take a video to show circuit connection,
> Arduino code, demonstration: pressing the switch (pressing → LED on; not
> pressing → LED off).

Deliverable is a video of about/less than 20 seconds, submitted to Google
Classroom. Stated due date: **20th Aug., before 11.59am**.

## Behavior

- `GPIO 34` is read every loop with `digitalRead()`.
- The value is echoed to the serial monitor at 115200 baud.
- Pressed (reads `LOW`) → `GPIO 17` HIGH → LED on.
- Not pressed (reads `HIGH`) → `GPIO 17` LOW → LED off.

## Source basis

Every fact below is taken from `Lecture Note 3 - Introduction to ESP32.pdf`:

| Fact | Source |
| --- | --- |
| Button on GPIO 34, LED on GPIO 17 | slide 26 diagram, slide 27 code |
| 10 kΩ pull-up to 3v3, switch to GND | slide 26 diagram |
| 330 Ω in series with the LED | slide 26 diagram |
| Pressed → LED on / released → LED off | slide 26 text |
| `Serial.begin(115200)` | slide 27 code; baud rule on slide 19 |
| Board: ThaiEasyElec's ESPino32 | slide 18 |

The sketch reproduces the instructor's `Digital_InOut.ino` listing (slide 27),
including its comments, because the exercise instruction is to *do Example 1*.

## How to test

1. Build the circuit exactly as in `wiring.md`. Check LED polarity: long leg to
   GPIO 17, short leg through the 330 Ω to GND.
2. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; Tools → Port → your port.
3. Open `P1.ino` and upload. If the output window shows `Connecting…`, press the
   PROGRAM button on the ESP32 (slide 20).
4. Serial Monitor at **115200** baud.
5. Expect `1` printed while released and `0` while pressed, with the LED
   following: pressed → on, released → off.

## Limitations

- Not hardware-tested.
- No debounce is used. The instructor's Example 1 does not debounce, and the
  task is a level-driven on/off, so debouncing is not required here.
