# Workshop02 — generated work

**Workshop 02 corresponds to Lecture Note 4** (`ESP32 – Multitasking and Deep
Sleep`). As in Workshop 01, the workshop number and the lecture number differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Status |
| --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 2.pdf` | Lecture Note 4, Example 2 (slides 15–17) | READY FOR REVIEW |
| `P1` | Homework | `CSS452 - Homework 2.pdf`, Problem 1 | Lecture Note 4, Example 5 (slides 34–36) | READY FOR REVIEW |
| `P2` | Homework | `CSS452 - Homework 2.pdf`, Problem 2 | Lecture Note 4, Example 9 (slides 57–58) | READY FOR REVIEW |
| `P3` | Homework | `CSS452 - Homework 2.pdf`, Problem 3 | Example 5 revised, plus Examples 2 and 7 | READY FOR REVIEW |

### Naming

Homework folders carry the instructor's own video names: `P1`, `P2`, `P3` are
Homework 2 Problems 1, 2 and 3, so the folder you open is the video you submit.
In-class work is `Exercise1`, numbered by task within `CSS452 - Exercise 2.pdf`;
the exercise sheet's own number follows the lecture note, not the workshop.

## Circuits at a glance

Three of the four tasks share one breadboard; only `P2` differs.

| Task | Circuit |
| --- | --- |
| `Exercise1` | SW on GPIO 34 (10 kΩ), LED1 on GPIO 16 (330 Ω), LED2 on GPIO 17 (330 Ω) |
| `P1` | identical to `Exercise1` |
| `P2` | **different** — SW on GPIO 32 (10 kΩ) only, no LEDs |
| `P3` | `P1` plus SW1 on GPIO 26 (10 kΩ) |

Recording order that minimises rewiring: `Exercise1` → `P1` → `P3` → `P2`.

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
| `P3` extra switch | SW1 on GPIO 26, 10 kΩ pull-up to 3v3 | Homework 2, Problem 3 diagram |
| `P3` sleep duration | 15 seconds | Homework 2, Problem 3 text |

## Questions and notes requiring confirmation

Nothing blocks a task this workshop — every pin, value and timing is stated in
the material. The items below are judgement calls and practical cautions, not
missing facts.

| # | Task | Item |
| --- | --- | --- |
| 1 | `P3` | The task says to use a pin-change interrupt to enter deep sleep but not **where** `esp_deep_sleep_start()` should be called. The sketch sets a flag in the handler and sleeps from `loop()`, keeping the handler minimal as `CLAUDE.md` requires. Calling it inside the handler would behave identically on video. See `P3/README.md`, *Design choice*. |
| 2 | `P1`, `P3` | The instructor's Example 5 allocates a 1024-byte stack per task while both tasks call `Serial.print()`. That is tight. Kept as written; raise to 10000 (slide 23) if you see a stack-overflow reset. |
| 3 | `P3` | `delay(100)` before sleeping is not from the material. It lets the serial buffer empty so the final message is not lost when the CPU powers down. |
| 4 | `Exercise1` | Example 2 has no debounce, so a bouncy press can toggle LED2 twice. Instructor's behaviour, kept unchanged. |
| 5 | `P2`, `P3` | Deep sleep can drop the USB serial connection on some adapters; the Serial Monitor may need reopening after a wake. |
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
| `Exercise1` | `Exercise1/Exercise1.ino` | ✅ | ✅ | — | ✅ 18% flash |
| `P1` | `P1/P1.ino` | ✅ | ✅ | — | ✅ 20% flash |
| `P2` | `P2/P2.ino` | ✅ | ✅ | — | ✅ 21% flash |
| `P3` | `P3/P3.ino` | ✅ | ✅ | — | ✅ 21% flash |

Compiled with `arduino-cli` against `esp32:esp32` core 2.0.17.
No sketch has been hardware-tested.

**Sketch convention.** A "do Example N" task is a verbatim transcription of the
instructor's listing — same lines, comments, spelling, and indentation, with no
header comment block. Task statement, circuit, board, baud, and caveats live in
each task's `README.md` and `wiring.md`. All sketches re-verified against the
slides and re-compiled on 2026-09-02.
