# Q2 — Homework 4 Problem 2: two ESP32s controlling each other's LED

Status: READY FOR REVIEW

> **Video name:** `"Q2"` — this folder is named after the video you submit.
>
> **Group work:** "Work as a group of two students. We will use two ESP32."

## Files in this folder

| File | What it is |
| --- | --- |
| `Node1/Node1.ino` | sketch for the first board |
| `Node2/Node2.ino` | sketch for the second board |
| `wiring.md` | the circuit — **built identically on both boards** |
| `README.md` | this file |

## Task

From `CSS452 - Homework 4 - ESP32 MQTT Client.pdf`, Problem 2:

> Work as a group of two students. We will use two ESP32. Let us call them Node1
> and Node2.
>
> - Each ESP32 will work as both publisher node and subscriber node similar to
>   Section 4.
> - Each ESP32 will connect to a potentiometer and an LED similar to Section 4.
> - We rotate the knob of the potentiometer of Node1 will turn on/off the LED of
>   Node2 (the condition is similar to Section 4).
> - We rotate the knob of the potentiometer of Node2 will turn on/off the LED of
>   Node1 (the condition is similar to Section 4).
> - Hint: Revise the code "Public_HiveMQ_PubSub.ino" and upload to both ESP32.

Name it as Q2. Submit the video to the Google Classroom.

## The idea: two topics instead of one

`Q1` publishes and subscribes on **one** topic, so its own value comes straight
back to its own LED. Q2 needs the value to land on the *other* board, so one
topic is no longer enough — with a single shared topic both boards would receive
both values and each knob would light both LEDs.

So the one `Topic` constant becomes two, and the two boards swap them:

| | publishes to | listens on |
| --- | --- | --- |
| **Node1** | `IoT/PotenValue_Node1_<ID>` | `IoT/PotenValue_Node2_<ID>` |
| **Node2** | `IoT/PotenValue_Node2_<ID>` | `IoT/PotenValue_Node1_<ID>` |

Each board still does exactly what Section 4 taught — publish every 2 seconds,
subscribe, compare against 500, drive GPIO 26. Only the address on the envelope
changed. Nothing new was introduced: no new library, no new call, no technique
absent from the lecture.

The hint says to "revise the code and upload to both ESP32". Both sketches here
*are* that one revised code; they differ only in which topic name goes in which
constant, and in the client ID. `Node1.ino` and `Node2.ino` are otherwise
identical, line for line.

## Behavior

Turn Node1's knob past 500 → **Node2's** LED lights. Turn Node2's knob past 500
→ **Node1's** LED lights. Each board's own LED ignores its own potentiometer
entirely.

Both directions run at once and independently, each on its own 2-second
publish timer, so expect up to ~2 seconds of lag plus the round trip to HiveMQ.

## Before you upload — five lines per board

| Line | Node1 | Node2 |
| --- | --- | --- |
| 4 `ssid` | your SSID | your SSID |
| 5 `password` | your password | your password |
| 8 `ClientID` | `Client_Node1_<your ID>` | `Client_Node2_<your ID>` |
| 9 `TopicPub` | `IoT/PotenValue_Node1_<your ID>` | `IoT/PotenValue_Node2_<your ID>` |
| 10 `TopicSub` | `IoT/PotenValue_Node2_<your ID>` | `IoT/PotenValue_Node1_<your ID>` |

**Lines 9 and 10 are swapped between the boards. That crossover is the whole
assignment** — get it wrong and you have rebuilt Q1 twice.

Use the same student ID in all four topic strings, so `Node1`'s `TopicPub`
matches `Node2`'s `TopicSub` character for character. A single typo and that
direction goes silent while the other keeps working, which looks like a hardware
fault and is not one.

**Failure modes worth recognising:**

- **Both boards given the same `ClientID`** — MQTT allows one connection per
  client ID. The broker kicks one off, it reconnects, kicks the other off, and
  they fight forever. Serial loops through `Attempting MQTT connection...
  connected` and neither LED settles.
- **`TopicPub` and `TopicSub` set the same on both boards** — you get Q1's
  behaviour on two boards: each knob drives its own LED, and probably the other
  one too.
- **One topic string mistyped** — one direction works perfectly, the other never
  responds.
