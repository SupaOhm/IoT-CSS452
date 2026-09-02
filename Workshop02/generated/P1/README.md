# P1 — Exercise 2: ESP32 Multitasking and Deep Sleep

Status: READY FOR REVIEW

## Task

From `CSS452 - Exercise 2.pdf`:

> Do the Example 2 in Lecture Note 4. Record a video to show circuit connection,
> Arduino code, demonstration:
>
> - LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds,
> - LED2 is toggled if we press the switch "SW".

Submit the video to Google Classroom. No due date is stated in the exercise.

## Behavior

Two tasks run in parallel:

- **Task 1 (timing-based).** `loop()` compares `millis()` against
  `previousMillis`. Every 2000 ms it flips `led1State` and writes it to GPIO 16.
  No `delay()` is used, so the loop never blocks.
- **Task 2 (event-based).** A pin-change interrupt on GPIO 34 fires on `FALLING`
  — the moment the switch is pressed. The handler `toggle()` inverts `led2State`
  and writes it to GPIO 17.

Note the difference from Example 1: LED2 is **toggled** by a press, not held on
while pressed. The lecture calls this out explicitly on slide 15.

## Source basis

`P1.ino` is a verbatim transcription of the instructor's `Ex_Interrupts.ino`
listing (Lecture Note 4, slides 16–17) — same lines, comments, and spacing.
Nothing was added or reworded, and no syntax fix was needed.

| Fact | Source |
| --- | --- |
| Button GPIO 34, LED1 GPIO 16, LED2 GPIO 17 | slide 15 diagram, slide 16 code |
| 10 kΩ pull-up to 3v3, switch to GND | slide 15 diagram |
| 330 Ω per LED | slide 15 diagram |
| Pressing gives LOW logic at the pin | slide 4 text |
| `interval = 2000` (2 seconds) | slide 16 code |
| `millis()` for the timing task | slides 8, 10 |
| `attachInterrupt(digitalPinToInterrupt(...), toggle, FALLING)` | slide 17 code |
| `toggle()` inverts `led2State` | slide 16 code |
| Interrupt-capable pins: all except GPIO6–11 | slide 14 |

The sketch reproduces the instructor's `Ex_Interrupts.ino` listing (slides 16–17).

## How to test

1. Build the circuit in `wiring.md`. Check LED polarity on both LEDs: long leg to
   the GPIO, short leg through the 330 Ω to GND.
2. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; select your port.
3. Open `P1.ino` and upload. Press the PROGRAM button if the output window sits
   at `Connecting…`.
4. LED1 should blink on 2 s / off 2 s continuously without pausing.
5. Press and release SW: LED2 changes state and stays there. Press again: it
   changes back. LED1's blinking must not stutter while you do this.

## Limitations

- Not hardware-tested.
- Example 2 does not call `Serial.begin()`, so this sketch prints nothing. The
  exercise does not ask for serial output.
- No debounce. A mechanical bounce on the press can fire `toggle()` more than
  once, leaving LED2 in the opposite state to what you expect. The instructor's
  Example 2 has the same behaviour, so it is kept unchanged — but if LED2 seems
  to ignore a press during your recording, this is why.
- `led2State` is written from an interrupt handler without a `volatile`
  qualifier, exactly as in the instructor's listing.
