# Q3 — Homework 5 Problem 3: switch-controlled LED (`is_pressed`)

Status: READY FOR REVIEW

> **Video name:** `"Q3"`. This folder is named after the video you submit.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q3.py` | the program: open it in Thonny on the Pi |
| `wiring.md` | LED + switch circuit, pin table |
| `README.md` | this file |

No companion files.

## Task

From `CSS452 - Homework 5 - Intro to Raspberry Pi.pdf`, Problem 3:

> Do the Example 4 in Lecture Note 8. Record a video to show
> - circuit connection,
> - Python code,
> - demonstration:
>   - Pressing the switch, the LED is on.
>   - Not pressing the switch, the LED is off.
>
> Set the video name "Q3" and submit it to the Google Classroom.

## Behavior

`Button(18, pull_up=True)` reads GPIO18 with the internal pull-up enabled.
`is_pressed` is `True` while the switch shorts GPIO18 to GND. The loop polls it
continuously: held down means the LED is on; released means off.

Example 5 (slide 57) does the same with `when_pressed` / `when_released`.
Homework 5 asks for **Example 4**, so that is what is here.

## Source basis

`Q3.py` is a **verbatim transcription** of the Example 4 listing on slide
55: same lines, order, spacing and spelling. Nothing was added or removed, and
no syntax fix was needed. It is `.py`, not `.ino`: Workshop05 moves from
ESP32/Arduino to Raspberry Pi/Python.

| Fact | Source |
| --- | --- |
| LED on GPIO22 through 330 Ω; switch GPIO18 → GND | LN8 slide 54 (schematic image) |
| "no resistor is needed" for the switch | LN8 slide 54 |
| `pull_up=True` enables the internal pull-up | LN8 slide 52 |
| `is_pressed` returns True when pressed | LN8 slides 53, 55 |

## Getting the file onto the Pi

The slides have you type the program into Thonny on the Pi. Typing it is fine
and shows on video. You can also copy it from the Mac:

```sh
scp Q3/Q3.py pi@raspberrypi.local:~/
```

Then, in the Pi desktop over VNC: **Thonny → Load → `/home/pi/Q3.py` → Run**.

## How to test

1. Build `wiring.md`: LED as in Q1, plus the switch between GPIO18 (pin 12)
   and GND.
2. Run `Q3.py`.
3. Hold the switch: LED on. Release: LED off.

## Limitations

- Not hardware-tested. Under gpiozero's mock pin factory, with GPIO18 driven
  low from 1.0 s to 2.5 s, GPIO22 went on at ~1.1 s and off at ~2.6 s.
- The loop has no `sleep`, so it busy-polls and keeps one CPU core busy. That
  is the instructor's listing, unchanged.
- No debounce (`bounce_time` is left at its default of none, slide 52). It
  doesn't matter here: the LED simply mirrors the switch, so bounce shows
  only as an invisible flicker.
