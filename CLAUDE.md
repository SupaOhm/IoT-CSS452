# ESP32 Coursework Generator

This repository turns a week's supplied course material into separate, reviewable Arduino/ESP32 solutions. It is coursework support: do not submit generated work without understanding and checking it.

## When asked to process a week

1. Read `WeekXX/materials/` recursively before writing output. Treat these folders in this priority order:
   1. `01_lecture-notes/` — required concepts, terminology, hardware, constraints.
   2. `02_example-code/` — required code structure, APIs, naming, and instructor style.
   3. `03_in-class-exercises/` and `04_homework/` — the problem statements to solve.
2. Create or update `WeekXX/generated/INDEX.md` first. List every discovered task, its source file/page (where available), chosen output ID, source facts used, and unresolved items.
3. Produce one directory per task: `P1`, `P2`, … for in-class tasks and `HW1`, `HW2`, … for homework tasks. Use the order in the supplied material. Do not renumber an existing task unless correcting an explicit mistake.
4. Each task directory must contain:
   - `solution.ino` — an Arduino sketch that follows the supplied examples' style.
   - `wiring.md` — a small text/ASCII wiring diagram, pin table, component values, and power/ground connections.
   - `README.md` — task summary, behavior, source basis, how to test, and limitations.
   - `QUESTIONS.md` only when information is missing, conflicting, unreadable, or ambiguous.
5. Finish by updating `generated/INDEX.md` with a concise completion status for every task.

## Evidence-first rules

- The materials are the source of truth. Preserve their terminology, pin numbers, circuit topology, resistor values, timing, board assumptions, and code conventions.
- Never silently invent a GPIO pin, component value, wiring connection, library, board, timing, behavior, or requirement.
- If a needed detail is absent or ambiguous, do **not** make the sketch appear final. Create `QUESTIONS.md`, state the exact missing fact and the affected line/connection, and mark the task `NEEDS CLARIFICATION` in `INDEX.md`.
- You may use a harmless placeholder such as `// TODO: confirm LED GPIO from assignment` only when that makes the incomplete code obvious; never present a guessed hardware mapping as fact.
- If sources conflict, quote the conflict in `QUESTIONS.md`, link to both source locations, and do not choose a side.
- Do not introduce techniques beyond those evidenced by the lecture/examples unless the task explicitly requires them. Prefer the examples' names, structure, comments, and libraries.
- If a PDF/image cannot be read reliably, say so in `INDEX.md` and `QUESTIONS.md`; do not infer its contents from its filename.

## Arduino/ESP32 code rules

- Keep every `solution.ino` self-contained and compile-oriented: includes, constants, state, `setup()`, and `loop()` as needed.
- Retain pin and behavior assumptions in comments next to the relevant code.
- For interrupt code, keep interrupt handlers minimal and match the taught approach. Flag electrical/debounce concerns only when relevant to the supplied circuit.
- Do not claim a sketch has been physically tested. Say `Not hardware-tested` unless a test result is provided.

## Wiring-diagram rules

- Use plain text/ASCII only—easy to review, version, and print.
- Label ESP32 GPIO, 3.3 V/5 V as specified, GND, each component, and resistor value if supplied.
- Show external pull-up/pull-down parts; do not assume an internal pull resistor unless the source explicitly uses one.

## Output format

Use this task heading in `README.md`:

`Status: READY FOR REVIEW` or `Status: NEEDS CLARIFICATION`

`INDEX.md` must distinguish facts sourced from materials from questions requiring instructor/student confirmation.
