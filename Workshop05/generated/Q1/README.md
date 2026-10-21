# Q1 — Homework 5 Problem 1: blink an LED with `on()` / `off()`

Status: READY FOR REVIEW

> **Video name:** `"Q1"`. This folder is named after the video you submit.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q1.py` | the program: open it in Thonny on the Pi |
| `wiring.md` | circuit, pin table, component values |
| `README.md` | this file |

No companion files: the task is one Python script and an LED.

## Task

From `CSS452 - Homework 5 - Intro to Raspberry Pi.pdf`, Problem 1:

> Do the Example 1 in Lecture Note 8. Record a video to show
> - circuit connection,
> - Python code,
> - demonstration:
>   - LED is alternatively turned on for 2 seconds and turned off for 2 seconds.
>
> Set the video name "Q1" and submit it to the Google Classroom.

## Behavior

`LED(LED_PIN)` drives GPIO22. The loop prints `on`, lights the LED, sleeps 2 s,
prints `off`, turns it off, sleeps 2 s, and repeats until you press **Stop** in
Thonny. The `on` / `off` lines appear in Thonny's Shell pane, so film both the
LED and the screen.

## Source basis

`Q1.py` is a **verbatim transcription** of the Example 1 listing on slide
42: same lines, order, spacing and spelling. Nothing was added or removed, and
no syntax fix was needed. It is `.py`, not `.ino`: Workshop05 moves from
ESP32/Arduino to Raspberry Pi/Python.

| Fact | Source |
| --- | --- |
| LED on GPIO22 through 330 Ω to GND | LN8 slide 41 (schematic image) |
| on/off every 2 seconds, using `on()` / `off()` | LN8 slide 41 text; listing slide 42 |
| BCM numbering in code | LN8 slides 9–10 |

## Getting the file onto the Pi

The slides have you type the program into Thonny on the Pi. Typing it is fine
and shows on video. You can also copy it from the Mac:

```sh
scp Q1/Q1.py pi@raspberrypi.local:~/
```

Then, in the Pi desktop over VNC: **Thonny → Load → `/home/pi/Q1.py` → Run**.

## How to test

1. Build `wiring.md`. Check the LED's long leg goes to GPIO22 (physical pin 15).
2. Run `Q1.py` in Thonny.
3. The Shell prints `on` / `off` alternately; the LED follows, 2 s each.
4. Press **Stop** to end it.

## Limitations

- Not hardware-tested. Checked on a Mac with `python3 -m py_compile` and run
  under gpiozero's **mock** pin factory: GPIO22 went on at 0 s, off at ~2 s, and
  on at ~4 s. A mock pin is not an LED.
- When stopped mid-cycle, the LED may be left in whatever state it was in.
  gpiozero normally releases the pin on exit.
