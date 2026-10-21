# Exercise1 — connections

No GPIO wiring. This task connects the Pi to the laptop only. Source: Lecture
Note 8 slides 7, 16, 19.

```
                 Ethernet cable                    USB-C power
 ┌───────────┐   ┌──────────┐   ┌──────────────┐   ┌──────────────┐
 │    Mac    ├───┤ USB-C /  ├───┤ Raspberry Pi ├───┤ 5.1 V 3 A    │
 │  (Wi-Fi → │   │ Ethernet │   │  4 Model B   │   │ USB-C supply │
 │ internet) │   │ adapter  │   │ Ethernet port│   └──────────────┘
 └───────────┘   └──────────┘   └──────────────┘
      │
      └─ Internet Sharing: Wi-Fi → Ethernet adapter (slide 19)
```

| From | To | Note |
| --- | --- | --- |
| Mac USB-C / Thunderbolt port | USB-to-Ethernet adapter | only if the Mac has no Ethernet port (slide 16) |
| Adapter Ethernet port | Pi Ethernet port | any ordinary Ethernet cable |
| Pi USB-C power port | 5.1 V, 3 A USB-C supply | rating from slide 7 |

The supplementary article says a laptop USB port can also power the Pi. Slide
7's rating is 3 A, which many laptop ports do not supply. If the Pi reboots at
random or shows a lightning-bolt icon, use a proper supply.

Have the SD card inserted before power is applied (slide 16, step 1).
