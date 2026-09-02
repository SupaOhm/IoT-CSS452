# HW2 — Homework 2, Problem 2

Status: READY FOR REVIEW

> **Naming:** submit this problem's **video** as `"P2"` per the instructor.

## Task

From `CSS452 - Homework 2.pdf`:

> Do the Example 9 in Lecture Note 4. Take a video to show circuit connection,
> Arduino code, demonstration:
>
> - The serial monitor shows that ESP32 is in the deep sleep.
> - Pressing the switch (SW) wakes ESP32 up (take a video to show "pressing the
>   switch" and, then, the serial monitor shows that ESP32 wakes up).

## Behavior

Everything happens in `setup()`, because waking from deep sleep is a **reset** —
execution restarts from the beginning each time (slide 44).

1. `esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, LOW)` arms the wake-up before
   sleeping, as slide 48 requires.
2. `bootCount` is stored with `RTC_DATA_ATTR`, so it survives deep sleep in RTC
   memory and increments on every wake — this is what visibly proves on the
   serial monitor that the board woke rather than merely rebooted.
3. The board prints the boot number, announces a 10 second countdown, waits,
   prints `... Now, in the deep sleep mode.` and calls `esp_deep_sleep_start()`.
4. Nothing after that line runs. Pressing SW pulls GPIO 32 LOW, the board wakes,
   resets, and prints `Boot number: 2`.

## Source basis

`HW2.ino` is a verbatim transcription of the instructor's `Ex_ext0WakeUp.ino`
listing (Lecture Note 4, slide 58) — same lines, comments, and spacing. Nothing
was added or reworded, and no syntax fix was needed.

| Fact | Source |
| --- | --- |
| Switch on GPIO 32, 10 kΩ pull-up to 3v3, switch to GND | slide 57 diagram |
| Pressing gives LOW logic at the pin | slide 57 text |
| `esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, LOW)` | slides 56, 58 |
| ext0-capable pins include GPIO 32 | slide 56 |
| No `pinMode()` needed for a wake-up pin | slide 56 |
| `RTC_DATA_ATTR int bootCount = 0;` | slides 44, 58 |
| 10 second delay then `esp_deep_sleep_start()` | slide 58 code |
| Wake-up sources must be configured before sleeping | slide 48, Remark 2 |
| Waking restarts the program with a reset | slides 44, 45 |
| `Serial.begin(115200)`, `delay(1000)` for the monitor | slide 58 code |

The sketch reproduces the instructor's `Ex_ext0WakeUp.ino` listing (slide 58).

## How to test

1. Build the circuit in `wiring.md`. Note this uses **GPIO 32**, not GPIO 34 as
   in the other problems — rewire before recording.
2. Board → **ThaiEasyElec's ESPino32**, select your port, upload `HW2.ino`.
3. Serial Monitor at **115200** baud, then press the RESET button so you catch
   the first boot message.
4. Expect `Boot number: 1`, then `ESP32 will enter the deep sleep in 10 s.`,
   then after ten seconds `... Now, in the deep sleep mode.` and silence.
5. Press SW. The board wakes and prints `Boot number: 2`.

For the video, the instructor wants the press itself on camera followed by the
serial monitor showing the wake — so frame both the breadboard and the monitor,
or pan between them without cutting.

## Limitations

- Not hardware-tested.
- Some USB-serial adapters drop the port when the ESP32 enters deep sleep, so
  the Arduino Serial Monitor may disconnect and lose output on wake. If that
  happens, reopen the monitor after the press; the `Boot number` counter will
  still show the wake occurred.
- `Serial.println("This sentence will never be printed.")` is retained from the
  instructor's listing. It is intentionally unreachable — slide 45 states the
  board sleeps immediately and executes nothing after the call.
