# HW1 — Homework 2, Problem 1

Status: READY FOR REVIEW

> **Naming:** submit this problem's **video** as `"P1"` per the instructor.
> The folder is `HW1` because this repository reserves `P` for in-class problems.

## Task

From `CSS452 - Homework 2.pdf`:

> Do the Example 5 in Lecture Note 4. Take a video to show circuit connection,
> Arduino code, demonstration:
>
> - The serial monitor shows which core is running.
> - LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
> - LED2 is on if we press the switch "SW"; otherwise, LED2 is off.

## Behavior

Two FreeRTOS tasks are created in `setup()` and pinned to different cores:

- **`TimerLED` on Core 0.** Prints `TimerLED() running on core 0`, waits 100 ms,
  then does the `millis()` comparison. Every 2000 ms it flips `led1State`;
  `digitalWrite(led1Pin, led1State)` runs on every pass.
- **`SwitchLED` on Core 1.** Prints `SwitchLED() running on core 1`, waits 100 ms,
  reads GPIO 34, and drives LED2 HIGH while the switch is held down.

`loop()` is empty — the two tasks do all the work. Both print continuously, so
the serial monitor interleaves lines from core 0 and core 1, which is what
demonstrates that they run simultaneously.

Note this differs from Exercise 2: here LED2 is **on while held**, not toggled.

## Source basis

| Fact | Source |
| --- | --- |
| Same circuit as Example 3 (SW 34, LED1 16, LED2 17) | slide 34, via slide 24 |
| `TimerLED` body, `for(;;)`, `vTaskDelete(NULL)` | slide 35 code |
| `SwitchLED` body | slide 36 code |
| Declarations (lines 1–12) | slide 25 code (carried into Examples 4 and 5) |
| `xPortGetCoreID()` to print the running core | slides 28, 30 |
| `xTaskCreatePinnedToCore(..., 1024, NULL, 1, NULL, 0/1)` | slide 36 code |
| Core 0 → TimerLED, Core 1 → SwitchLED | slides 34, 36 |
| `Serial.begin(115200)` | slide 36 code |
| `delay(100)` inside each task | slides 35, 36 |

The sketch reproduces the instructor's `Ex_AssignCore.ino` listing. Its
declaration block is not reprinted on slides 35–36; it is carried over unchanged
from Example 3 (slide 25), which slide 34 states Example 5 is built from.

## How to test

1. Build the circuit in `wiring.md` — unchanged from Exercise 2, so you can
   record both from the same breadboard.
2. Board → **ThaiEasyElec's ESPino32**, select your port, upload `HW1.ino`.
3. Serial Monitor at **115200** baud.
4. Expect interleaved lines: `TimerLED() running on core 0` and
   `SwitchLED() running on core 1`.
5. LED1 blinks 2 s on / 2 s off. Hold SW: LED2 lights and stays lit until you
   release.

## Limitations

- Not hardware-tested.
- The stack size is 1024 bytes per task, as in the instructor's listing. That is
  small for tasks that call `Serial.print()`; if you hit a stack-overflow reset,
  raise it to 10000 (the value the lecture uses for `xTaskCreate()` on slide 23)
  and mention the change in your video.
- `previousMillis`, `led1State` and `led2State` are shared between tasks on
  different cores without a mutex or `volatile`, exactly as in the instructor's
  listing. This is safe enough here because each variable is touched by only one
  task.
