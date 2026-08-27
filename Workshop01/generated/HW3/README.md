# HW3 — Homework 1, Problem 3

Status: NEEDS CLARIFICATION

See `QUESTIONS.md`. Two facts are missing from the supplied material: the touch
threshold, and which lecture example the homework's "Example 5" refers to.

> **Naming:** submit this problem's **video** as `"P3"` per the instructor.
> The folder is `HW3` because this repository reserves `P` for in-class problems.

## Task

From `CSS452 - Homework 1.pdf`:

> Connect a wire to a touch pin of ESP32 (as shown in Example 4). Write the
> Arduino code such that the ESP32 will perform these 2 tasks:
>
> - when ESP32 starts, it will connect to your WiFi access point and show its IP
>   address on the serial monitor (similar to Example 6),
> - thereafter, if you touch the wire, ESP32 will restart (look at Example 4 and
>   Example 5).
>
> Take a video to show circuit connection, Arduino code, demonstration of the
> above 2 tasks. Name your video as "P3" and submit to the Google Classroom. The
> demonstration video is shown in the attached video "CSS452 - Homework 1 -
> Problem 3".

Unlike HW1 and HW2, this problem is **not** a straight copy of a lecture
example — it composes three of them.

## Behavior

1. On start, `setup()` puts the ESP32 in station mode, connects to WiFi, and
   prints `Connected, IP address: <ip>` on the serial monitor.
2. `loop()` reads `touchRead(32)` once per second and prints the value.
3. When the reading falls below the threshold — i.e. the wire is touched —
   the sketch prints `Touched - restarting` and calls `ESP.restart()`.
4. After restarting, the board reconnects and prints its IP again, so the cycle
   is visible on the serial monitor.

## Source basis

| Fact | Source |
| --- | --- |
| Wire on GPIO 32 as the touch pin | slide 39 (Example 4) |
| Touch pins are GPIO 0,2,4,12,13,14,15,27,32,33 | slide 37 |
| `touchRead()` returns 0–1023; touched = low value | slide 38 |
| 1 second sampling period | slide 40 (Example 4 code) |
| `WiFi.mode(WIFI_STA)`, `WiFi.begin()`, connect loop | slide 48 (Example 6) |
| `Serial.println(WiFi.localIP())` to show the IP | slide 48 (Example 6) |
| `ESP.restart()` for a software reset | slide 43 (section 3.6) |
| Baud 115200 | slides 19, 48 |

**Not** from the material: the numeric touch threshold. See `QUESTIONS.md`.

## Before you run it

Replace the placeholders with your own network, following the lecture's own
placeholder names:

```cpp
const char* ssid     = "Your_SSID";
const char* password = "Your_Password";
```

## How to test

1. Connect one wire to GPIO 32 and leave its far end bare.
2. Fill in your SSID and password.
3. Board → **ThaiEasyElec's ESPino32**, select your port, upload `HW3.ino`.
4. Serial Monitor at **115200** baud.
5. Watch the printed `touchRead()` values while *not* touching the wire; note
   the typical range. Touch the wire and note the lower range.
6. If your two ranges do not straddle `20`, set `touchThreshold` midway between
   them and re-upload — see `QUESTIONS.md`.
7. Expect: IP address on boot, then a value each second, then on touch
   `Touched - restarting`, a boot message, and the IP address again.

## Limitations

- Not hardware-tested.
- The touch threshold is unconfirmed; the sketch will restart at the wrong
  moment, or never, if `20` does not suit your board.
- There is no debounce or hold-off. A sustained touch may retrigger a restart
  immediately after boot. The supplied material specifies no such behaviour, so
  none was added.
- The task references an attached demonstration video, `CSS452 - Homework 1 -
  Problem 3`. That video was not supplied, so its exact demonstrated behaviour
  could not be checked.
