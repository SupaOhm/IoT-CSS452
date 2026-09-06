# Workshop03 — generated work

**Workshop 03 corresponds to Lecture Note 5** (`ESP32 – Web Servers and
Clients`). As in Workshops 01 and 02, the workshop number and the lecture number
differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Status |
| --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 3.pdf` | Lecture Note 5, Section 3 (slides 52–59) | READY FOR REVIEW |
| `P1` | Homework | `CSS452 - Homework 3.pdf`, Problem 1 | Lecture Note 5, Section 4 (slides 76–82) | READY FOR REVIEW |
| `P2` | Homework | `CSS452 - Homework 3.pdf`, Problem 2 | Lecture Note 5, Section 5.2 (slides 96–101) | READY FOR REVIEW |
| `P3` | Homework | `CSS452 - Homework 3.pdf`, Problem 3 | Section 3 revised for three LEDs | READY FOR REVIEW |

### Naming

Homework folders carry the instructor's own video names: `P1`, `P2`, `P3` are
Homework 3 Problems 1, 2 and 3, so the folder you open is the video you submit.
In-class work is `Exercise1`, numbered by task within `CSS452 - Exercise 3.pdf`;
the exercise sheet's own number follows the lecture note, not the workshop.

**Sketch convention.** A "do the project in Section N" task is a verbatim
transcription of the instructor's listing — same lines, comments, spelling and
indentation, with no header comment block. Task statement, circuit, board, baud
and caveats live in each task's `README.md` and `wiring.md`.

## Completion

| Task | Sketch | Lines | Compiles (`esp32:esp32:esp32`) | Flash | RAM |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | `Exercise1/Exercise1/Exercise1.ino` | 151 | yes | 55% | 13% |
| `P1` | `P1/P1/P1.ino` | 106 | yes | 56% | 13% |
| `P2` | `P2/P2/P2.ino` | 66 | yes | 59% | 14% |
| `P3` | `P3/P3/P3.ino` | 172 | yes | 55% | 13% |

None is hardware-tested. Compiling is not testing.

### What each task folder holds

Every folder is a complete package — sketch, wiring, the page the sketch serves,
and a README. Nothing has to be pulled out of `materials/` to work on a task.

| Task | Sketch | Wiring | Page files | README |
| --- | --- | --- | --- | --- |
| `Exercise1` | yes | yes | `page-leds-off.html`, `page-leds-on.html` | yes |
| `P1` | yes | yes | `page.html` | yes |
| `P2` | yes | yes | none — see below | yes |
| `P3` | yes | yes | `page-leds-off.html`, `page-leds-on.html` | yes |

The `.html` files are **not uploaded to the board**. These projects keep no
filesystem on the ESP32: the sketch prints the whole document with
`client.println()` on every request. Each file is that same markup written out
so the page can be opened in a browser, read, or shown in a video without
powering the board. Each was generated from its sketch and diffed against it
line by line; `P1/page.html` carries `2048` where the sketch prints
`analogRead(A0)`, a stand-in, not a measured reading.

`P2` has no page because the ESP32 is a **client** there, not a server: it posts
to `api.thingspeak.com/update` and ThingSpeak renders the charts.

**Section 2 of the lecture note is covered by these files.** Slides 13–37 are a
step-by-step HTML/CSS walkthrough — create `index.html`, add a title, heading,
paragraph, buttons, hyperlinks, then CSS syntax, the `html` selector, `.button`,
`.button2`, and metadata. Its end product is the two-LED control page, which is
exactly what `Exercise1/page-leds-*.html` hold. Neither `CSS452 - Exercise 3.pdf`
nor `CSS452 - Homework 3.pdf` sets a task from Section 2, so it has no task ID of
its own.

## Circuits at a glance

| Task | Circuit |
| --- | --- |
| `Exercise1` | LED1 on GPIO 26, LED2 on GPIO 27, 330 Ω each to GND |
| `P1` | potentiometer only — 3v3 / wiper to A0 / GND |
| `P2` | **identical to `P1`** |
| `P3` | LED1 GPIO 16, LED2 GPIO 17, LED3 GPIO 32, 330 Ω each to GND |

Recording order that minimises rewiring: `P1` → `P2` (same breadboard, change
only the sketch) → `Exercise1` → `P3` (both LED circuits, `P3` adds one LED and
moves the pins).

Every task also needs a 2.4 GHz Wi-Fi network with the browser device joined to
the same network as the ESP32 (slides 40, 43). `P2` additionally needs a
ThingSpeak account and channel.

## Three sketches are copies, one is written

`Exercise1`, `P1` and `P2` are **byte-identical copies** of the instructor's
supplied `.ino` files. Each was also checked line by line against the rendered
slide images of its listing:

| Task | Supplied file | Listing slides | Result |
| --- | --- | --- | --- |
| `Exercise1` | `WebServer_ControlOutputs.ino` | 54–59 | matches, except lines 5–6 (see below) |
| `P1` | `WebServer_MonitorSensor.ino` | 78–82 | matches exactly |
| `P2` | `WebClient_ThingSpeak.ino` | 98–101 | matches exactly |

`P3` is the only written task. The homework says "revise the Arduino code in
Section 3", so it is `WebServer_ControlOutputs.ino` with the pins changed to
GPIO 16/17/32, a third output added in `setup()`, two more routing branches, and
a third state-and-button block in the page. Nothing else was touched and no new
technique was introduced.

## Facts taken from the materials

| Fact | Value | Source |
| --- | --- | --- |
| Board | ThaiEasyElect's ESPino32 | Lecture Note 3, slide 18; board photos on LN5 slides 52, 76, 96 |
| Serial baud | 115200 | LN5 slides 55, 79, 99 |
| Web server port | 80 — `WiFiServer server(80)` | LN5 slides 54, 78 |
| Client timeout | `timeoutTime = 2000` ms | LN5 slides 54, 78 |
| Station mode | `WiFi.mode(WIFI_STA)` before `WiFi.begin()` | LN5 slides 55, 79 |
| Section 3 circuit | LED1 GPIO 26, LED2 GPIO 27, long leg to GPIO, short leg through 330 Ω to GND | LN5 slide 52 (schematic image) |
| Section 3 routing | `header.indexOf("GET /26/on")` and three siblings | LN5 slide 57 |
| Section 3 page | one button per LED; `button` green, `button2` grey | LN5 slides 58–59; `html example - Control code -{ON,OFF}.html` |
| Section 4 circuit | potentiometer: 3v3 — wiper to A0 — GND | LN5 slide 76 (schematic image) |
| Section 4 page | one table, `border: 1px solid black`, centred | LN5 slide 81 |
| Section 4 value | `analogRead(A0)` printed into the second row | LN5 slide 81 |
| Refresh required to update the reading | stated | LN5 slide 71; Homework 3 Problem 1 |
| Section 5.2 circuit | identical to Section 4 | LN5 slide 96 (schematic image) |
| ThingSpeak request | `http://api.thingspeak.com/update?api_key=…&field1=…&field2=…` | LN5 slide 92; slide 98 |
| ThingSpeak payload | `field1` = `analogRead(A0)`, `field2` = `random(100)` | LN5 slide 100 |
| ThingSpeak interval | every 10 s (`timerDelay = 10000`) | LN5 slides 89, 102; slide 98 |
| Same-network requirement | ESP32 and browser on one local network | LN5 slides 40, 43 |
| `P3` circuit | LED1 GPIO 16, LED2 GPIO 17, LED3 GPIO 32, 330 Ω each | Homework 3 Problem 3 schematic |
| `P3` page | three rows: `GPIO 16 / 17 / 32 - State off`, one button each | Homework 3 Problem 3 mock-up |

