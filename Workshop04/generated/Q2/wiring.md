# Q2 — wiring

**Two ESP32 boards, wired identically.** Each carries a potentiometer *and* an
LED. Source: the homework sheet ("Each ESP32 will connect to a potentiometer and
an LED similar to Section 4") and Lecture Note 6 slide 41.

Board: ThaiEasyElect's ESPino32. Serial baud 115200 on both.

Build the `Q1` circuit twice — once on Node1, once on Node2:

```
    3v3 ──────────┐
                  │
              ┌───┴───┐
              │  POT  │
   A0 ────────┤ wiper │      ESP32 (Node1, and again on Node2)
              │       │
              └───┬───┘
                  │
    GND ──────────┤
                  │
GPIO 26 ──┬──▶|───┴─ 330 Ω ──── GND
          │  LED
```

| ESP32 pin | Connects to |
| --- | --- |
| `3v3` | one outer leg of the potentiometer |
| `A0` | the potentiometer's **wiper** (centre leg) |
| `GND` | the other outer leg |
| `26` | LED **long leg** (anode) |
| — | LED short leg (cathode) → 330 Ω resistor |
| `GND` | other end of the 330 Ω resistor |

The homework gives no schematic of its own; it says the circuit is "similar to
Section 4", so slide 41's diagram is used unchanged on both boards. No pin was
invented and nothing was moved.

## No wire runs between the boards

The crossover is entirely in software — Node1 publishes to one topic and listens
on the other, Node2 does the reverse. Nothing physical connects them, and as in
Section 3 they need not share an access point.
