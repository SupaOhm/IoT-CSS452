# Q4 — Homework 5 Problem 4: GUI On/Off buttons (guizero)

Status: READY FOR REVIEW

> **Video name:** `"Q4"`. This folder is named after the video you submit.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q4.py` | the program: open it in Thonny on the Pi |
| `wiring.md` | circuit (same as Q1) |
| `README.md` | this file |

No companion files. The GUI window is built by the code itself; there is no
separate layout file.

## Task

From `CSS452 - Homework 5 - Intro to Raspberry Pi.pdf`, Problem 4:

> Do the Example 6 in Lecture Note 8. Record a video to show
> - circuit connection,
> - Python code,
> - demonstration:
>   - Pressing the ON button, the LED is on.
>   - Pressing the OFF button, the LED is off.
>
> Set the video name "Q4" and submit it to the Google Classroom.

## Behavior

A 100 × 150 window opens with two large buttons, **On** and **Off**. **Off**
starts greyed out (`enabled=False`). Clicking **On** lights the LED, greys out
**On**, and enables **Off**; clicking **Off** does the reverse. So only one
button is clickable at any time, matching the window on slide 67.

The "buttons" are on screen, clicked with the mouse through VNC, not wired
switches.

## Before you run: install guizero (slide 60)

The Pi needs internet for this (Internet Sharing; see
`../Exercise1/README.md` step 2). In a Pi terminal:

```sh
sudo pip3 install guizero
```

Or, if that errors: `sudo apt install python3-guizero` (slide 60).

## Source basis

`Q4.py` is a **verbatim transcription** of the Example 6 listing on slide
67: same lines, order, spacing and spelling. Nothing was added or removed, and
no syntax fix was needed. It is `.py`, not `.ino`: Workshop05 moves from
ESP32/Arduino to Raspberry Pi/Python.
Line 3 is blank, as on the slide (the slide shows the text cursor there).

| Fact | Source |
| --- | --- |
| LED on GPIO22 through 330 Ω to GND | LN8 slide 66 (schematic image) |
| Two GUI push buttons turn the LED on/off | LN8 slide 66 |
| `App`, `PushButton(app, command=…)` | LN8 slides 61, 65 |
| Install `guizero` with pip3 or apt | LN8 slide 60 |

## Getting the file onto the Pi

The slides have you type the program into Thonny on the Pi. Typing it is fine
and shows on video. You can also copy it from the Mac:

```sh
scp Q4/Q4.py pi@raspberrypi.local:~/
```

Then, in the Pi desktop over VNC: **Thonny → Load → `/home/pi/Q4.py` → Run**.

## How to test

1. Install guizero (above). Same circuit as Q1.
2. Run `Q4.py` **from Thonny in the Pi desktop** (VNC). It needs a display, so
   running it in a plain `ssh` session fails with a Tk "no display" error.
3. Click **On**: LED lights, **Off** becomes clickable. Click **Off**: LED goes
   out.
4. Film the VNC window and the LED together.

## Limitations

- Not hardware-tested. Syntax-checked only: guizero needs a Tk display, so it
  was not run under the mock pin factory.
- The window is tiny (100 × 150). Zoom the screen recording or move the window
  to where the camera sees it.
