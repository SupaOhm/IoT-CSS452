# P2 — Homework 1, Problem 2

Status: READY FOR REVIEW

> **Video name:** `"P2"` — this folder is named after the video the
> instructor asks you to submit, so the two always match.

## Task

From `CSS452 - Homework 1.pdf`:

> Do the Example 8 in Lecture Note 3. Take a video to show Arduino code,
> demonstration: the serial monitor shows the local time every one second.
> Name your video as "P2" and submit to the Google Classroom. Note that your
> ESP32 must be able to connect to your WiFi access point in order to connect
> to the Internet.

## Behavior

1. `setup()` connects to WiFi, printing dots until `WiFi.status()` is `WL_CONNECTED`.
2. `configTime()` initialises the NTP client against `pool.ntp.org` with a
   +7 hour offset and no daylight saving.
3. The time is printed once, then WiFi is disconnected and switched off — the
   internal clock keeps counting from there (slide 61, Remark 1).
4. `loop()` waits 1000 ms and prints the time again, giving the once-per-second
   output the task asks for.

Output format is `%A, %B %d %Y %H:%M:%S`, e.g. `Sunday, August 01 2021 10:38:35`
(slide 56).

## Source basis

`P2.ino` is a verbatim transcription of the instructor's `DateTimerNTP.ino`
listing (Lecture Note 3, slides 54–56) — same lines, comments, and spacing.
Nothing was added or reworded, and no syntax fix was needed. The WiFi
placeholders `"Your SSID"` / `"Your Password"` are the instructor's own; see
**Before you run it**.

| Fact | Source |
| --- | --- |
| `#include <WiFi.h>`, `#include "time.h"` | slide 54 code |
| `ntpServer = "pool.ntp.org"` | slide 54 code |
| `gmtOffset_sec = 7*3600` (Thailand UTC+7) | slide 54 code; explained slide 57 |
| `daylightOffset_sec = 0` for Thailand | slide 54 code; explained slide 57 |
| `printLocalTime()` using `getLocalTime()` | slides 54, 58 |
| WiFi connect loop, `configTime`, disconnect | slide 55 code |
| `loop()` with `delay(1000); printLocalTime();` | slide 56 code |
| Baud 115200 | slide 55 code; baud rule slide 19 |

The sketch reproduces the instructor's `DateTimerNTP.ino` listing (slides 54–56).
Example 8 already prints once per second, so no modification was needed.

## Before you run it

Replace the two placeholders with your own network:

```cpp
const char* ssid     = "Your SSID";
const char* password = "Your Password";
```

The lecture ships these as placeholders (slide 54) and the course material
supplies no credentials, so none are guessed here.

## How to test

1. Fill in your SSID and password.
2. Board → **ThaiEasyElec's ESPino32**, select your port, upload `P2/P2.ino`.
3. Serial Monitor at **115200** baud.
4. Expect `Connecting to <ssid> ..... CONNECTED`, then a date-and-time line
   appearing once per second.

## Limitations

- Not hardware-tested.
- WiFi is switched off after the first sync, so the displayed time afterwards
  comes from the ESP32's internal clock and will drift over long runs. This is
  the instructor's design (slide 61, Remark 1), kept unchanged.
- If the serial monitor prints `Failed to obtain time`, the NTP sync did not
  complete before the first call.
