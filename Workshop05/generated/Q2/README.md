# Q2 — Homework 5 Problem 2: set LED brightness from typed input

Status: READY FOR REVIEW

> **Video name:** `"Q2"`. This folder is named after the video you submit.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q2.py` | the program: open it in Thonny on the Pi |
| `wiring.md` | circuit (same as Q1) |
| `README.md` | this file |

No companion files.

## Task

From `CSS452 - Homework 5 - Intro to Raspberry Pi.pdf`, Problem 2:

> Do the Example 3 in Lecture Note 8. Record a video to show
> - circuit connection,
> - Python code,
> - demonstration:
>   - Input a value to adjust the LED intensity.
>
> Set the video name "Q2" and submit it to the Google Classroom.

## Behavior

`PWMLED(22)` drives GPIO22 with PWM. Each pass the program asks
`Enter Brightness (0.0 to 1.0):` in Thonny's Shell. Whatever you type is
converted with `float()` and written to `led.value`: `0` is off, `1` is full,
and `0.5` is roughly half (slide 46).

For a clear video, type `0.1`, `0.5`, `1.0`, then `0`.

## Source basis

`Q2.py` is a **verbatim transcription** of the Example 3 listing on slide
47: same lines, order, spacing and spelling. Nothing was added or removed, and
no syntax fix was needed. It is `.py`, not `.ino`: Workshop05 moves from
ESP32/Arduino to Raspberry Pi/Python.

| Fact | Source |
| --- | --- |
| LED on GPIO22, same circuit as Example 1 | LN8 slide 47 text → slide 41 schematic |
| `PWMLED`, `led.value` from 0 to 1 | LN8 slide 46 |
| Software PWM on all pins | LN8 slide 10 |

## Getting the file onto the Pi

The slides have you type the program into Thonny on the Pi. Typing it is fine
and shows on video. You can also copy it from the Mac:

```sh
scp Q2/Q2.py pi@raspberrypi.local:~/
```

Then, in the Pi desktop over VNC: **Thonny → Load → `/home/pi/Q2.py` → Run**.

## How to test

1. Same circuit as Q1.
2. Run `Q2.py`. Click into Thonny's Shell pane and type a value, then Enter.
3. The LED's brightness changes to match; the prompt repeats.

## Limitations

- Not hardware-tested. Run under gpiozero's mock pin factory with inputs
  `0.25`, `1.0`, `0`: GPIO22's duty cycle followed each value.
- **No input checking, as in the instructor's listing.** Typing text
  (`ValueError`) or a number outside 0–1 (gpiozero `OutputDeviceBadValue`)
  stops the program with an error. Keep to 0.0–1.0 while filming.
- Perceived brightness is not linear in duty cycle: the step from `0.1` to
  `0.3` looks bigger than `0.7` to `0.9`.
