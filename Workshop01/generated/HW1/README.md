# HW1 — Homework 1, Problem 1

Status: READY FOR REVIEW

> **Naming:** the instructor asks you to name this **video** `"P1"`. In this
> repository `P` folders mean in-class problems, so the homework problems are
> `HW1`, `HW2`, `HW3`. This folder is homework Problem 1 → submit its video as
> `"P1"`.

## Task

From `CSS452 - Homework 1.pdf`:

> Do the Example 3 in Lecture Note 3. Take a video to show circuit connection,
> Arduino code, demonstration: adjust the brightness of the LED by rotating the
> potentiometer. Name your video as "P1" and submit to the Google Classroom.

## Behavior

- `analogRead(A0)` returns 0–4095 for 0–3.3 V from the potentiometer wiper.
- That value is mapped to 0–255 and written to LEDC channel 0 with `ledcWrite()`.
- Channel 0 is attached to GPIO 17, so LED brightness tracks the knob.

## Source basis

| Fact | Source |
| --- | --- |
| Potentiometer to A0, LED on GPIO 17 | slide 35 diagram, slide 36 code |
| 330 Ω in series with the LED | slide 35 diagram |
| `freq = 5000`, `ledChannel = 0`, `resolution = 8` | slide 33 and slide 36 code |
| `ledcSetup` / `ledcAttachPin` / `ledcWrite` | slides 33–34 |
| `map(potValue, 0, 4095, 0, 255)` | slide 36 code |
| Analog range 0–4095 ↔ 0–3.3 V | slide 28 |

The sketch reproduces the instructor's `Analog_PWM.ino` listing (slide 36).

## How to test

1. Build the circuit in `wiring.md`.
2. Board → **ThaiEasyElec's ESPino32**, select your port, upload `HW1.ino`.
3. Rotate the potentiometer: the LED should dim smoothly at one end and reach
   full brightness at the other.

## Limitations

- Not hardware-tested.
- The instructor's Example 3 does not call `Serial.begin()`, so this sketch
  prints nothing. Nothing in the task asks for serial output.
- `ledcSetup()` and `ledcAttachPin()` are the ESP32 Arduino core 2.x API used
  throughout Lecture Note 3. On ESP32 core 3.x these were replaced by
  `ledcAttach()` and the sketch will not compile unmodified. Install the core
  version your course uses; the material does not state a version.