## Conversion notes

- `Lecture Note 5 …pdf` converted `CLEAN`, but **every code listing and every
  schematic in it is an image**: the extracted text contains no `WiFiServer`, no
  `setup()`, no `analogRead`. Every slide-sourced fact above was read by
  rendering that page (`pdftoppm -f N -l N -r 150 -png`), not from the text.
  Slides read: 45, 52, 53–59, 76, 77–82, 96, 97–101.
- `CSS452 - Homework 3.pdf` converted `CLEAN` for its prose, but Problem 3's
  schematic and page mock-up are images; the extracted text flattens the diagram
  into `ESP32330LED116Pin GND of ESP32…`. Page 1 was rendered and read.
- The two `.html` files converted `CLEAN` as *rendered pages*, which strips the
  markup they exist to show. The originals in `02_example-code/` are the source
  of truth for their HTML and CSS.

## Open questions and notes

None of these blocks a task; all four are READY FOR REVIEW.

| # | Item | Detail |
| --- | --- | --- |
| 1 | **Credentials must be replaced before uploading** | All four sketches carry the instructor's SSID and password on lines 5–6, and `P2` carries his ThingSpeak Write API Key on line 9. Slides 53, 77 and 97 tell you to fill in your own. Leaving `P2` line 9 alone writes your readings into his channel. |
| 2 | Section 3's two sources disagree on lines 5–6 | The call-out box on **slide 53** prints `const char* ssid = "Your SSID";` / `"Your Password";`, while the full listing on **slide 54** and the supplied `WebServer_ControlOutputs.ino` both carry the instructor's own network. Slides 78 and 98 carry his network too. `Exercise1.ino` follows the supplied file, so all four sketches in this workshop are consistent and each is byte-identical to a file the instructor supplied. Either way item 1 applies. |
| 3 | `A0` is never given as a GPIO number | The Section 4 and 5.2 schematics label the pin `A0` and the code says `analogRead(A0)`; neither the lecture nor the sketches name a GPIO. Wire to the pin your board labels `A0` — the Arduino ESP32 core resolves the name. No GPIO number was invented. |
| 4 | The potentiometer's resistance is not stated | Slides 76 and 96 label the part only as "Potentiometer". Any common linear pot divides 3.3 V the same way and the sketch does not depend on the value. |
| 5 | The supplied `-OFF.html` links its OFF buttons to `/26/on` | `html example - Control code -OFF.html` shows both OFF buttons as `<a href="/26/on">` and `<a href="/27/on">`, which would not switch a LED off, and it capitalises the state as `State Off` where the sketch prints `output26State` and so emits `State off`. The supplied `.html` files are hand-written illustrations of the design, not the sketch's output; the sketch itself is correct. `Exercise1/page-leds-*.html` follow the sketch. Nothing to fix in any `.ino`. |
| 6 | ThingSpeak free-tier rate limit | The free tier accepts one write per 15 s; the instructor's `timerDelay` is 10 s, so some `P2` requests may be rejected. The listing's own comment on lines 13–14 warns about API call limits. Kept unchanged. |
