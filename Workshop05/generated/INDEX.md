# Workshop05 — generated work

**Workshop 05 corresponds to Lecture Note 8** (`Introduction to Raspberry Pi`).
Lecture Note 7 was never dropped, so the gap between workshop and lecture
numbers widens from two to three.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

**Platform change.** Workshops 01–04 were ESP32 + Arduino C++. Workshop05 is
**Raspberry Pi 4 + Python 3** (gpiozero, guizero, requests). There are no
`.ino` sketches and no `arduino-cli` compile this time.

## Tasks

| ID | Type | Source | Based on | Video name | Status |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 5`, task 1 | LN8 §2 (slides 11–28) + supplementary | *(none given)* | READY FOR REVIEW |
| `Q1` | Homework | `CSS452 - Homework 5`, Problem 1 | LN8 Example 1 (slides 41–42) | `Q1` | READY FOR REVIEW |
| `Q2` | Homework | `CSS452 - Homework 5`, Problem 2 | LN8 Example 3 (slides 46–47) | `Q2` | READY FOR REVIEW |
| `Q3` | Homework | `CSS452 - Homework 5`, Problem 3 | LN8 Example 4 (slides 52–55) | `Q3` | READY FOR REVIEW |
| `Q4` | Homework | `CSS452 - Homework 5`, Problem 4 | LN8 Example 6 (slides 60–67) | `Q4` | READY FOR REVIEW |
| `Q5` | Homework | `CSS452 - Homework 5`, Problem 5 | LN8 Example 8 (slides 73–74) | `Q5` | READY FOR REVIEW |

Homework 5 says "Set the video name "Q1"" … "Q5", so the folders are `Q1`–`Q5`.
Exercise 5 names no video, so **no name collides** this time (contrast
Workshop04's two `Q1`s).

Examples 2, 5 and 7 are in the lecture but not assigned, so they were not
generated.

### What the task folders hold

```
Exercise1/  README.md  wiring.md            macOS access walkthrough, no code
Q1/         Q1.py  README.md  wiring.md     LED on/off (gpiozero LED)
Q2/         Q2.py  README.md  wiring.md     brightness from input (PWMLED)
Q3/         Q3.py  README.md  wiring.md     switch → LED (Button.is_pressed)
Q4/         Q4.py  README.md  wiring.md     GUI On/Off (guizero)
Q5/         Q5.py  README.md  wiring.md     random int → ThingSpeak (requests)
```

**Layout deviation:** the program sits directly in the task folder (`Q1/Q1.py`),
not in a nested `Q1/Q1/` subfolder. The nesting rule exists because the Arduino
IDE requires a sketch folder named after the sketch. Thonny has no such rule,
and the scripts are copied to the Pi individually anyway.

No task has a companion file: no served web page, data file or config. Q4's GUI
is built entirely in code, and Q5's ThingSpeak channel is configured in the
browser.

## Completion

| Task | File | Lines | `py_compile` | Mock-GPIO run | Hardware |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | — (setup only) | — | — | — | SSH + TigerVNC desktop confirmed 2026-10-21; Thonny/video pending |
| `Q1` | `Q1/Q1.py` | 12 | yes | GPIO22 on 0 s / off 2 s / on 4 s | not tested |
| `Q2` | `Q2/Q2.py` | 8 | yes | duty followed inputs 0.25 → 1.0 → 0 | not tested |
| `Q3` | `Q3/Q3.py` | 10 | yes | GPIO22 followed GPIO18 low/high | not tested |
| `Q4` | `Q4/Q4.py` | 21 | yes | not run (needs a Tk display) | not tested |
| `Q5` | `Q5/Q5.py` | 16 | yes | not run (would POST to ThingSpeak) | not tested |

Mock runs used gpiozero's `MockFactory` with `MockPWMPin` on the Mac, inside a
scratch virtualenv. They show the scripts drive the right pins in the right
order. They do not show an LED lights.

## Transcription sources

All five programs are **verbatim transcriptions** ("Do the Example N in Lecture
Note 8"). Every listing is an **image**: the converted text has none of them.
Pages were rendered with `pdftoppm` and read.

| Task | Listing | Circuit |
| --- | --- | --- |
| `Q1` | slide 42 | slide 41 |
| `Q2` | slide 47 | slide 41, by reference from slide 47 |
| `Q3` | slide 55 | slide 54 |
| `Q4` | slide 67 | slide 66 |
| `Q5` | slide 74 (re-rendered at 250 dpi, red arrow over lines 1–5) | none (slide 73) |

No syntax fixes were needed. Indentation is 4 spaces throughout, as rendered.

## Facts taken from the materials

| Fact | Value | Source |
| --- | --- | --- |
| Board | Raspberry Pi 4 Model B | LN8 slides 6–8 |
| OS on the supplied SD card | Raspberry Pi OS, pre-installed | LN8 slide 12 |
| Python version | 3.7.3 (→ Buster) on the slides; the course card actually runs Bullseye | LN8 slide 32; `/etc/os-release` on the card, 2026-10-21 |
| Default login | `pi` / `raspberry` | LN8 slides 12, 21, 26 |
| Pin numbering in code | BCM / GPIO number, not physical | LN8 slides 9–10 |
| GPIO22 = physical 15; GPIO18 = physical 12; GND = 6, 9, 14, 20, 25, 30, 34, 39 | | LN8 slide 9 pinout |
| GPIO logic level | 3.3 V max; ≥1.8 V reads HIGH | LN8 slide 10 |
| PWM | software PWM on all pins; hardware on 12, 13, 18, 19 | LN8 slide 10 |
| LED circuit | GPIO22 → LED → 330 Ω → GND | LN8 slides 41, 54, 66 |
| Switch circuit | GPIO18 → switch → GND, internal pull-up, "no resistor is needed" | LN8 slide 54 |
| IDE | Thonny, Menu → Programming | LN8 slides 31–32 |
| Library | gpiozero ("We will use this library in this course") | LN8 slide 33 |
| guizero install | `sudo pip3 install guizero` or `sudo apt install python3-guizero` | LN8 slide 60 |
| ThingSpeak channel | name `Lect8 – Ex8`, Field 1 `Random Integer` | LN8 slide 73 |
| Access tools | Putty + VNC Viewer over Ethernet | LN8 slide 14 |
| macOS internet sharing | Sharing → Internet Sharing, Wi-Fi → wired LAN | LN8 slide 19 |

### Not from the materials: the macOS route for `Exercise1`

Lecture Note 8 §2 targets Windows (PuTTY, RealVNC Viewer). Only slide 19 covers
macOS, and it covers only Internet Sharing. `Exercise1/README.md` substitutes:

| Slides | macOS replacement | Basis |
| --- | --- | --- |
| PuTTY | `ssh pi@raspberrypi.local` | OpenSSH ships with macOS |
| VNC Viewer | TigerVNC (open source, installed) **or** RealVNC Viewer (installed) **or** Screen Sharing | — |
| — | RealVNC Server switched to `Authentication=VncAuth` so TigerVNC / Screen Sharing can connect | [RealVNC help article](https://help.realvnc.com/hc/en-us/articles/10406396398877-How-do-I-connect-from-a-non-RealVNC-VNC-Viewer-to-RealVNC-Server-on-a-Raspberry-Pi) |

The Exercise 5 sheet asks you to *show access*, not to use particular
programs, so this does not change the task. It is still a departure from the
slides; see open question 1.

## Conversion notes

- All four PDFs converted `CLEAN`. The text layer is fine, but **every code
  listing and every circuit diagram in Lecture Note 8 is an image**. Extraction
  turns the schematics into vertical letter soup (e.g. slide 54 becomes
  `I S f W n o …`). Slides 9, 19, 32, 41, 42, 47, 54, 55, 66, 67 and 74 were
  rendered and read; nothing was reconstructed from prose.
- `Lecture Note 8 - Supplementary … with Notes (1).pdf` is a printed web article
  (beebom.com) with the instructor's handwritten notes. The extraction mixes in
  ad text and garbles the handwriting. The notes that matter were read off the
  extracted fragments: "No need to do this step", "Your SD card already has
  OS", "Our technician did this" for the `ssh` file, and "Do this update when
  you have time". They agree with slides 12 and 20. No GPIO numbers, values
  or timings depend on this file.
- The exercise sheet was rendered to read its figure: a RealVNC Viewer window
  titled `raspberrypi.local (raspberrypi) - VNC Viewer`, showing Menu →
  Programming → Thonny Python IDE.

## Open questions and notes

Nothing blocks any task; all six are READY FOR REVIEW.

| # | Item | Detail |
| --- | --- | --- |
| 1 | **Is a non-PuTTY/VNC-Viewer route acceptable?** | The sheet says "show Raspberry Pi desktop and Thonny Python program similar to the figure". The figure's title bar reads "VNC Viewer". TigerVNC or Screen Sharing gives a different title bar. If you want zero risk, use RealVNC Viewer (installed as *RealVNC Connect*); it needs no Pi change. |
| 2 | Screen recording or camera video? | Exercise 5 says "Take a video". It doesn't say whether a Mac screen recording is enough or whether it wants the laptop and Pi in frame. Homework Q1–Q4 need a camera anyway, for "circuit connection". |
| 3 | ~~OS on the SD card is inferred~~ **Resolved** | Checked on the card 2026-10-21: `Raspbian GNU/Linux 11 (bullseye)`, RealVNC Server. Newer than slide 32's Python 3.7.3 / Buster, so expect Python 3.9 in Thonny's Shell. The listings are unaffected. |
| 4 | Lecture Note 7 is missing | No LN7 material was dropped. Nothing in Workshop05 needs it; noted only for the numbering map. |
| 5 | Q4 and Q5 need internet on the Pi | Q4 to install guizero (slide 60), Q5 to reach ThingSpeak (slide 74). Set up Internet Sharing during Exercise1. |
| 6 | **Q5's real API key must not be committed** | `Q5.py` keeps the instructor's `'Your Write API Key'` placeholder. Edit the copy on the Pi. |
| 7 | Q2 accepts no out-of-range input | Typing text or a value outside 0–1 crashes the program, as the listing does. Keep to 0.0–1.0 on video. |
