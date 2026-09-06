# Exercise1 — Exercise 3: ESP32 Web Server to Control Outputs

Status: READY FOR REVIEW

## Files in this folder

| File | What it is |
| --- | --- |
| `Exercise1/Exercise1.ino` | the sketch — open this folder in the Arduino IDE |
| `wiring.md` | circuit, pin table, component values |
| `page-leds-off.html` | the page the sketch serves while both LEDs are off |
| `page-leds-on.html` | the page the sketch serves while both LEDs are on |
| `README.md` | this file |

Everything the task needs is here; nothing has to be fetched from `materials/`.

**The `.html` files are not uploaded.** The ESP32 has no filesystem in this
project — the sketch prints the page with `client.println()` on every request
(`Exercise1.ino` lines 100–130). The two files are that same markup written out
so you can open it in a browser, read the CSS, or show the page design in your
video without powering the board. Both were generated from the sketch and
checked line by line against it.

They differ from the instructor's supplied `html example - Control code -ON.html`
and `-OFF.html`, which are hand-written illustrations rather than the sketch's
actual output. Two differences: the supplied files capitalise the state
(`State Off`) where the sketch prints `output26State` verbatim and so emits
`State off`; and in `-OFF.html` both OFF buttons link to `/26/on` and `/27/on`,
which would fail to switch a LED off. The sketch is correct — it emits
`/26/off` and `/27/off` in that state. The files here follow the sketch.

## Task

From `CSS452 - Exercise 3.pdf`:

> Do the project in Section 3 "ESP32 as a Local Web Server to Control Actuators".
> Take a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - Turn on and off the LED1 by pressing the button on the web page.
>   - Turn on and off the LED2 by pressing the button on the web page.

Submit the video to the Google Classroom. No due date is stated in the exercise.

## Behavior

The ESP32 joins your Wi-Fi network as a station, prints its IP address over
serial at 115200 baud, and listens on port 80.

When a browser connects, the sketch reads the request line by line into
`header` until it sees a blank line, then:

1. **Routes the request.** `header.indexOf("GET /26/on")` and its three siblings
   drive GPIO 26 and GPIO 27 HIGH or LOW and update `output26State` /
   `output27State`.
2. **Renders the page.** It prints an HTTP 200 response whose body shows
   `GPIO 26 - State on|off` and a single button per LED: an **ON** button while
   that output is off, an **OFF** button while it is on.
3. **Closes the connection.** `client.stop()`, and `header` is cleared for the
   next request.

Each button is an `<a href="/26/on">` link, so pressing it is an ordinary page
load — the browser navigates, the ESP32 acts on the URL and returns the updated
page in the same response. There is no JavaScript and no auto-refresh.

`timeoutTime = 2000` ms bounds how long the sketch will wait on a connected
client that stops sending.

## Source basis

`Exercise1.ino` is a **byte-identical copy** of the instructor's supplied
`WebServer_ControlOutputs.ino`. Nothing was added, removed, or reworded, and no
syntax fix was needed.

The supplied file is also the listing printed on slides 54–59, verified
line by line against rendered images of those slides — 151 lines, same order,
same comments, same spacing. One difference exists and it is the instructor's
own: the call-out box on **slide 53** prints lines 5–6 as
`const char* ssid = "Your SSID";` / `"Your Password"`, while both the full
listing on slide 54 and the supplied `.ino` carry his own network. The sketch
keeps the supplied file, so it matches the other three tasks in this workshop;
either way **you must replace lines 5–6 with your own SSID and password**, which
is what slide 53 step 2 tells you to do.

| Fact | Source |
| --- | --- |
| LED1 on GPIO 26, LED2 on GPIO 27 | slide 52 schematic; slide 54 code |
| 330 Ω per LED, long leg to the GPIO | slide 52 schematic |
| Web server on port 80 | slide 54 code |
| `WiFi.mode(WIFI_STA)` before `WiFi.begin()` | slide 55 code |
| Serial baud 115200 | slide 55 code |
| `timeoutTime = 2000` ms | slide 54 code |
| URL routes `/26/on`, `/26/off`, `/27/on`, `/27/off` | slide 57 code |
| Page markup and CSS classes `button` / `button2` | slides 58–59 code; `html example - Control code -ON.html` |
| Client and ESP32 must share one network | slides 40, 43 |

## How to test

1. Build the circuit in `wiring.md`. Check LED polarity on both: long leg to the
   GPIO, short leg through the 330 Ω to GND.
2. Open `Exercise1/Exercise1.ino` and edit lines 5–6 to your own SSID and
   password. The ESP32 cannot join a 5 GHz-only network — use a 2.4 GHz SSID.
3. Arduino IDE: Tools → Board → **ThaiEasyElec's ESPino32**; select your port.
   Upload. Press the PROGRAM button if the output window sits at `Connecting…`.
4. Open Serial Monitor at 115200. Wait for `WiFi connected.` and note the
   printed IP address.
5. On a phone or computer **joined to the same network**, browse to that IP.
   The page shows `GPIO 26 - State off` and `GPIO 27 - State off`, each with an
   ON button.
6. Press the GPIO 26 ON button: LED1 lights, the row reads `State on`, and the
   button becomes OFF. Press OFF: LED1 goes dark. Repeat for GPIO 27 / LED2.
   The serial monitor echoes `GPIO 26 on`, `GPIO 26 off`, and so on.

## Limitations

- Not hardware-tested. It compiles for `esp32:esp32:esp32` (55% program storage,
  13% dynamic memory) — compiling is not testing.
- Credentials are hard-coded in the sketch, as in the instructor's listing. They
  are visible on screen if you record the code with real values in place.
- The page does not refresh itself. If you change an LED from a second browser,
  the first browser shows a stale state until you reload.
- `header` is a `String` that grows for the whole request and is cleared only
  after the response. This is the instructor's design and is kept unchanged.
- The server handles one client at a time; a second browser waits.
