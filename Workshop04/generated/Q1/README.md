# Q1 — Homework 4 Problem 1: one ESP32 as both publisher and subscriber

Status: READY FOR REVIEW

> **Video name:** `"Q1"` — this folder is named after the video you submit.
>
> **Careful:** Exercise 4 task 1 is *also* named `Q1` by the instructor. Two
> different videos, one name. See open question 1 in `../INDEX.md` — ask him
> which to rename before uploading.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q1/Q1.ino` | the sketch — open this folder in the Arduino IDE |
| `wiring.md` | circuit, pin table, component values |
| `README.md` | this file |

No page files: MQTT has no web page. The payload is a bare number on a topic.

## Task

From `CSS452 - Homework 4 - ESP32 MQTT Client.pdf`, Problem 1:

> Do the project in Section 4 in Lecture Note 6 as shown in Pages 36 – 51. Take
> a video to show
>
> - circuit connection,
> - Arduino code,
> - demonstration:
>   - rotate the knob of the potentiometer to turn on the LED,
>   - rotate the knob of the potentiometer to turn off the LED,

Name it as Q1. Submit the video to the Google Classroom.

## Behavior

One board does both jobs. Slide 37 puts it plainly: the ESP32 works as publisher
and subscriber "to send the data to itself."

Every 2 seconds the sketch reads `analogRead(A0)`, converts it with `dtostrf`,
and publishes it to `Topic`. It is also subscribed to that same `Topic`, so the
broker sends the message straight back. `callback()` then reads the payload,
converts it with `toInt()`, and drives the LED:

```cpp
if (ValInt > 500) {
  digitalWrite(26, HIGH);   // Turn the LED on
} else {
  digitalWrite(26, LOW);    // Turn the LED off
}
```

**The value travels to the internet and back to light an LED wired two
centimetres away.** That is the point of the exercise, not an accident — it
proves the round trip works before Q2 splits the two halves across two boards.

`loop()` calls `ClientESP.loop()` every pass so arriving messages get processed,
then publishes on the 2-second timer. So expect up to ~2 seconds between turning
the knob and the LED reacting, plus whatever the round trip to HiveMQ costs.

## Before you upload — three lines

Slide 42 says to revise the given code:

| Line | Change to |
| --- | --- |
| 4 `ssid` | your SSID |
| 5 `password` | your password |
| 8 `ClientID` | `Client_<your student ID>` |
| 9 `Topic` | `IoT/PotenValue_<your student ID>` |

> 3) Add your student ID at the end of Client and Topic such that we have
> unique names.

Only one board here, so there is no PubNode/SubNode ID clash to worry about —
but the topic still has to be yours alone. `broker.hivemq.com` is public and
unauthenticated: if another student picked the same topic string, their
potentiometer will drive your LED and yours will drive theirs. Use your real
student ID.

## Source basis

`Q1.ino` is a **byte-identical copy** of the instructor's supplied
`Public_HiveMQ_PubSub.ino` — same lines, comments, spacing, and CRLF line
endings. Nothing was added, removed, or reworded, and no syntax fix was needed.

Unlike `Exercise1`, no line needed changing: that task had to split one shared
`ClientID` across two boards, while this one runs a single node.

| Fact | Source |
| --- | --- |
| One ESP32 as both publisher and subscriber | slide 37 |
| Potentiometer > 500 → LED on, else off | slide 40; `Q1.ino` line 89 |
| Publish every 2 seconds | slide 40; `Q1.ino` line 46 |
| Potentiometer 3v3 / wiper to A0 / GND | slide 41 schematic |
| LED on GPIO 26 through 330 Ω to GND | slide 41 schematic |
| Broker `broker.hivemq.com`, port 1883 | slide 39; `Q1.ino` lines 6–7 |
| Mosquitto as fallback if HiveMQ is down | slide 39 |
| Fill in SSID, password, student ID | slide 42 |
| `PubSubClient.h` must be installed | slide 15 |

## How to test

1. **Install the library:** Arduino IDE → Tools → Manage Libraries → search
   `PubSubClient` → Install (slide 15). Without it the sketch will not compile.
2. Build the circuit in `wiring.md`. Check LED polarity — long leg to GPIO 26.
3. Edit lines 4, 5, 8, 9 as above.
4. Tools → Board → **ThaiEasyElect's ESPino32**; select your port; Upload.
5. Serial Monitor at **115200**. Expect `Connecting`, an IP address, then
   `Attempting MQTT connection...connected` **once**.
6. Watch for paired lines every 2 seconds — `Pub: 1234`, then
   `Message arrived [...]` and `Sub : 1234` with the *same* number. Seeing
   `Pub:` with no `Sub:` means the subscribe failed or your topic is wrong.
7. Turn the knob past 500: the LED lights. Turn it back: it goes dark.

## Limitations

- Not hardware-tested. Compiles for `esp32:esp32:esp32` (56% program storage,
  13% dynamic memory). Compiling is not testing.
- **The broker is public and unauthenticated.** Anyone can read your topic and
  publish to it.
- HiveMQ's public broker occasionally goes down; slide 39 says switch to
  Mosquitto — change line 6.
- No internet, no LED. The value has to reach HiveMQ and come back, so this
  circuit does nothing offline even though both parts sit on one board.
- Credentials are hard-coded, as in the instructor's listing, and will be on
  screen if you film the code with real values in place.
- `ConnectMQTT()` blocks in a `while` loop with a 5-second retry while the
  broker is unreachable.
- `setCallback(callback)` is called twice, in `setup()` and again in
  `ConnectMQTT()`. Harmless, and it is the instructor's code — left as supplied.
