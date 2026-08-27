# HW2 wiring — Homework 1 Problem 2 (Lecture Note 3, Example 8)

Source: `Lecture Note 3 - Introduction to ESP32.pdf`, slides 54–56.

## Diagram

```text
   +-------------------+
   |      ESP32        |
   |  (ESPino32 board) |        Micro USB
   |                   |=================== your computer
   +-------------------+                    (power + serial monitor)

   No external components.
   Time is fetched over WiFi from pool.ntp.org.
```

## Pin table

| ESP32 pin | Connects to | Notes |
| --- | --- | --- |
| — | — | This problem uses no GPIO pins |

## Connections required

| Item | Requirement | Source |
| --- | --- | --- |
| Micro USB | to the computer, for power and the serial monitor | slide 5 |
| WiFi access point | ESP32 must be able to reach the Internet | `CSS452 - Homework 1.pdf`, Problem 2 |
| NTP server | `pool.ntp.org` | slide 54 |

No breadboard wiring, resistors, or external parts are involved.
