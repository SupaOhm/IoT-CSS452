# HW3 — Homework 2, Problem 3

Status: READY FOR REVIEW

> **Naming:** submit this problem's **video** as `"P3"` per the instructor.

Every pin, resistor and timing value in this task is stated in the supplied
material, so there is no `QUESTIONS.md`. One structural choice was not specified;
it is described under *Design choice* below.

## Task

From `CSS452 - Homework 2.pdf`:

> In this problem, we will revise Example 5 in Lecture Note 4 by connect one more
> switch (call it "SW1") to ESP32 (to the pin GPIO26) as shown below.
>
> Write the Arduino code such that
>
> - when ESP32 is on (similar to the jobs in Example 5 in Lecture Note 4):
>   - The serial monitor shows which core is running.
>   - LED1 is alternatively turned on for 2 seconds and turned off for 2 seconds.
>   - LED2 is on if we press the switch "SW"; otherwise, LED2 is off.
> - (New) when ESP32 is on, pressing the switch "SW1" will let the ESP32 go to
>   deep sleep. Here, we use the pin-change interrupt to do this (similar to
>   Example 2 in Lecture Note 4).
> - (New) After ESP32 is in deep sleep, it will wake up 15 seconds later by using
>   the timer wakeup (similar to Example 7 in Lecture Note 4).

## Behavior

**While awake** — unchanged from HW1:

- `TimerLED` on Core 0 prints its core and blinks LED1 on 2 s / off 2 s.
- `SwitchLED` on Core 1 prints its core and holds LED2 on while SW is pressed.

**On pressing SW1:**

1. GPIO 26 falls from HIGH to LOW, firing the `FALLING` interrupt.
2. `requestSleep()` sets `sleepRequested`. It does nothing else.
3. `loop()` sees the flag, prints `SW1 pressed ... Now, in the deep sleep mode.`,
   and calls `esp_deep_sleep_start()`. Both LEDs go dark and the serial output
   stops.
4. Fifteen seconds later the timer wakes the board. Waking is a **reset**
   (slide 44), so `setup()` runs again, `bootCount` increments, the tasks are
   recreated, and the core messages and LED1 blinking resume.

`bootCount` is kept in RTC memory with `RTC_DATA_ATTR`, so the increasing
`Boot number:` line is what proves on camera that a real deep-sleep cycle
happened rather than a stall.

## Design choice

The task says to use the pin-change interrupt to enter deep sleep, but does not
say **where** `esp_deep_sleep_start()` should be called. Two readings work:

- call it inside the interrupt handler, or
- set a flag in the handler and sleep from `loop()` — what this sketch does.

The flag was chosen because `CLAUDE.md` requires interrupt handlers to stay
minimal, and Lecture Note 4's own handler (`toggle()`, slide 16) is two lines.
The observable behaviour is identical, so either reading satisfies the video
demonstration. If your instructor wants the call inside the handler, move the
two lines from `loop()` into `requestSleep()`.

## Source basis

| Fact | Source |
| --- | --- |
| SW1 on GPIO 26 with a 10 kΩ pull-up to 3v3 | Homework 2 Problem 3 diagram |
| SW on 34, LED1 on 16, LED2 on 17, 330 Ω each | Homework 2 Problem 3 diagram |
| Both switches read LOW when pressed | Homework 2 diagram; Lecture Note 4 slide 4 |
| Task bodies, cores, `xTaskCreatePinnedToCore` | slides 35, 36 (Example 5) |
| Declarations (lines 1–12) | slide 25, carried into Example 5 |
| `attachInterrupt(digitalPinToInterrupt(...), fn, FALLING)` | slides 13, 17 (Example 2) |
| Interrupt-capable pins: all except GPIO6–11 | slide 14 |
| `esp_sleep_enable_timer_wakeup(X*1000000)`, X in seconds | slides 49, 50 (Example 7) |
| 15 seconds | Homework 2 Problem 3 text |
| `esp_deep_sleep_start()` | slide 45 |
| Wake-up source must be armed before sleeping | slide 48, Remark 2 |
| Waking restarts the program with a reset | slides 44, 45 |
| `RTC_DATA_ATTR` survives deep sleep | slide 44 |

Not from the material: the `sleepRequested` flag structure (see *Design choice*)
and the `delay(100)` before sleeping, which gives the serial buffer time to
empty — without it the final message can be lost when the CPU powers down.

## How to test

1. Start from the HW1 breadboard and add SW1 plus its 10 kΩ pull-up on GPIO 26.
2. Board → **ThaiEasyElec's ESPino32**, select your port, upload `HW3.ino`.
3. Serial Monitor at **115200** baud.
4. Confirm the Example 5 behaviour first: interleaved core messages, LED1
   blinking 2 s / 2 s, LED2 following SW.
5. Press SW1. Expect the deep-sleep message, then both LEDs dark and no output.
6. Wait 15 seconds. Expect `Boot number:` to increment and everything resume.

## Limitations

- Not hardware-tested.
- Holding SW1 down across the wake-up re-triggers the interrupt immediately, so
  the board can sleep again at once. Press and release cleanly.
- No debounce on SW1. A bouncy press only sets an already-set flag, so it is
  harmless here.
- Task stack size is 1024 bytes, as in the instructor's Example 5. If you hit a
  stack-overflow reset, raise it to 10000 (slide 23) and say so in your video.
- Deep sleep may drop the USB serial connection; reopen the Serial Monitor after
  the wake if output does not resume. The `Boot number` counter still proves the
  cycle occurred.
