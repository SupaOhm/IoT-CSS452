# P1 — Homework 3 Problem 1: Web Server to Monitor Sensor Data

Status: READY FOR REVIEW

> **Video name:** `"P1"` — this folder is named after the video the
> instructor asks you to submit, so the two always match.

## Files in this folder

| File | What it is |
| --- | --- |
| `P1/P1.ino` | the sketch — open this folder in the Arduino IDE |
| `wiring.md` | circuit, pin table, component values |
| `page.html` | the page the sketch serves |
| `README.md` | this file |

Everything the task needs is here; nothing has to be fetched from `materials/`.

**`page.html` is not uploaded.** The ESP32 has no filesystem in this project —
the sketch prints the page with `client.println()` on every request (`P1.ino`
lines 66–85). The file is that same markup written out so you can open it in a
browser and see the table and its `1px solid black` borders without powering the
board. The value `2048` in the second row is a stand-in: the sketch prints
`analogRead(A0)` there, which is 0–4095 depending on where the knob sits. No
reading was measured.

## Task

From `CSS452 - Homework 3.pdf`, Problem 1:

> Do the project in Section 4 "ESP32 as a Local Web Server to Monitor Sensor
> Data". Take a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - The potentiometer value is shown on the webpage.
>   - The potentiometer value on the webpage is updated when we rotated the knob
>     of the potentiometer (you will need to press the refresh button on the web
>     browser).

Name your video as "P1" and submit to the Google Classroom.

## Behavior

The same web-server skeleton as `Exercise1`, with the output control removed and
a table added.

The ESP32 joins Wi-Fi, prints its IP at 115200 baud, and serves port 80. On each
request it returns a page containing one table:

| Sensor | Value |
| --- | --- |
| Potentiometer | `analogRead(A0)` |

`analogRead()` is called while the response is being written, so the number on
the page is the reading taken at that moment. The page is static once delivered —
**turning the knob changes nothing until you reload**, which is exactly what the
homework asks you to demonstrate with the browser's refresh button.

On the ESP32 the ADC is 12-bit by default, so the value spans 0–4095 across the
knob's travel.

## Source basis

`P1.ino` is a **byte-identical copy** of the instructor's supplied
`WebServer_MonitorSensor.ino`. Nothing was added, removed, or reworded, and no
syntax fix was needed.

The supplied file is also the listing printed on slides 78–82, verified line by
line against rendered images of those slides — 106 lines, same order, same
comments, same spacing, including the instructor's own SSID and password on
lines 5–6. Slide 77 step 2 tells you to replace those two lines with your own.

| Fact | Source |
| --- | --- |
| Potentiometer on pin A0, between 3v3 and GND | slide 76 schematic; slide 81 code |
| Web server on port 80 | slide 78 code |
| Serial baud 115200 | slide 79 code |
| `timeoutTime = 2000` ms | slide 78 code |
| Table markup `<table>` / `<th>` / `<tr>` / `<td>` | slides 72–75 text; slide 81 code |
| Table CSS `border: 1px solid black`, centred | slide 81 code |
| `analogRead(A0)` printed into the second row | slide 81 code |
| Refresh is required to update the value | slide 71 text; Homework 3 Problem 1 |
| Client and ESP32 must share one network | slides 40, 43 |

## How to test

1. Build the circuit in `wiring.md`.
2. Open `P1/P1.ino` and edit lines 5–6 to your own SSID and password. Use a
   2.4 GHz network — the ESP32 cannot join a 5 GHz-only SSID.
3. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; select your port.
   Upload. Press the PROGRAM button if the output window sits at `Connecting…`.
4. Open Serial Monitor at 115200, wait for `WiFi connected.`, note the IP.
5. On a device joined to the same network, browse to that IP. The page shows the
   table with a number in the Potentiometer row.
6. Turn the knob, then press the browser's refresh button. The number changes.
   Turn it fully both ways to show the range.

## Limitations

- Not hardware-tested. It compiles for `esp32:esp32:esp32` (56% program storage,
  13% dynamic memory) — compiling is not testing.
- Credentials are hard-coded in the sketch, as in the instructor's listing. They
  are visible on screen if you record the code with real values in place.
- No auto-refresh. The value is frozen until you reload, by design.
- The raw ADC count is displayed, not a voltage or a percentage. The lecture does
  not convert it and neither does this sketch.
- The server handles one client at a time.
