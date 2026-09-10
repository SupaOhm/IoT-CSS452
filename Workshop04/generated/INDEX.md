# Workshop04 — generated work

**Workshop 04 corresponds to Lecture Note 6** (`ESP32 – MQTT Clients`). As in
Workshops 01–03, the workshop number and the lecture number differ.

Course: CSS452 Internet of Things · Dr. Seksan Laitrakun · School of ICT, SIIT,
Thammasat University.

## Tasks

| ID | Type | Source | Based on | Video name | Status |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | In-class | `CSS452 - Exercise 4.pdf` | Lecture Note 6, Section 3 (slides 16–35) | `Q1` | READY FOR REVIEW |
| `Q1` | Homework | `CSS452 - Homework 4`, Problem 1 | Lecture Note 6, Section 4 (slides 36–51) | `Q1` | READY FOR REVIEW |
| `Q2` | Homework | `CSS452 - Homework 4`, Problem 2 | Section 4 revised for two mutual nodes | `Q2` | READY FOR REVIEW |

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

| Task | Sketch | Lines | Compiles (`esp32:esp32:esp32`) | Flash | RAM |
| --- | --- | --- | --- | --- | --- |
| `Exercise1` | `PubNode/PubNode.ino` | 65 | yes | 56% | 13% |
| `Exercise1` | `SubNode/SubNode.ino` | 84 | yes | 55% | 13% |
| `Q1` | `Q1/Q1.ino` | 94 | yes | 56% | 13% |
| `Q2` | `Node1/Node1.ino` | 95 | yes | 56% | 13% |
| `Q2` | `Node2/Node2.ino` | 95 | yes | 56% | 13% |

None is hardware-tested. Compiling is not testing — and `Exercise1` and `Q2`
especially cannot be verified here, since each needs two boards, two people, and
a live public broker.

### What the task folders hold

Workshop04 is the first workshop whose tasks ship **more than one sketch**,
because two of the three drive two boards each:

```
Exercise1/  PubNode/PubNode.ino   potentiometer board — publishes
            SubNode/SubNode.ino   LED board — subscribes
Q1/         Q1/Q1.ino             one board doing both jobs
Q2/         Node1/Node1.ino       pot + LED, crossed over with Node2
            Node2/Node2.ino       pot + LED, crossed over with Node1
```

Every sketch keeps its own folder so the Arduino IDE opens it alone — the same
reason every other task in this repo nests `<ID>/<ID>.ino`.

There are no companion page files this workshop. Workshop03's tasks served HTML;
MQTT has no web page at all — the payload is a bare number on a topic.

## How each sketch relates to the supplied code

All three supplied `.ino` files are used, one per task. Two tasks are near-verbatim; one is written.

| Task file | Supplied file | Differs in | Why |
| --- | --- | --- | --- |
| `Exercise1/PubNode/PubNode.ino` | `Public_HiveMQ_PubNode.ino` | line 8 | client IDs must differ |
| `Exercise1/SubNode/SubNode.ino` | `Public_HiveMQ_SubNode.ino` | line 8 | client IDs must differ |
| `Q1/Q1/Q1.ino` | `Public_HiveMQ_PubSub.ino` | **nothing — byte-identical** | single node, no clash to fix |
| `Q2/Node1/Node1.ino` | `Public_HiveMQ_PubSub.ino` | lines 8, 9–10, 51, 64 | written task; topic crossover |
| `Q2/Node2/Node2.ino` | `Public_HiveMQ_PubSub.ino` | lines 8, 9–10, 51, 64 | same, with the topics swapped |

CRLF line endings are preserved throughout.

### `Exercise1` — one mandatory line

Both supplied node files carry the *same* client ID, and slide 23 requires the
two to differ:

> 3.1) *ClentID: PubNode and SubNode have different ClientIDs and different from
> other students.

MQTT permits one live connection per client ID, so two boards sharing one would
disconnect each other in a loop. Line 8 became `"Client_PubNode_YourStudentID"`
and `"Client_SubNode_YourStudentID"`, keeping the instructor's own
`YourStudentID` placeholder so the remaining edit stays obvious.

### `Q2` — the only written task in this workshop

The instructor supplied no listing for Problem 2, only the hint to revise
`Public_HiveMQ_PubSub.ino`. `Q1` publishes and subscribes on one topic, so its
value returns to its own LED; Problem 2 needs each knob to reach the *other*
board's LED. One shared topic cannot express that — both boards would receive
both values. So the single `Topic` constant became two:

