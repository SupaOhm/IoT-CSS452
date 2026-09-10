# Exercise1 — wiring

Two ESP32 boards, wired differently. Source: Lecture Note 6 slide 20 (schematic
image, rendered and read) and slide 17.

Board: ThaiEasyElect's ESPino32. Serial baud 115200 on both nodes.

## PubNode — potentiometer

Identical to the Workshop03 `P1` circuit.

```
    3v3 ──────────┐
                  │
              ┌───┴───┐
              │  POT  │
   A0 ────────┤ wiper │        ESP32 (PubNode)
              │       │
              └───┬───┘
                  │
    GND ──────────┘
```

| ESP32 pin | Connects to |
| --- | --- |
| `3v3` | one outer leg of the potentiometer |
| `A0` | the potentiometer's **wiper** (centre leg) |
| `GND` | the other outer leg |

The potentiometer's resistance is not stated on slide 20 — any common linear pot
divides 3.3 V the same way. `A0` is given only as the pin label; wire to the pin
your board prints `A0` on, exactly as in Workshop03 `P1`.

## SubNode — LED

```
   GPIO 26 ────┬──▶|──── 330 Ω ──── GND
               │  LED
        ESP32 (SubNode)
```

| ESP32 pin | Connects to |
| --- | --- |
| `26` | LED **long leg** (anode) |
| — | LED short leg (cathode) → 330 Ω resistor |
| `GND` | other end of the 330 Ω resistor |

Same LED-and-resistor arrangement as Workshop03 `Exercise1`, on a single pin.

## No wire runs between the boards

The two ESP32s are never physically connected. Everything travels
potentiometer → PubNode → HiveMQ broker (over the internet) → SubNode → LED.
Slide 17 says they "do not need to connect to the same access point and they can
be at different locations."
