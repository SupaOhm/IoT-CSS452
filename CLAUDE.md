# ESP32 Coursework Generator

This repository turns a workshop's supplied course material into separate,
reviewable Arduino/ESP32 solutions. It is coursework support: do not submit
generated work without understanding and checking it.

Workshops are numbered `Workshop01`, `Workshop02`, … in the order the course
runs them. **Workshop numbering does not necessarily match the instructor's
lecture numbering** (for example `Workshop01` uses `Lecture Note 3`). Record the
mapping in `generated/INDEX.md`.

## The dropper

All supplied files arrive through a single folder, `dropper/`. The student does
not sort them.

- `dropper/.active-workshop` holds the target workshop, e.g. `Workshop01`. Set
  it with `./scripts/set-workshop.sh WorkshopXX`.
- `dropper/_unsorted/` holds files that could not be converted or classified.

## When asked to process a workshop ("do Workshop02")

1. **Intake.** Run `./scripts/intake.sh scan`. It converts each dropped file to
   markdown and proposes a category. Read each converted file and confirm or
   correct the proposal, then run `./scripts/intake.sh apply <decisions.tsv>`.
   Print the classification table so any misfile is visible.
2. Read `WorkshopXX/materials/` recursively before writing output. Treat these
   folders in this priority order:
   1. `01_lecture-notes/` — required concepts, terminology, hardware, constraints.
   2. `02_example-code/` — required code structure, APIs, naming, and instructor style.
   3. `03_in-class-exercises/` and `04_homework/` — the problem statements to solve.
3. Create or update `WorkshopXX/generated/INDEX.md` first. List every discovered
   task, its source file/page (where available), chosen output ID, source facts
   used, and unresolved items.
4. Produce one directory per task: `P1`, `P2`, … for in-class tasks and `HW1`,
   `HW2`, … for homework tasks. Use the order in the supplied material. Do not
   renumber an existing task unless correcting an explicit mistake.
5. Each task directory must contain:
   - `<ID>.ino` — an Arduino sketch named after its folder (`P1/P1.ino`,
     `HW1/HW1.ino`). The Arduino IDE requires the sketch filename to match its
     parent folder, so this name is mandatory.
   - `wiring.md` — a small text/ASCII wiring diagram, pin table, component
     values, and power/ground connections.
   - `README.md` — task summary, behavior, source basis, how to test, and limitations.
   - `QUESTIONS.md` only when information is missing, conflicting, unreadable, or ambiguous.
6. Finish by updating `generated/INDEX.md` with a concise completion status for
   every task.

## Conversion fidelity

Converted text is a reading aid; the **original file is the source of truth**.
Extracted text lives in a sibling `.converted/` folder and every file carries a
grade recorded in `materials/INTAKE.md`:

| Grade | Meaning | Constraint |
| --- | --- | --- |
| `NATIVE` | text file read directly | facts usable normally |
| `CLEAN` | markitdown structured output | facts usable normally |
| `REDUCED` | pdftotext fallback; layout and tables lost | pin tables, wiring figures, and column-aligned values must raise `QUESTIONS.md` |
| `OCR` | tesseract on a scanned page | GPIO numbers, resistor values, and timings must raise `QUESTIONS.md` |
| `FAILED` | unconvertible; left in `dropper/_unsorted/` | dependent tasks are `NEEDS CLARIFICATION` |

A `CLEAN` grade means the *text layer* extracted well. It does **not** mean the
document held no other content: slide decks routinely put code listings and
circuit diagrams in images, which text extraction silently misses. When a task
depends on a listing or diagram that is absent from the converted text, render
the relevant pages to images and read them, then cite the slide numbers in
`INDEX.md`. Do not reconstruct a listing from prose.

## Evidence-first rules

- The materials are the source of truth. Preserve their terminology, pin
  numbers, circuit topology, resistor values, timing, board assumptions, and
  code conventions.
- Never silently invent a GPIO pin, component value, wiring connection, library,
  board, timing, behavior, or requirement.
- If a needed detail is absent or ambiguous, do **not** make the sketch appear
  final. Create `QUESTIONS.md`, state the exact missing fact and the affected
  line/connection, and mark the task `NEEDS CLARIFICATION` in `INDEX.md`.
- You may use a harmless placeholder such as `// TODO: confirm LED GPIO from
  assignment` only when that makes the incomplete code obvious; never present a
  guessed hardware mapping as fact.
- If sources conflict, quote the conflict in `QUESTIONS.md`, link to both source
  locations, and do not choose a side.
- Do not introduce techniques beyond those evidenced by the lecture/examples
  unless the task explicitly requires them. Prefer the examples' names,
  structure, comments, and libraries.
- If a PDF/image cannot be read reliably, say so in `INDEX.md` and
  `QUESTIONS.md`; do not infer its contents from its filename.
- When a task says "do Example N", reproduce the instructor's listing rather
  than writing an independent solution.

## Arduino/ESP32 code rules

- Keep every sketch self-contained and compile-oriented: includes, constants,
  state, `setup()`, and `loop()` as needed.
- Retain pin and behavior assumptions in comments next to the relevant code.
- For interrupt code, keep interrupt handlers minimal and match the taught
  approach. Flag electrical/debounce concerns only when relevant to the supplied
  circuit.
- Compile-check with `arduino-cli compile --fqbn esp32:esp32:esp32 <dir>` when
  available, and report the result honestly.
- Do not claim a sketch has been physically tested. Say `Not hardware-tested`
  unless a test result is provided. Compiling is not testing.

## Wiring-diagram rules

- Use plain text/ASCII only—easy to review, version, and print.
- Label ESP32 GPIO, 3.3 V/5 V as specified, GND, each component, and resistor
  value if supplied.
- Show external pull-up/pull-down parts; do not assume an internal pull resistor
  unless the source explicitly uses one.

## Output format

Use this task heading in `README.md`:

`Status: READY FOR REVIEW` or `Status: NEEDS CLARIFICATION`

`INDEX.md` must distinguish facts sourced from materials from questions
requiring instructor/student confirmation.