- **Another group picked your topic names** — the broker is public. Their knob
  moves your LED. Put your real student ID in all four strings.

## Source basis

Both sketches start from the instructor's supplied `Public_HiveMQ_PubSub.ino`,
which the homework's own hint names. Each differs from it in **four places**:

| Line | Supplied | Here (Node1) | Why |
| --- | --- | --- | --- |
| 8 | `ClientID = "Client_YourStudentID"` | `"Client_Node1_YourStudentID"` | two boards need different client IDs (slide 23) |
| 9–10 | `Topic = "IoT/PotenValue_YourStudentID"` | `TopicPub` + `TopicSub` | the crossover the task asks for |
| 51 | `ClientESP.publish(Topic, Val)` | `publish(TopicPub, Val)` | publish to its own topic |
| 64 | `ClientESP.subscribe(Topic)` | `subscribe(TopicSub)` | listen to the other board's |

Everything else — `setup()`, `ConnectMQTT()`, `callback()`, the 2-second timer,
the `> 500` test, every comment, the CRLF line endings — is the supplied file
untouched. `Node2.ino` is `Node1.ino` with `Node1` and `Node2` exchanged on
lines 8–10 and nothing else.

| Fact | Source |
| --- | --- |
| Each node is both publisher and subscriber | Homework 4 Problem 2 |
| Each node has a potentiometer and an LED | Homework 4 Problem 2 |
| Circuit "similar to Section 4" | Homework 4 Problem 2; slide 41 schematic |
| Threshold > 500 → LED on | "condition is similar to Section 4"; slide 40 |
| Start from `Public_HiveMQ_PubSub.ino` | Homework 4 Problem 2 hint |
| Client IDs must differ between two boards | slide 23 |
| Publish every 2 seconds | slide 40; `Node1.ino` line 47 |
| Broker `broker.hivemq.com`, port 1883 | slide 39; sketches lines 6–7 |
| `PubSubClient.h` must be installed | slide 15 |

## How to test

1. **Install `PubSubClient` on both machines** (slide 15).
2. Build the `wiring.md` circuit on **both** boards — potentiometer and LED on
   each. Check LED polarity: long leg to GPIO 26.
3. Edit lines 4, 5, 8, 9, 10 on each board per the table. Agree the student ID
   with your partner and type all four topic strings identically.
4. Upload `Node1.ino` to one board, `Node2.ino` to the other. Board:
   **ThaiEasyElect's ESPino32**.
5. Serial Monitor at **115200** on both. Each should print `Connecting`, an IP,
   then `Attempting MQTT connection...connected` **once**.
6. Each board prints `Pub: 1234` every 2 seconds with **its own** knob value,
   and `Sub : 5678` with **the other board's**. If a board's `Sub :` numbers
   track its own knob, the topics are not crossed over.
7. Turn Node1's knob past 500 → Node2's LED lights. Turn it back → dark. Repeat
   from Node2's knob onto Node1's LED. Film both directions; the sheet asks for
   both.

## Limitations

- Not hardware-tested. Both compile for `esp32:esp32:esp32` (56% program
  storage, 13% dynamic memory each). Compiling is not testing, and this task
  cannot be verified here at all — it needs two boards, two people, and a live
  public broker.
- **This task was written, not transcribed.** The instructor supplied no listing
  for it, only the hint to revise `Public_HiveMQ_PubSub.ino`. The two-topic
  split is the minimal change that satisfies the four bullets; another shape
  (retaining one topic and filtering on the payload, say) would also work.
  Read it before you submit it.
- The topic names `IoT/PotenValue_Node1_…` / `_Node2_…` are a choice, not a
  requirement. Slide 32 says "The publisher name, subscriber name, or Topic can
  be any name" — only uniqueness and matching across the pair matter.
- **The broker is public and unauthenticated.** Both potentiometer streams are
  readable by anyone, and anyone can drive your LEDs.
- HiveMQ's public broker occasionally goes down; slide 39 says switch to
  Mosquitto — change line 6 on **both** boards.
- `ConnectMQTT()` blocks with a 5-second retry while the broker is unreachable,
  so a board stuck there stops publishing and the other board's LED freezes.
- `setCallback(callback)` is called twice, as in every sketch in this workshop.
  It is the instructor's code and was left alone.
