# Exercise1 — Exercise 4: MQTT publisher and subscriber on two ESP32s

Status: READY FOR REVIEW

> **Video name:** `"Q1"` — the exercise sheet names this one, unlike Workshops
> 01–03 where only homework carried a video name. The folder is `Exercise1` by
> this repo's in-class convention; **the file you upload must be named `Q1`.**

> **Group work:** the sheet says "Work as a group of two students. We will use
> two ESP32." You need a partner and a second board.

## Files in this folder

| File | What it is |
| --- | --- |
| `PubNode/PubNode.ino` | sketch for the board with the **potentiometer** |
| `SubNode/SubNode.ino` | sketch for the board with the **LED** |
| `wiring.md` | both circuits, pin tables, component values |
| `README.md` | this file |

Two sketches, because the task uses two boards. Each sits in its own folder so
the Arduino IDE opens it alone.

## Task

From `CSS452 - Exercise 4.pdf`:

> Work as a group of two students. We will use two ESP32. Do the project in
> Section 3 in Lecture Note 6 as shown in Pages 16 – 35. Take a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - rotate the knob of the potentiometer (connected to the publisher node) to
>     turn on the LED (connected to the subscriber node),
>   - rotate the knob of the potentiometer (connected to the publisher node) to
>     turn off the LED (connected to the subscriber node).

Name it as Q1. Submit the video to the Google Classroom.

## Behavior

Nothing runs between the two boards. They meet at a public broker on the
internet.

**PubNode** joins Wi-Fi, connects to `broker.hivemq.com` on port 1883, then every
2 seconds reads `analogRead(A0)`, converts it to text with `dtostrf`, and
publishes it to the topic. It never subscribes and never calls
`ClientESP.loop()` — it only talks.

**SubNode** joins Wi-Fi, connects to the same broker, subscribes to the same
topic, and calls `ClientESP.loop()` every pass so incoming messages get
processed. When a message arrives, `callback()` reads the payload byte by byte
into `ValString`, converts it with `toInt()`, and:

```cpp
if (ValInt > 500) {
  digitalWrite(26, HIGH);   // Turn the LED on
} else {
  digitalWrite(26, LOW);    // Turn the LED off
}
```

So **500 is the threshold**, out of the 0–4095 range `analogRead` returns. Turn
the knob past roughly an eighth of its travel and the LED lights.

Because PubNode publishes on a 2-second timer, the LED can lag your hand by up
to 2 seconds. That is the design, not a fault — SubNode prints
`============== Wait 2 seconds ===================` after every message to say
so.

Slide 17: the two boards "do not need to connect to the same access point and
they can be at different locations." Different Wi-Fi networks is fine.

## Before you upload — four lines per board

Slide 23 says to revise the given code. Both sketches need lines 4–5; lines 8–9
need care.

| Line | PubNode | SubNode |
| --- | --- | --- |
| 4 `ssid` | your SSID | your SSID |
| 5 `password` | your password | your password |
| 8 `ClientID` | `Client_PubNode_<your ID>` | `Client_SubNode_<your ID>` |
| 9 `Topic` | `IoT/PotenValue_<your ID>` | **the same string as PubNode** |

Slide 23 states the two rules exactly:

> 3.1) *ClentID: PubNode and SubNode have different ClientIDs and different from
> other students.
> 3.2) *Topic: The topic must be the same topic name in both PubNode and SubNode.
> However, it must be a different name from other students.

**Get these wrong and the symptoms are confusing:**

- **Same `ClientID` on both boards** — MQTT allows one connection per client ID.
  The broker kicks the older one off, it reconnects, kicks the other off, and
  the two boards fight forever. The serial monitors loop through
  `Attempting MQTT connection...connected` over and over and the LED never
  settles.
- **Different `Topic` between the boards** — everything *looks* healthy. PubNode
  prints `Pub: 2314`, SubNode says `connected`, and the LED simply never moves,
  because SubNode is listening to a channel nobody publishes on.
