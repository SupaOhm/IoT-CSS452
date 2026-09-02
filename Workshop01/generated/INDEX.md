# Workshop01 — generated work

**Workshop 01 corresponds to Lecture Note 3.** The workshop numbering and the
lecture numbering differ; the supplied lecture file for this workshop is
`Lecture Note 3 - Introduction to ESP32.pdf`.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Status |
| --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 1.pdf` | Lecture Note 3, Example 1 (slides 26–27) | READY FOR REVIEW |
| `P1` | Homework | `CSS452 - Homework 1.pdf`, Problem 1 | Lecture Note 3, Example 3 (slides 35–36) | READY FOR REVIEW |
| `P2` | Homework | `CSS452 - Homework 1.pdf`, Problem 2 | Lecture Note 3, Example 8 (slides 54–56) | READY FOR REVIEW |
| `P3` | Homework | `CSS452 - Homework 1.pdf`, Problem 3 | Examples 4 + 6 + section 3.6 (slides 39–40, 48, 43) | **NEEDS CLARIFICATION** |

### Naming

Homework folders carry the instructor's own video names: `P1`, `P2`, `P3` are
Homework 1 Problems 1, 2 and 3, so the folder you open is the video you submit.
In-class work is `Exercise1`, numbered by task within `CSS452 - Exercise 1.pdf`;
the exercise sheet's own number follows the lecture note, not the workshop.

## Facts taken from the materials

All hardware facts below are sourced, not assumed.

| Fact | Value | Source |
| --- | --- | --- |
| Board | ThaiEasyElec's ESPino32 | Lecture Note 3, slide 18 |
| Serial baud | 115200 (explicitly "not 9600") | slides 19, 21 |
| Example 1 button pin | GPIO 34, with external 10 kΩ pull-up to 3v3, switch to GND | slide 26 |
| Example 1 LED pin | GPIO 17, 330 Ω to GND | slide 26 |
| Example 3 potentiometer | wiper to A0, ends to 3v3 and GND | slide 35 |
| Example 3 LED pin | GPIO 17, 330 Ω to GND | slide 35 |
| PWM settings | `freq = 5000`, `ledChannel = 0`, `resolution = 8` | slides 33, 36 |
| Analog input range | 0–3.3 V maps to 0–4095 | slide 28 |
| PWM-capable pins | GPIO 0–19, 21–23, 25–27, 32–33 | slide 32 |
| Touch pins | GPIO 0, 2, 4, 12, 13, 14, 15, 27, 32, 33 | slide 37 |
| Example 4 touch pin | GPIO 32, plain wire, no other components | slides 39–40 |
| `touchRead()` range | 0–1023; touched = low, untouched = high | slide 38 |
| NTP server | `pool.ntp.org` | slide 54 |
| Time zone | `gmtOffset_sec = 7*3600`, `daylightOffset_sec = 0` (Thailand) | slides 54, 57 |
| Software reset | `ESP.restart()` | slide 43 |

## Questions requiring instructor or student confirmation

These are **not** facts from the materials. They are unresolved.

| # | Task | Question | Detail |
| --- | --- | --- | --- |
| 1 | `P3` | What touch threshold separates touched from untouched? | Not stated anywhere. Slide 40 shows only sample values: roughly 38–46 untouched, 6–9 touched. `P3/P3.ino` uses `20` marked `UNCONFIRMED`. See `P3/QUESTIONS.md`. |
| 2 | `P3` | Homework Problem 3 says "look at Example 4 and Example 5" for restarting, but Example 5 (slide 42) is the Hall-effect sensor. `ESP.restart()` is in section 3.6 (slide 43), an unnumbered example. | Conflict between the two supplied documents; no side chosen. See `P3/QUESTIONS.md`. |
| 3 | `P1` | Potentiometer resistance value | Not stated in the material; none asserted in `P1/wiring.md`. |
| 4 | `P3` | The task references an attached demo video, `CSS452 - Homework 1 - Problem 3`. | Not supplied, so the demonstrated behaviour could not be checked. |
| 5 | all | ESP32 Arduino core version | Not stated. `P1` uses `ledcSetup`/`ledcAttachPin`, which exist in core 2.x but were replaced in core 3.x. |
| 6 | `Exercise1` | Exercise 1 states a due date of "20th Aug., before 11.59am" with no year. | Confirm the deadline still applies. |

## Material provenance

All three supplied PDFs converted cleanly to text (`markitdown`, fidelity
`CLEAN`); no OCR fallback was needed. See `../materials/INTAKE.md`.

However, **every code listing and circuit diagram in Lecture Note 3 is an
image**, so the extracted text contains no code. The instructor's listings and
circuits were read by rendering the relevant PDF pages and reading them
directly: slides 26, 27, 35, 36, 39, 40, 43, 48, 54, 55, 56.

## Superseded material

`materials/_superseded/interrupt-and-timing-reconstruction.md` was a placeholder
written before the real files arrived. Lecture Note 3 contains no interrupt or
`millis()` content, so it does not belong to this workshop and was not used.
The in-class task previously generated from it has been removed and replaced with the
real Exercise 1. See `materials/_superseded/README.md`.

## Completion status

| ID | Sketch | Wiring | README | Questions | Notes |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | `Exercise1/Exercise1.ino` | ✅ | ✅ | — | Reproduces `Digital_InOut.ino` (slide 27). |
| `P1` | `P1/P1.ino` | ✅ | ✅ | — | Reproduces `Analog_PWM.ino` (slide 36). Core-version caveat in README. |
| `P2` | `P2/P2.ino` | ✅ | ✅ | — | Reproduces `DateTimerNTP.ino` (slides 54–56). Needs your WiFi credentials. |
| `P3` | `P3/P3.ino` | ✅ | ✅ | `QUESTIONS.md` | Composed, not copied. Threshold unconfirmed. |

No sketch has been hardware-tested.

**Sketch convention.** A "do Example N" task is a verbatim transcription of the
instructor's listing — same lines, comments, spelling, and indentation, with no
header comment block. Task statement, circuit, board, baud, and caveats live in
each task's `README.md` and `wiring.md`. All sketches re-verified against the
slides and re-compiled on 2026-09-02.
