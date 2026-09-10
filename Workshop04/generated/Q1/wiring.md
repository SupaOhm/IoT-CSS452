# Q1 — wiring

One ESP32 carrying **both** the potentiometer and the LED. Source: Lecture Note 6
slide 41 (schematic image) and slide 40.

Board: ThaiEasyElect's ESPino32. Serial baud 115200.

```
    3v3 ──────────┐
                  │
              ┌───┴───┐
              │  POT  │
   A0 ────────┤ wiper │      ESP32
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

Both circuits from `Exercise1` on a single board: the `PubNode` potentiometer and
the `SubNode` LED, unchanged. If you built `Exercise1` first, this is those two
breadboards merged.

The potentiometer's resistance is not stated on slide 41. `A0` is given only as
a pin label — wire to the pin your board prints `A0` on.
