# Wiring — P1

## Pin table

| Part | ESP32 connection | Other connection |
| --- | --- | --- |
| Button signal | GPIO 34 | Button to GND when pressed |
| Button pull-up | GPIO 34 | 10 kΩ to 3.3 V |
| LED1 | GPIO 16 | LED/resistor return to GND (resistor value not stated) |
| LED2 | GPIO 17 | LED/resistor return to GND (resistor value not stated) |

## Simple wiring diagram

```text
                    3.3 V
                      |
                    [10 kΩ]
                      |
ESP32 GPIO 34 --------+-------- push button -------- GND

ESP32 GPIO 16 ----------------- LED1 -- [resistor: value not stated] -- GND
ESP32 GPIO 17 ----------------- LED2 -- [resistor: value not stated] -- GND
```

The LED resistor values were not stated in the preserved source, so no value is assumed.
