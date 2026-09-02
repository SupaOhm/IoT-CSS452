# ESP32 Coursework

Drop each workshop's files into one folder and ask Claude Code to process it.
The result is a separate Arduino sketch, wiring diagram, and explanation for
each in-class problem and homework task.

## Weekly routine

1. Point the dropper at the workshop you are working on:

   ```bash
   ./scripts/set-workshop.sh Workshop02
   ```

   This creates the workshop folder if it does not exist yet.

2. Drop the supplied files into `dropper/`. **No sorting, no renaming.**

   ```bash
   open dropper/
   ```

   PDFs, slides, images, `.ino`, `.cpp`, `.h`, `.txt` — mixed together is fine.

3. In Claude Code, say:

   ```text
   do Workshop02
   ```

   Claude converts each file, sorts it into the right category, files it under
   `Workshop02/materials/`, then generates the solutions.

4. Review `Workshop02/generated/INDEX.md`, especially every
   `NEEDS CLARIFICATION` item, before using a sketch.

## Naming

Workshops are `Workshop01`, `Workshop02`, … in course order. **The workshop
number does not necessarily match the lecture number** — `Workshop01` uses
`Lecture Note 3`. Each `generated/INDEX.md` records the mapping for its
workshop.

## Results

```text
Workshop02/
├── materials/
│   ├── INTAKE.md              # what was filed where, and how well it converted
│   ├── 01_lecture-notes/
│   │   ├── Lecture Note 4.pdf # the original, always preserved
│   │   └── .converted/        # extracted text Claude reads
│   ├── 02_example-code/
│   ├── 03_in-class-exercises/
│   └── 04_homework/
└── generated/
    ├── INDEX.md               # task list, sourced facts, open questions
    ├── Exercise1/             # first in-class task
    │   ├── Exercise1/         # the sketch folder the Arduino IDE opens
    │   │   └── Exercise1.ino
    │   ├── wiring.md
    │   └── README.md
    └── P1/                    # Homework Problem 1 — submit its video as "P1"
        ├── P1/                # the sketch folder the Arduino IDE opens
        │   └── P1.ino
        ├── wiring.md
        └── README.md
```

Homework tasks are `P1`, `P2`, `P3` — the instructor's own video names, so the
folder you open is the video you submit. In-class tasks are `Exercise1`,
`Exercise2`, … numbered within that workshop's exercise sheet.

Each sketch sits in a subfolder of its task folder and is named after that
subfolder (`P1/P1/P1.ino`). The Arduino IDE will not open a sketch whose
filename differs from its folder, and the extra level keeps `README.md` and
`wiring.md` out of the sketch folder, so the IDE opens the sketch on its own.

A `QUESTIONS.md` appears in any task folder that could not be completed from the
supplied material. Pins and wiring are never guessed.

## Requirements

| Tool | Purpose | Install |
| --- | --- | --- |
| `markitdown` | converts PDF/PPTX/DOCX to markdown | `pipx install 'markitdown[all]'` |
| `pdftotext`, `pdftoppm` | fallback extraction and page rendering | `brew install poppler` |
| `tesseract` | OCR for scanned PDFs | `brew install tesseract` |
| `arduino-cli` | optional compile check | `brew install arduino-cli` |

## How intake decides

Each dropped file is converted, then graded:

| Grade | Meaning |
| --- | --- |
| `NATIVE` | already text (`.ino`, `.md`, `.txt`) — read directly |
| `CLEAN` | converted well by markitdown |
| `REDUCED` | fell back to `pdftotext`; layout and tables lost |
| `OCR` | scanned page recovered by tesseract |
| `FAILED` | unconvertible — parked in `dropper/_unsorted/` for you |

`REDUCED` and `OCR` facts are treated as unreliable: any GPIO number, resistor
value, or timing drawn from them is raised as a question rather than written
into a sketch as fact.

Note that a `CLEAN` grade only means the text layer extracted well. Slide decks
often hold their code listings and circuit diagrams as **images**, which text
extraction misses entirely; in that case Claude renders the pages and reads them
directly, citing slide numbers in `INDEX.md`.

Files are tracked by content hash, so re-dropping the same file does nothing,
and a different file with an existing name is saved alongside rather than
overwriting it.

## Before uploading

Generated work is a starting point, not proof that it matches the instructor's
intent or works on your exact board. Check the questions, inspect the wiring
against your board, compile in the Arduino IDE, and test safely with the
hardware.
