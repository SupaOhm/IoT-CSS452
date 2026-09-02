# Workshop02 — generated work

**Workshop 02 corresponds to Lecture Note 4** (`ESP32 – Multitasking and Deep
Sleep`). As in Workshop 01, the workshop number and the lecture number differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Status |
| --- | --- | --- | --- | --- |
| `P1` | In-class | `CSS452 - Exercise 2.pdf` | Lecture Note 4, Example 2 (slides 15–17) | READY FOR REVIEW |
| `HW1` | Homework | `CSS452 - Homework 2.pdf`, Problem 1 | Lecture Note 4, Example 5 (slides 34–36) | READY FOR REVIEW |
| `HW2` | Homework | `CSS452 - Homework 2.pdf`, Problem 2 | Lecture Note 4, Example 9 (slides 57–58) | READY FOR REVIEW |
| `HW3` | Homework | `CSS452 - Homework 2.pdf`, Problem 3 | Example 5 revised, plus Examples 2 and 7 | READY FOR REVIEW |

### Video naming — read this before submitting

The instructor asks for homework videos named `P1`, `P2`, `P3`. This repository
uses `P` for in-class problems, so folder names and video names differ:

| Folder here | Submit video as | Task |
| --- | --- | --- |
| `P1` | (video name not specified) | Exercise 2, in-class |
| `HW1` | `P1` | Homework 2, Problem 1 |
| `HW2` | `P2` | Homework 2, Problem 2 |
| `HW3` | `P3` | Homework 2, Problem 3 |

## Circuits at a glance

Three of the four tasks share one breadboard; only HW2 differs.

| Task | Circuit |
| --- | --- |
| `P1` | SW on GPIO 34 (10 kΩ), LED1 on GPIO 16 (330 Ω), LED2 on GPIO 17 (330 Ω) |
| `HW1` | identical to `P1` |
| `HW2` | **different** — SW on GPIO 32 (10 kΩ) only, no LEDs |
| `HW3` | `HW1` plus SW1 on GPIO 26 (10 kΩ) |

Recording order that minimises rewiring: `P1` → `HW1` → `HW3` → `HW2`.

## Facts taken from the materials

| Fact | Value | Source |
| --- | --- | --- |
| Board | ThaiEasyElec's ESPino32 | Lecture Note 3, slide 18 |
| Serial baud | 115200 | Lecture Note 4, slides 36, 58 |
| Shared circuit | SW GPIO 34 (10 kΩ pull-up to 3v3), LED1 GPIO 16, LED2 GPIO 17, 330 Ω each | LN4 slides 4, 9, 15, 24, 34 |
| Switch polarity | pressing gives LOW logic at the pin | LN4 slide 4 |
| Blink interval | `interval = 2000` ms | LN4 slides 10, 16, 25 |
| Interrupt syntax | `attachInterrupt(digitalPinToInterrupt(GPIO), function, mode)` | LN4 slide 13 |
| Interrupt-capable pins | all GPIO except GPIO6–GPIO11 | LN4 slide 14 |
| Core reporting | `xPortGetCoreID()` | LN4 slide 28 |
| Core pinning | `xTaskCreatePinnedToCore(fn, name, 1024, NULL, 1, NULL, core)` | LN4 slide 36 |
| Core assignment | TimerLED → Core 0, SwitchLED → Core 1 | LN4 slides 34, 36 |
| Deep sleep | `esp_deep_sleep_start()` | LN4 slide 45 |
| Timer wake-up | `esp_sleep_enable_timer_wakeup(X*1000000)`, X in seconds | LN4 slides 49, 50 |
| ext0 wake-up | `esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, LOW)` | LN4 slides 56, 58 |
| ext0-capable pins | GPIO 0, 2, 4, 12–15, 25–27, 32–39 | LN4 slide 56 |
| RTC-persistent variable | `RTC_DATA_ATTR` | LN4 slide 44 |
| Wake-up arms before sleeping | required | LN4 slide 48, Remark 2 |
| Waking is a reset | program restarts from the beginning | LN4 slides 44, 45 |
| HW3 extra switch | SW1 on GPIO 26, 10 kΩ pull-up to 3v3 | Homework 2, Problem 3 diagram |
| HW3 sleep duration | 15 seconds | Homework 2, Problem 3 text |

## Questions and notes requiring confirmation

Nothing blocks a task this workshop — every pin, value and timing is stated in
the material. The items below are judgement calls and practical cautions, not
missing facts.

| # | Task | Item |
| --- | --- | --- |
| 1 | `HW3` | The task says to use a pin-change interrupt to enter deep sleep but not **where** `esp_deep_sleep_start()` should be called. The sketch sets a flag in the handler and sleeps from `loop()`, keeping the handler minimal as `CLAUDE.md` requires. Calling it inside the handler would behave identically on video. See `HW3/README.md`, *Design choice*. |
| 2 | `HW1`, `HW3` | The instructor's Example 5 allocates a 1024-byte stack per task while both tasks call `Serial.print()`. That is tight. Kept as written; raise to 10000 (slide 23) if you see a stack-overflow reset. |
| 3 | `HW3` | `delay(100)` before sleeping is not from the material. It lets the serial buffer empty so the final message is not lost when the CPU powers down. |
| 4 | `P1` | Example 2 has no debounce, so a bouncy press can toggle LED2 twice. Instructor's behaviour, kept unchanged. |
| 5 | `HW2`, `HW3` | Deep sleep can drop the USB serial connection on some adapters; the Serial Monitor may need reopening after a wake. |
| 6 | all | Exercise 2 states no due date; Homework 2 states none either. |

## Material provenance

All three supplied PDFs converted cleanly to text (`markitdown`, fidelity
`CLEAN`); no OCR fallback was needed. See `../materials/INTAKE.md`.

As in Workshop 01, **every code listing and circuit diagram is an image**, so the
extracted text contained no code. The instructor's listings and circuits were
read by rendering pages directly:

- Lecture Note 4: slides 10, 16, 17, 25, 30, 35, 36, 50, 58
- Homework 2: page 1 (the Problem 3 schematic)

## Note on the Workshop 01 superseded file

`Workshop01/materials/_superseded/interrupt-and-timing-reconstruction.md` — the
placeholder retired during Workshop 01 — describes an interrupt plus `millis()`
exercise on GPIO 34 / 16 / 17. That matches **this** workshop's material
(Lecture Note 4, Example 2), not Lecture Note 3. Retiring it from Workshop 01
was correct; it was describing Workshop 02 content.

## Completion status

| ID | Sketch | Wiring | README | Questions | Compiles |
| --- | --- | --- | --- | --- | --- |
| `P1` | `P1.ino` | ✅ | ✅ | — | ✅ 18% flash |
| `HW1` | `HW1.ino` | ✅ | ✅ | — | ✅ 20% flash |
| `HW2` | `HW2.ino` | ✅ | ✅ | — | ✅ 21% flash |
| `HW3` | `HW3.ino` | ✅ | ✅ | — | ✅ 21% flash |

Compiled with `arduino-cli` against `esp32:esp32` core 2.0.17.
No sketch has been hardware-tested.

**Sketch convention.** A "do Example N" task is a verbatim transcription of the
instructor's listing — same lines, comments, spelling, and indentation, with no
header comment block. Task statement, circuit, board, baud, and caveats live in
each task's `README.md` and `wiring.md`. All sketches re-verified against the
slides and re-compiled on 2026-09-02.
