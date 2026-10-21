# Q3 — wiring

LED on GPIO22 as in Q1, plus a push switch from GPIO18 to GND. Source: Lecture
Note 8 slide 54 (schematic image). Pin numbers are from slide 9.

```
  Raspberry Pi
  ┌──────────────────┐
  │ GPIO22 (pin 15) ─┼────▶|──── 330 Ω ────┐
  │                  │   LED               │
  │                  │                     │
  │ GPIO18 (pin 12) ─┼──── SW ──┐          │
  │                  │   (push) │          │
  │ GND    (pin 14) ─┼──────────┴──────────┘
  └──────────────────┘
```

| Pi pin | Connects to |
| --- | --- |
| GPIO22, physical pin **15** | LED **long leg** (anode) |
| — | LED short leg → 330 Ω resistor → GND |
| GPIO18, physical pin **12** | one side of the push switch |
| GND, physical pin **14** (or any GND) | other side of the switch, and the 330 Ω resistor |

- **No resistor on the switch.** Slide 54: "no resistor is needed". The code
  uses `Button(18, pull_up=True)`, which turns on the Pi's **internal** pull-up
  (slide 52). GPIO18 reads HIGH when the switch is open and is pulled LOW when
  it is pressed. The internal pull-up is the source's own choice; it was not
  assumed here.
- Slide 54 calls this "the pull-up configuration". Slide 49's pull-up has an
  external 10–100 kΩ resistor; here it is internal to the Pi.
- On a 4-leg tactile switch, the two legs on the same side are usually *not*
  joined. Wire across the diagonal if unsure.
- gpiozero uses BCM numbering: `18` means GPIO18 = physical pin 12.
