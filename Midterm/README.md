# Practical midterm kit

Open-book material for the CSS452 practical midterm (1 hour, 3 questions,
Lecture Notes 3–6). Built from the lecture notes, exercises and homework already
in this repo.

| File | Use |
| --- | --- |
| `CHEATSHEET.html` | **Open this in the exam.** Works offline, sidebar filter, a Copy button on every listing, prints cleanly |
| `CHEATSHEET.md` | The same content as Markdown — renders on GitHub |
| `sketches/` | 32 ready-to-open sketches, one per example. Open, change pins, upload |
| `cheatsheet.src.md`, `build.py` | Source and build script |

Rebuild after editing the source or a sketch:

```
uv run --with markdown python build.py
```

The listings in the cheatsheet are pulled from `sketches/` at build time, so the
two cannot disagree.

## What is in `sketches/`

| Prefix | Count | Origin |
| --- | --- | --- |
| `LN3_…` | 9 | Lecture Note 3 Examples 1–8 and the software-reset example |
| `LN4_…` | 10 | Lecture Note 4 Examples 1–10 |
| `LN5_…` | 3 | Lecture Note 5 Sections 3, 4, 5.2 (instructor's `.ino` files) |
| `LN6_…` | 3 | Lecture Note 6 Sections 3 and 4 (instructor's `.ino` files) |
| `HW…` | 5 | The written homework problems: HW1 P3, HW2 P3, HW3 P3, HW4 Q2 (two nodes) |
| `MIX_…` | 2 | Written for this kit: touch as a switch; LED buttons plus a sensor table on one web page |

Thirteen listings existed only as slide images and were transcribed for this
kit by rendering the slides: LN3 slides 31, 40, 42, 43, 48, 52 and LN4 slides
10, 25–26, 30–31, 46, 50, 54, 65. `LN4_Ex4_ShowCore` takes its first 12 lines
from slide 25, because slides 30–31 start at line 13.

These are exam templates, not the homework submissions: every sketch carries
`Your SSID` / `Your Password` / `YourStudentID` / `YourAPIkey` placeholders and
LF line endings. The byte-identical copies of the instructor's files stay in
`WorkshopNN/generated/`.

## Verification

- All 32 sketches **compile** with the ESP32 compiler against core 2.0.17.
- **None was linked, uploaded or hardware-tested here** — see the next section
  for why linking was not possible. Compiling is not testing.
- The two `MIX_` sketches and the four homework composites are written code,
  not transcriptions. Read them before relying on them.

## Check your toolchain before the exam

On the Mac this kit was built on (macOS 27.0.1, Apple Silicon), the Arduino
build currently **fails** with:

```
…/esptool_py/4.5.1/esptool: Bad CPU type in executable
…/builtin/tools/ctags/5.8-arduino11/ctags: bad CPU type in executable
```

Two tools the ESP32 core 2.0.17 build depends on are Intel-only programs, and
Rosetta — the macOS layer that runs Intel programs — is not installed. The
Arduino IDE uses the same `~/Library/Arduino15` tools, so **Verify and Upload in
the IDE will very likely fail the same way.** It worked on 11 September, before
the macOS update.

Check: open the IDE, open any sketch, press Verify.

If it fails, install Rosetta from Terminal and try again:

```
softwareupdate --install-rosetta --agree-to-license
```

Do not "fix" it by updating the ESP32 boards package to 3.x the night before:
3.x removes `ledcSetup`, `ledcAttachPin` and `hallRead`, which the lecture's
PWM and hall examples use.

## Not covered

- **Quizzes 3–6.** In the exam scope, never supplied to this repo.
- The exam guideline PDF sits in this folder but is git-ignored: it lists the
  whole class by name.