| | publishes to | listens on |
| --- | --- | --- |
| `Node1` | `IoT/PotenValue_Node1_<ID>` | `IoT/PotenValue_Node2_<ID>` |
| `Node2` | `IoT/PotenValue_Node2_<ID>` | `IoT/PotenValue_Node1_<ID>` |

`publish(Topic, …)` became `publish(TopicPub, …)` and `subscribe(Topic)` became
`subscribe(TopicSub)`. Nothing else changed — no new library, no new call, no
technique absent from the lecture. `Node2.ino` is `Node1.ino` with `Node1` and
`Node2` exchanged on lines 8–10 and nothing else.

The topic *names* are a choice, not a requirement: slide 32 says "The publisher
name, subscriber name, or Topic can be any name". Only uniqueness per student
and an exact match across the pair matter.

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
| Section 4 role | one ESP32 as publisher *and* subscriber, "to send the data to itself" | LN6 slide 37 |
| Section 4 circuit | potentiometer **and** LED on one board, same pins as Section 3 | LN6 slide 41 (schematic image) |
| Section 4 threshold and interval | > 500 → LED on; publish every 2 seconds | LN6 slide 40 |
| Topic names are free-form | "The publisher name, subscriber name, or Topic can be any name" | LN6 slide 32 |
| `Q2` starting point | revise `Public_HiveMQ_PubSub.ino`, upload to both boards | Homework 4 Problem 2 hint |

## Conversion notes

- All three PDFs converted `CLEAN`, and unlike Lecture Note 5 the prose of
  Lecture Note 6 carries the facts in its text layer — slides 17, 19, 23 and 32
  were read directly.
- **Slide 20's schematic is an image.** The extracted text flattens it to
  `ESP32 Pin 3v3 of ESP32 (PubNode) … 26 Potentiometer LED A0 330`. Page 20 was
  rendered (`pdftoppm -f 20 -l 20 -r 150 -png`) and read to confirm the
  potentiometer's wiper goes to `A0`, and that GPIO 26 drives the LED's long leg
  with the 330 Ω resistor on the cathode side to GND.
- **Slide 41's schematic is also an image**, flattened by extraction to
  `Pin 3v3 of ESP32 ESP32 26 Potentiometer A0 LED 330 Pin GND of ESP32`. It is
  the Section 3 pair merged onto one board — same pins, same 330 Ω — and the
  prose on slide 40 states the threshold and interval independently, so `Q1`'s
  wiring rests on both.
- Slides 24–31 are annotated screenshots of the two listings. They were not
  transcribed: the instructor supplied both `.ino` files directly, so the files
  are the source of truth for the code.
- The three `.ino` files were taken in as `NATIVE` — read directly, no
  conversion.

## Open questions and notes

Nothing blocks any task; all three are READY FOR REVIEW.

| # | Item | Detail |
| --- | --- | --- |
| 1 | **Two different videos are both named `Q1`** | Exercise 4 task 1 and Homework 4 problem 1 both say "Name it as Q1". Quoted from both sheets. Ask the instructor which to rename. |
| 2 | **Student ID must be filled in on four lines** | Lines 8 and 9 of both sketches still carry `YourStudentID`. Slide 23 requires the topic to be unique per student; `broker.hivemq.com` is public and unauthenticated, so a topic another student picked means their potentiometer moves your LED. |
| 3 | Nothing states which board is "yours" in a pair | The sheet says work in a group of two with two ESP32s. Which partner supplies which board, and whether both students submit the same video, is not specified. |
| 4 | The potentiometer's resistance is not stated | Slide 20 labels the part only "Potentiometer", as in Workshop03. Any common linear pot divides 3.3 V the same way. |
| 5 | `A0` is never given as a GPIO number | Same as Workshop03: the schematic labels the pin `A0` and the code says `analogRead(A0)`. Wire to the pin your board labels `A0`. No GPIO number was invented. |
| 6 | `setCallback` is called twice | Once in `setup()` and again in `ConnectMQTT()`, in every sketch this workshop supplies. Harmless; it is the instructor's code and was left as supplied. |
| 7 | **`Q2` is written, not transcribed** | No listing exists for Homework 4 Problem 2 — only the hint to revise `Public_HiveMQ_PubSub.ino`. The two-topic crossover is the minimal change satisfying the four bullets, but another shape (one topic, filtering on the payload) would also work. Read it before submitting. |
| 8 | `Q2`'s topic names are a choice | `IoT/PotenValue_Node1_…` / `_Node2_…` are not required by any source. Slide 32 allows any name; only uniqueness and an exact match across the pair matter. |
| 9 | Nothing states whether both partners submit the same video | `Exercise1` and `Q2` are both group tasks. Whether each student uploads their own copy is unspecified. |
