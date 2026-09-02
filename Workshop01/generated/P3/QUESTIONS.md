# P3 — open questions

Two facts needed for this task are not present in the supplied material.
Confirm both before submitting.

## 1. The touch threshold is not specified

**Affected line:** `P3.ino`, `const int touchThreshold = 20;` and the
`if (touchValue < touchThreshold)` test in `loop()`.

The task requires the ESP32 to restart "if you touch the wire", which needs a
numeric threshold separating touched from not-touched. Lecture Note 3 never
states one:

- Slide 38 says only that `touchRead()` returns 0–1023, that not touching
  returns "a high value", and that touching returns "a low value".
- Slide 40 shows a serial-monitor screenshot with values of roughly **38, 20,
  9, 8, 8, 7, 7, 6, 39, 41, 44, 46, 46**, annotated "the values given from the
  touch sensor when we touch the wire" against the low run.

`20` was chosen to sit between the two observed bands, but **it is not from the
course material** and the reading `20` itself appears in the screenshot, close
to the boundary. Capacitive readings also vary with board, wire length, and
humidity.

**Question for the instructor:** what touch threshold should we use, or should
we calibrate per board by observing `touchRead()` first?

**Interim workaround:** upload the sketch, watch the printed values while
touching and releasing the wire, and set `touchThreshold` midway between your
own two bands.

## 2. The homework's cross-reference to "Example 5" does not match the lecture

**Affected requirement:** Problem 3, restart behaviour.

`CSS452 - Homework 1.pdf` states:

> thereafter, if you touch the wire, ESP32 will restart (look at Example 4 and
> Example 5).

But in `Lecture Note 3 - Introduction to ESP32.pdf`:

- **Example 4** (slides 39–40) is the touch sensor — consistent with the task.
- **Example 5** (slide 42) is `Hall_Effect.ino`, the built-in Hall sensor. It
  has nothing to do with restarting.
- The restart command `ESP.restart()` appears in **section 3.6** (slide 43) in
  an example named `Soft_Reset.ino`, which is **not** given an "Example N"
  number.

`P3.ino` uses `ESP.restart()` from slide 43, since that is the only restart
mechanism the lecture teaches. No side is chosen on the numbering itself.

**Question for the instructor:** should "Example 5" in Homework 1 Problem 3 read
"the Soft Reset example in section 3.6"? Is any Hall-sensor behaviour intended
in this problem?
