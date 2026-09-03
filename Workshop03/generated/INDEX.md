# Workshop03 — generated work

**Workshop 03 corresponds to Lecture Note 5** (`ESP32 – Web Servers and
Clients`). As in Workshops 01 and 02, the workshop number and the lecture number
differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Status — materials incomplete, no tasks generated yet

The lecture note and the instructor's example code have been filed. **The
exercise sheet and the homework sheet have not been dropped yet**, so there is
no task statement to work from and no `Exercise*/` or `P*/` folder has been
created. This file records what the materials say so that generation can start
the moment the remaining sheets arrive.

| Material | State |
| --- | --- |
| Lecture Note 5 (PDF) | received |
| Instructor example sketches (3 × `.ino`) | received |
| Instructor example web pages (2 × `.html`) | received |
| In-class exercise sheet | **not yet dropped** |
| Homework sheet | **not yet dropped** |

## Tasks

| ID | Type | Source | Based on | Status |
| --- | --- | --- | --- | --- |
| — | In-class | exercise sheet not yet supplied | — | AWAITING MATERIAL |
| — | Homework | homework sheet not yet supplied | — | AWAITING MATERIAL |

### Naming

Once the sheets arrive, homework folders take the instructor's own video names
(`P1`, `P2`, …), so the folder you open is the video you submit. In-class work is
`Exercise1`, `Exercise2`, … numbered by task within the workshop's exercise
sheet; the sheet's own number follows the lecture note, not the workshop.

**Sketch convention.** A "do Example N" task is a verbatim transcription of the
instructor's listing — same lines, comments, spelling, and indentation, with no
header comment block. Task statement, circuit, board, baud, and caveats live in
each task's `README.md` and `wiring.md`.

## Instructor example programs

All three sketches were supplied as `.ino` source (fidelity `NATIVE`), so the
files themselves — not the slide images — are the listing to transcribe from.

| Sketch | Lecture section | Listing slides | What it does |
| --- | --- | --- | --- |
| `WebServer_ControlOutputs.ino` | 3.2 | 53–59 | ESP32 hosts a page with ON/OFF buttons for two LEDs |
| `WebServer_MonitorSensor.ino` | 4.1 | 77–82 | ESP32 hosts a page showing a potentiometer reading in a table |
| `WebClient_ThingSpeak.ino` | 5.2 | 97–101 | ESP32 posts a potentiometer reading and a random number to ThingSpeak every 10 s |

The two `.html` files are the web pages section 3.2 serves, captured in their
OFF and ON states. They are the same markup the sketch prints from
`client.println(...)`.

## Facts taken from the materials

| Fact | Value | Source |
| --- | --- | --- |
| Lecture outline | 1 web servers · 2 HTML/CSS · 3 server to control outputs · 4 server to monitor sensor · 5 web client · 6 advanced | LN5 slide 2 |
| Control-outputs circuit | LED1 on GPIO 26, LED2 on GPIO 27; long leg to the GPIO, short leg through 330 Ω to GND | LN5 slide 52 (schematic image) |
| Monitor-sensor circuit | potentiometer: one end to 3v3, wiper to A0, other end to GND | LN5 slide 76 (schematic image) |
| ThingSpeak circuit | identical to the monitor-sensor circuit | LN5 slide 96 (schematic image) |
| Web server port | 80 — `WiFiServer server(80)` | `WebServer_ControlOutputs.ino` |
| HTTP client timeout | `timeoutTime = 2000` ms | `WebServer_ControlOutputs.ino`, `WebServer_MonitorSensor.ino` |
| Serial baud | 115200 | all three supplied sketches |
| Wi-Fi mode for the servers | `WiFi.mode(WIFI_STA)` before `WiFi.begin(ssid, password)` | both `WebServer_*.ino` |
| URL routing | `header.indexOf("GET /26/on")` and the three siblings | `WebServer_ControlOutputs.ino` |
| ThingSpeak send interval | every 10 seconds (`timerDelay = 10000`) | LN5 slides 89, 102; `WebClient_ThingSpeak.ino` |
| ThingSpeak request shape | `http://api.thingspeak.com/update?api_key=…&field1=…&field2=…` | LN5 slide 92; `WebClient_ThingSpeak.ino` |
| ThingSpeak payload | `analogRead(A0)` in `field1`, `random(100)` in `field2` | `WebClient_ThingSpeak.ino` |
| Client libraries | `WiFi.h`, and `HTTPClient.h` for the cloud client | supplied sketches |
| Board | ThaiEasyElect ESPino32 — the board photographed on slides 52, 76, 96 and named in Lecture Note 3, slide 18 | LN3 slide 18; LN5 board photos |

## Conversion notes

- `Lecture Note 5 …pdf` converted `CLEAN`, but **every code listing and every
  schematic in it is an image**: the extracted text contains no `WiFiServer`,
  no `setup()`, no `analogRead`. Facts above that come from a slide were read by
  rendering that page (`pdftoppm -f N -l N -r 150 -png`), not from the text.
- The two `.html` files converted `CLEAN` as *rendered pages*, which strips the
  markup they exist to show. The originals in `02_example-code/` are the source
  of truth for their HTML and CSS; the `.converted/` copies are not usable for
  this file type.

## Open questions

Nothing here blocks generation of an unsupplied task; these are the points to
settle when the sheets arrive.

| # | Question | Why it matters |
| --- | --- | --- |
| 1 | Which physical pin is `A0` on the ESPino32? | The lecture and all three sketches say `A0`, and the schematic just labels the pin `A0`. The Arduino ESP32 core resolves `A0` for you, so the code is correct as written, but `wiring.md` cannot name a GPIO number or a silkscreen label without confirming it against the board's pinout. Not guessed. |
| 2 | Does the student have a ThingSpeak account and channel? | `WebClient_ThingSpeak.ino` ships with the instructor's own API key. Any submitted work must use the student's own channel key, and the write-API limits apply per channel. |
| 3 | Which Wi-Fi network will the demo run on? | The supplied sketches hard-code the instructor's SSID and password. Both need replacing, and the client device must be on the same network as the ESP32 for the two web-server projects (LN5 slides 40, 43). |

## Next step

Drop the exercise sheet and the homework sheet into `dropper/` and say
`do Workshop03`. Intake will file them into `03_in-class-exercises/` and
`04_homework/`, this file will be rewritten with the real task table, and the
task folders will be generated.
