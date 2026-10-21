# Q1 — wiring

One LED on GPIO22 through a 330 Ω resistor to GND. Source: Lecture Note 8
slide 41 (schematic image). Pin numbers are from slide 9.

```
  Raspberry Pi
  ┌──────────────────┐
  │ GPIO22 (pin 15) ─┼────▶|──── 330 Ω ────┐
  │                  │   LED               │
  │ GND    (pin 14) ─┼─────────────────────┘
  └──────────────────┘
```

| Pi pin | Connects to |
| --- | --- |
| GPIO22, physical pin **15** | LED **long leg** (anode) |
| — | LED short leg (cathode) → 330 Ω resistor |
| GND, physical pin **14** (or any GND: 6, 9, 20, 25, 30, 34, 39) | other end of the 330 Ω resistor |

- The code says `22`: gpiozero uses **BCM/GPIO numbering**, not physical pin
  numbers (slides 9–10). Physical pin 22 is GPIO25, so do not wire to it.
- The schematic puts the resistor on the cathode side. Either side works
  electrically; this follows the slide.
- GPIO is 3.3 V. Never feed 5 V into a GPIO pin (slide 10).

Q2 and Q4 use this same circuit unchanged, so build it once.
