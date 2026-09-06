# P2 — Homework 3 Problem 2: Sending ESP32 Data to the ThingSpeak Cloud

Status: READY FOR REVIEW

> **Video name:** `"P2"` — this folder is named after the video the
> instructor asks you to submit, so the two always match.

## Files in this folder

| File | What it is |
| --- | --- |
| `P2/P2.ino` | the sketch — open this folder in the Arduino IDE |
| `wiring.md` | circuit, pin table, component values |
| `README.md` | this file |

Everything the task needs is here; nothing has to be fetched from `materials/`.

**There is no `.html` file for this task, and none is missing.** P2 is the only
task in Workshop03 where the ESP32 is a *client*, not a server: it posts to
`api.thingspeak.com/update` every 10 s and serves no page of its own. The
display is the ThingSpeak channel's own charts in your browser, which
ThingSpeak renders — the demonstration in your video is that site, not a page
this sketch produces.

## Task

From `CSS452 - Homework 3.pdf`, Problem 2:

> Do the project in Section 5.2 "Sending ESP32 Data to the ThingSpeak Cloud".
> Take a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - The potentiometer value and a random number are shown on the ThingSpeak
>     charts.

Name your video as "P2" and submit to the Google Classroom.

## Behavior

Here the ESP32 is a **client**, not a server. There is no local web page.

`setup()` joins Wi-Fi and prints the IP at 115200 baud. `loop()` compares
`millis()` against `lastTime` and, every `timerDelay = 10000` ms:

1. Checks `WiFi.status() == WL_CONNECTED`.
2. Builds the request string
   `serverName + "&field1=" + analogRead(A0) + "&field2=" + random(100)`,
   where `serverName` already ends in `?api_key=…`.
3. Prints the full URL to serial, sends it with `http.GET()`, prints the HTTP
   response code, and calls `http.end()`.

ThingSpeak stores each pair and plots `field1` and `field2` on two charts in
your channel. A successful write returns a response code of `200`; the body is
the new entry number.

## Source basis

`P2.ino` is a **byte-identical copy** of the instructor's supplied
`WebClient_ThingSpeak.ino`. Nothing was added, removed, or reworded, and no
syntax fix was needed.

The supplied file is also the listing printed on slides 98–101, verified line by
line against rendered images of those slides — 66 lines, same order, same
comments, same spacing, including the instructor's own SSID, password and Write
API key. Slide 97 steps 2 and 3 tell you to replace them.

| Fact | Source |
| --- | --- |
| Potentiometer on pin A0, between 3v3 and GND | slide 96 schematic; slide 100 code |
| `WiFi.h` plus `HTTPClient.h` | slide 98 code |
| Request shape `…/update?api_key=…&field1=…&field2=…` | slide 92 text; slides 98, 100 code |
| `field1` = `analogRead(A0)`, `field2` = `random(100)` | slide 100 code |
| Send every 10 seconds (`timerDelay = 10000`) | slides 89, 102 text; slide 98 code |
| Serial baud 115200 | slide 99 code |
| ESP32 is the client, ThingSpeak the server | slides 89, 91 |

## Before you upload — three lines to change

| Line | What to put there | Told by |
| --- | --- | --- |
| 5 | your SSID | slide 97 step 2 |
| 6 | your password | slide 97 step 2 |
| 9 | **your own** ThingSpeak Write API Key, in place of the key after `api_key=` | slide 97 step 3 |

Line 9 matters most. The sketch ships with the instructor's key, so leaving it
alone writes your readings into **his** channel and nothing appears on yours.
Create a free ThingSpeak channel with at least two fields and copy its Write API
Key from the channel's API Keys tab.

## How to test

1. Build the circuit in `wiring.md` — identical to `P1`, so you can leave the
   breadboard untouched between the two recordings.
2. Create your ThingSpeak channel and enable Field 1 and Field 2.
3. Open `P2/P2.ino`, edit lines 5, 6 and 9 as above.
4. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; select your port.
   Upload. Press the PROGRAM button if the output window sits at `Connecting…`.
5. Open Serial Monitor at 115200. After the connect message, wait 10 seconds for
   the first request. Each cycle prints the full URL and then
   `HTTP Response code: 200`.
6. Open your channel's Private View. Two charts appear; a new point lands on
   each every 10 seconds. Turn the knob between sends so the Field 1 chart
   visibly tracks it while Field 2 stays random.

## Limitations

- Not hardware-tested. It compiles for `esp32:esp32:esp32` (59% program storage,
  14% dynamic memory) — compiling is not testing.
- The sketch carries the instructor's Wi-Fi credentials and Write API key
  verbatim. They are visible on screen if you record the code before editing it,
  and the key is a live credential for someone else's channel — replace it first.
- ThingSpeak's free tier rate-limits writes to one every 15 seconds. The
  instructor's 10-second timer is faster than that, so some requests may be
  rejected. The listing's own comment on lines 13–14 warns about API call limits.
- `random(100)` is never seeded, so the Field 2 sequence repeats after a reset.
  This is the instructor's code and is kept unchanged.
- The request is plain HTTP, not HTTPS: the API key travels in clear text.
