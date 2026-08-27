# ESP32 Coursework

Drop each week's files into a week folder, then ask Claude Code to process it. The result is a separate Arduino sketch, wiring diagram, and explanation for each in-class problem and homework task.

## Weekly routine

1. Create a week folder:

   ```bash
   ./scripts/new-week.sh Week02
   ```

2. Put supplied files here (keep the categories):

   ```text
   Week02/materials/
   ├── 01_lecture-notes/
   ├── 02_example-code/
   ├── 03_in-class-exercises/
   └── 04_homework/
   ```

   PDFs, slides, images, `.ino`, `.cpp`, `.h`, `.txt`, and other instructor-provided files are fine. Do not rename the category folders.

3. From this repository, run:

   ```bash
   ./scripts/process-week.sh Week02
   ```

   The command starts Claude Code with a focused processing prompt. It reads the permanent rules in `CLAUDE.md` too. To work interactively instead, run `claude` and say `Process Week02 according to CLAUDE.md.`

4. Review `Week02/generated/INDEX.md`, especially every `NEEDS CLARIFICATION` item, before using a sketch.

## Results

```text
Week02/generated/
├── INDEX.md                 # task list, evidence, open questions
├── P1/                      # first in-class task
│   ├── solution.ino
│   ├── wiring.md
│   └── README.md
└── HW1/                     # first homework task
    ├── solution.ino
    ├── wiring.md
    └── README.md
```

`P` means in-class problem; `HW` means homework. The generator should create `QUESTIONS.md` in any task folder that cannot be completed from the supplied material. It must not guess pins or wiring.

## One-command behavior

`process-week.sh` validates the folder shape and launches the Claude Code CLI using the processing prompt. It intentionally does not parse PDFs or generate code itself: Claude Code can inspect the mixed source materials and follow the evidence rules in `CLAUDE.md`.

Use `--dry-run` to inspect the exact prompt without launching Claude Code:

```bash
./scripts/process-week.sh Week02 --dry-run
```

## Week 01 example

`Week01` demonstrates the expected output for the interrupt exercise discussed in the supplied conversation. Its material is labeled as a reconstruction; replace it with the original lecture PDF when you have it. The example preserves the stated GPIO 34 button, GPIO 16 LED1, GPIO 17 LED2, external 10 kΩ pull-up, and 2-second `millis()` pattern.

## Before uploading

Generated work is a starting point, not proof that it matches the instructor's intent or works on your exact board. Check the questions, inspect the wiring against your board, compile in Arduino IDE, and test safely with the hardware.