- **A topic another student also picked** — `broker.hivemq.com` is public and
  unauthenticated. Anyone on it can publish to your topic, and your LED will
  react to their potentiometer. Put your real student ID in the topic.

## Source basis

Both sketches are the instructor's supplied files, **byte-identical except line
8**:

| Sketch | Supplied file | Difference |
| --- | --- | --- |
| `PubNode.ino` | `Public_HiveMQ_PubNode.ino` | line 8 only |
| `SubNode.ino` | `Public_HiveMQ_SubNode.ino` | line 8 only |

Both supplied files ship line 8 as `"Client_YourStudentID"` — the *same string*.
Slide 23 requires the two nodes to differ, so line 8 became
`"Client_PubNode_YourStudentID"` and `"Client_SubNode_YourStudentID"`, keeping
the instructor's own `YourStudentID` placeholder. Nothing else was touched:
same lines, comments, spacing, and CRLF line endings.

The third supplied file, `Public_HiveMQ_PubSub.ino`, belongs to **Section 4**
(one ESP32 doing both jobs, slides 36+), which this exercise does not cover. It
is left in `materials/`.

| Fact | Source |
| --- | --- |
| Two ESP32s, PubNode publishes / SubNode subscribes | slide 17 |
| Threshold 500 turns the LED on | slide 17; `SubNode.ino` line 79 |
| Broker `broker.hivemq.com`, port 1883 | slide 19; both sketches line 6–7 |
| Mosquitto as fallback if HiveMQ is down | slide 19 |
| Potentiometer 3v3 / wiper to A0 / GND | slide 20 schematic |
| LED on GPIO 26 through 330 Ω to GND | slide 20 schematic |
| ClientIDs must differ; topic must match | slide 23 |
| Publish interval 2000 ms | `PubNode.ino` line 41 |
| `PubSubClient.h` must be installed | slide 15 |
| Boards may be on different networks | slide 17 |

## How to test

1. **Install the library on both machines.** Arduino IDE → Tools → Manage
   Libraries → search `PubSubClient` → Install (slide 15). Without it neither
   sketch compiles.
2. Build both circuits from `wiring.md`. Check LED polarity: long leg to GPIO 26.
3. Edit lines 4–5, 8, 9 in each sketch per the table above. Agree the topic
   string with your partner and type it identically on both boards.
4. Tools → Board → **ThaiEasyElect's ESPino32**. Upload `PubNode.ino` to the
   potentiometer board and `SubNode.ino` to the LED board.
5. Open a Serial Monitor at **115200** on each. Both should print `Connecting`,
   an IP address, then `Attempting MQTT connection...connected` **once**.
   Repeated reconnects mean your ClientIDs collide.
6. PubNode prints `Pub: 1234` every 2 seconds. SubNode should print
   `Message arrived [...]` and `Sub : 1234` with the same number. If PubNode
   publishes and SubNode stays silent, your topics differ.
7. Turn the knob past 500: the LED lights within 2 seconds. Turn it back below
   500: it goes dark.

## Limitations

- Not hardware-tested. Both compile for `esp32:esp32:esp32` — PubNode 56%
  program storage / 13% dynamic memory, SubNode 55% / 13%. Compiling is not
  testing, and this task in particular cannot be verified without two boards and
  a live broker.
- **The broker is public and unauthenticated.** Your potentiometer readings are
  visible to anyone who subscribes to your topic, and anyone can publish to it.
  Do not put anything private in the payload.
- HiveMQ's public broker occasionally goes down. Slide 19 says to switch to
  Mosquitto if that happens — change line 6 on **both** boards.
- Credentials are hard-coded, as in the instructor's listing. They are on screen
  if you film the code with real values in place.
- `ConnectMQTT()` blocks in a `while` loop with a 5-second delay while the
  broker is unreachable. A board stuck there stops publishing entirely.
- `SubNode.ino` calls `ClientESP.setCallback(callback)` twice, once in `setup()`
  and again inside `ConnectMQTT()`. Harmless, and it is the instructor's code —
  left as supplied.
