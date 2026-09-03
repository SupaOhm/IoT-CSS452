# P3 — Homework 3 Problem 3: Web Server Controlling Three LEDs

Status: READY FOR REVIEW

> **Video name:** `"P3"` — this folder is named after the video the
> instructor asks you to submit, so the two always match.

## Task

From `CSS452 - Homework 3.pdf`, Problem 3:

> Connect three LEDs to the ESP32 as shown below. Similar to the project in
> Section 3, write an Arduino code such that the ESP32 will be a webserver and
> provide a webpage consisting of three buttons. By using a web browser,
> pressing these buttons will turn on/off these LEDs accordingly (i.e., revise
> the Arduino code in Section 3).
>
> Upload your code to the ESP32 and take a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - Press the button (GPIO16) on the webpage to turn the LED1 on/off.
>   - Press the button (GPIO17) on the webpage to turn the LED2 on/off.
>   - Press the button (GPIO32) on the webpage to turn the LED3 on/off.

Name your video as "P3" and submit to the Google Classroom.

## Behavior

Identical to `Exercise1` with a third output added and the pins changed:

| | `Exercise1` (Section 3) | `P3` |
| --- | --- | --- |
| LED1 | GPIO 26, routes `/26/on` and `/26/off` | GPIO 16, routes `/16/on` and `/16/off` |
| LED2 | GPIO 27, routes `/27/on` and `/27/off` | GPIO 17, routes `/17/on` and `/17/off` |
| LED3 | — | GPIO 32, routes `/32/on` and `/32/off` |

The page lists three rows — `GPIO 16 - State off`, `GPIO 17 - State off`,
`GPIO 32 - State off` — each with one button, ON while that output is off and
OFF while it is on. This matches the page mock-up printed beside Problem 3 in
the homework.

All three outputs start LOW, so the page opens with three ON buttons.

## Source basis

This is the one task in Workshop 03 that is **written, not transcribed**. The
homework says "revise the Arduino code in Section 3", so `P3.ino` is
`WebServer_ControlOutputs.ino` with the minimum changes the homework requires:

| Change | Why |
| --- | --- |
| `output26`/`output27` → `output16`/`output17`/`output32` | Homework 3 Problem 3 schematic and demonstration bullets |
| Third `pinMode()` and `digitalWrite(…, LOW)` in `setup()` | the added LED |
| Two more `else if` branches for `/32/on` and `/32/off` | the third button |
| Third state row and button block in the HTML | the page mock-up beside Problem 3 |

Everything else — the connection handling, the timeout, the HTTP response, the
CSS, the comment wording — is left exactly as the instructor wrote it. No new
technique is introduced.

| Fact | Source |
| --- | --- |
| LED1 GPIO 16, LED2 GPIO 17, LED3 GPIO 32 | Homework 3 Problem 3 schematic and bullets |
| 330 Ω per LED, long leg to the GPIO | Homework 3 Problem 3 schematic |
| Page shows `GPIO 16 - State off` etc. with one button each | Homework 3 Problem 3 page mock-up |
| Server skeleton, port 80, `timeoutTime = 2000` | Lecture Note 5 slides 54–59 |
| Serial baud 115200 | slide 55 code |
| Client and ESP32 must share one network | slides 40, 43 |

## How to test

1. Build the circuit in `wiring.md`. Check polarity on all three LEDs: long leg
   to the GPIO, short leg through the 330 Ω to GND.
2. Open `P3/P3.ino` and edit lines 5–6 to your own SSID and password.
3. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; select your port.
   Upload. Press the PROGRAM button if the output window sits at `Connecting…`.
4. Open Serial Monitor at 115200, wait for `WiFi connected.`, note the IP.
5. On a device joined to the same network, browse to that IP. Three rows appear,
   all reading `State off`, each with an ON button.
6. Press each ON button in turn: the matching LED lights, its row reads
   `State on`, and its button becomes OFF. Press OFF and the LED goes dark. The
   serial monitor echoes `GPIO 16 on`, `GPIO 32 off`, and so on.
7. Show all three LEDs lit at once, then all three off, so each button is
   visibly independent.

## Limitations

- Not hardware-tested. It compiles for `esp32:esp32:esp32` (55% program storage,
  13% dynamic memory) — compiling is not testing.
- Credentials are hard-coded, following the instructor's listing.
- No auto-refresh: a second browser sees stale state until reloaded.
- The server handles one client at a time.
- GPIO 32 is also an ADC and touch-capable pin, but nothing here uses those
  functions — it is driven as a plain digital output, as the homework requires.
