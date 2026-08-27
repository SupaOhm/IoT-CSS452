# P1 — interrupt plus timed LED

Status: READY FOR REVIEW

## Behavior

- LED1 on GPIO 16 changes state every 2 seconds using `millis()`.
- A press takes GPIO 34 from HIGH to LOW and triggers `toggle()` on `FALLING`.
- `toggle()` changes LED2 on GPIO 17.

## Source basis

This sketch follows `materials/03_in-class-exercises/interrupt-and-timing-reconstruction.md`, which preserves the pin mapping and code pattern from the prior conversation. It is not a replacement for the original lecture document.

## Check before using

- Confirm the original assignment did not require a specific LED resistor value or LED polarity.
- The sketch is not hardware-tested.
