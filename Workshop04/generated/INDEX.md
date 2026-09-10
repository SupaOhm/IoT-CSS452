# Workshop04 — generated work

**Workshop 04 corresponds to Lecture Note 6** (`ESP32 – MQTT Clients`). As in
Workshops 01–03, the workshop number and the lecture number differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Video name | Status |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 4.pdf` | Lecture Note 6, Section 3 (slides 16–35) | `Q1` | READY FOR REVIEW |
| `Q1` | Homework | `CSS452 - Homework 4`, Problem 1 | Lecture Note 6, Section 4 (slides 36–51) | `Q1` | NOT STARTED |
| `Q2` | Homework | `CSS452 - Homework 4`, Problem 2 | Section 4 revised for two mutual nodes | `Q2` | NOT STARTED |

Only the in-class exercise was requested so far. The two homework problems are
recorded here because `INDEX.md` lists every discovered task; neither has been
generated.

### Naming — read this, it changed for Workshop04

Workshop04 is the first workshop where **the exercise sheet also names its
video**, and it picks a name that collides with the homework's:

- `CSS452 - Exercise 4.pdf` task 1 → "Name it as **Q1**"
- `CSS452 - Homework 4` problem 1 → "Name it as **Q1**"
- `CSS452 - Homework 4` problem 2 → "Name it as **Q2**"

Two different videos are both called `Q1`. That is the instructor's wording in
both sheets, quoted above — not a transcription slip. **Confirm with him which
to rename before submitting**, or the two uploads will be indistinguishable in
Google Classroom.

The in-class folder keeps this repo's standing convention (`Exercise1`,
numbered by task within the exercise sheet) and its `README.md` carries the
required video name at the top. Homework folders take the instructor's own
video names, which for this workshop are `Q1` and `Q2` rather than the `P1`–`P3`
of Workshops 01–03.

## Completion

| Task | Sketches | Lines | Compiles (`esp32:esp32:esp32`) | Flash | RAM |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | `PubNode/PubNode.ino` | 65 | yes | 56% | 13% |
| `Exercise1` | `SubNode/SubNode.ino` | 84 | yes | 55% | 13% |

Neither is hardware-tested. Compiling is not testing — and this task especially
cannot be verified here, since it needs two boards, two people, and a live
public broker.

### What the task folder holds

`Exercise1` is the first task in this repo that ships **two sketches**, because
it drives two boards:

```
Exercise1/
  PubNode/PubNode.ino    potentiometer board — publishes
  SubNode/SubNode.ino    LED board — subscribes
  wiring.md              both circuits
  README.md
```

Each sketch keeps its own folder so the Arduino IDE opens it alone, the same
reason every other task nests `<ID>/<ID>.ino`.

There are no companion page files this time. Workshop03's tasks served HTML;
MQTT has no web page at all — the payload is a bare number on a topic.

## Two sketches, one line changed in each

Both are the instructor's supplied files, byte-identical **except line 8**,
CRLF line endings included:

| Task file | Supplied file | Line 8 as supplied | Line 8 here |
| --- | --- | --- | --- |
| `PubNode/PubNode.ino` | `Public_HiveMQ_PubNode.ino` | `"Client_YourStudentID"` | `"Client_PubNode_YourStudentID"` |
| `SubNode/SubNode.ino` | `Public_HiveMQ_SubNode.ino` | `"Client_YourStudentID"` | `"Client_SubNode_YourStudentID"` |

The change is mandatory, not stylistic. Both supplied files carry the *same*
client ID, and slide 23 requires the two nodes to differ:

> 3.1) *ClentID: PubNode and SubNode have different ClientIDs and different from
> other students.

MQTT permits one live connection per client ID, so two boards sharing one would
disconnect each other in a loop. The instructor's own `YourStudentID`
placeholder is kept, so what must still be edited stays obvious.

`Public_HiveMQ_PubSub.ino`, the third supplied sketch, belongs to Section 4 and
is used by the homework, not by this exercise. It stays in `materials/`.

## Facts taken from the materials

| Fact | Value | Source |
| --- | --- | --- |
| Board | ThaiEasyElect's ESPino32 | Lecture Note 3, slide 18 (carried forward) |
| Serial baud | 115200 | both sketches, line 16 |
| Required library | `PubSubClient.h`, via Library Manager | LN6 slide 15 |
| Broker | `broker.hivemq.com`, port 1883 | LN6 slide 19; sketches lines 6–7 |
| Fallback broker | Mosquitto, if HiveMQ has problems | LN6 slide 19 |
| Roles | PubNode = potentiometer + publisher; SubNode = LED + subscriber | LN6 slide 17 |
| LED threshold | `ValInt > 500` → LED on, else off | LN6 slide 17; `SubNode.ino` line 79 |
| Publish interval | every 2000 ms | `PubNode.ino` line 41 |
| PubNode circuit | 3v3 — potentiometer — GND, wiper to `A0` | LN6 slide 20 (schematic image) |
| SubNode circuit | GPIO 26 → LED long leg, short leg → 330 Ω → GND | LN6 slide 20 (schematic image) |
| Networks | the two boards may be on different access points and in different places | LN6 slide 17 |
| ClientID / Topic rules | IDs differ per node; topic identical across nodes, unique per student | LN6 slide 23 |

## Conversion notes

- All three PDFs converted `CLEAN`, and unlike Lecture Note 5 the prose of
  Lecture Note 6 carries the facts in its text layer — slides 17, 19, 23 and 32
  were read directly.
- **Slide 20's schematic is an image.** The extracted text flattens it to
  `ESP32 Pin 3v3 of ESP32 (PubNode) … 26 Potentiometer LED A0 330`. Page 20 was
  rendered (`pdftoppm -f 20 -l 20 -r 150 -png`) and read to confirm the
  potentiometer's wiper goes to `A0`, and that GPIO 26 drives the LED's long leg
  with the 330 Ω resistor on the cathode side to GND.
- Slides 24–31 are annotated screenshots of the two listings. They were not
  transcribed: the instructor supplied both `.ino` files directly, so the files
  are the source of truth for the code.
- The three `.ino` files were taken in as `NATIVE` — read directly, no
  conversion.

## Open questions and notes

Nothing blocks `Exercise1`; it is READY FOR REVIEW.

| # | Item | Detail |
| --- | --- | --- |
| 1 | **Two different videos are both named `Q1`** | Exercise 4 task 1 and Homework 4 problem 1 both say "Name it as Q1". Quoted from both sheets. Ask the instructor which to rename. |
| 2 | **Student ID must be filled in on four lines** | Lines 8 and 9 of both sketches still carry `YourStudentID`. Slide 23 requires the topic to be unique per student; `broker.hivemq.com` is public and unauthenticated, so a topic another student picked means their potentiometer moves your LED. |
| 3 | Nothing states which board is "yours" in a pair | The sheet says work in a group of two with two ESP32s. Which partner supplies which board, and whether both students submit the same video, is not specified. |
| 4 | The potentiometer's resistance is not stated | Slide 20 labels the part only "Potentiometer", as in Workshop03. Any common linear pot divides 3.3 V the same way. |
| 5 | `A0` is never given as a GPIO number | Same as Workshop03: the schematic labels the pin `A0` and the code says `analogRead(A0)`. Wire to the pin your board labels `A0`. No GPIO number was invented. |
| 6 | `setCallback` is called twice in `SubNode.ino` | Once in `setup()` (line 32) and again in `ConnectMQTT()` (line 52). Harmless; it is the instructor's code and was left as supplied. |
