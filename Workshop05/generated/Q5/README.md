# Q5 — Homework 5 Problem 5: random integers to ThingSpeak

Status: READY FOR REVIEW

> **Video name:** `"Q5"`. This folder is named after the video you submit.

## Files in this folder

| File | What it is |
| --- | --- |
| `Q5.py` | the program: open it in Thonny on the Pi |
| `wiring.md` | no circuit; network requirement only |
| `README.md` | this file |

No companion files. The ThingSpeak channel is set up in the browser (below), not
in a file.

## Task

From `CSS452 - Homework 5 - Intro to Raspberry Pi.pdf`, Problem 5:

> Do the Example 8 in Lecture Note 8. Record a video to show
> - Python code,
> - The graph (showing random numbers) in ThingSpeak
>
> Set the video name "Q5" and submit it to the Google Classroom.

## Behavior

Every 60 s (`PERIOD`), the program picks `randint(0, 100)`, prints
`Number: NN`, and POSTs `{'api_key': KEY, 'field1': NN}` as JSON to
`https://api.thingspeak.com/update.json`. The channel's Field 1 chart adds one
point per minute.

## Before you run — ThingSpeak channel (slide 73)

1. ThingSpeak → **Channels → New Channel**
   - Name: `Lect8 – Ex8`
   - Field 1: `Random Integer`
   - leave the rest blank → **Save Channel**
2. **API Keys** tab → copy the **Write API Key**.
3. Put it on line 6 in place of `Your Write API Key` (slide 74: "Note that put
   your own Write API Key"). Keep the quotes.

**Do not commit the real key.** `Q5.py` in this repo keeps the instructor's
placeholder. Paste your key into the copy on the Pi (or a local copy you don't
stage), and blur it if line 6 is in your video.

## Source basis

`Q5.py` is a **verbatim transcription** of the Example 8 listing on slide
74: same lines, order, spacing and spelling. Nothing was added or removed, and
no syntax fix was needed. It is `.py`, not `.ino`: Workshop05 moves from
ESP32/Arduino to Raspberry Pi/Python.

Slide 74 has a red annotation arrow drawn across lines 1–5. The page was
re-rendered at 250 dpi to confirm the characters under it: `from`, `PERIOD` and
`BASE_URL` are intact. Line 17 on the slide is empty; the file ends after
line 16.

| Fact | Source |
| --- | --- |
| No circuit; Pi must be on the internet | LN8 slides 73–74 |
| Channel `Lect8 – Ex8`, Field 1 `Random Integer` | LN8 slide 73 |
| Use your own Write API Key | LN8 slides 73–74 |
| Random integer 0–100, every 60 seconds | LN8 slide 74 |

## Getting the file onto the Pi

The slides have you type the program into Thonny on the Pi. Typing it is fine
and shows on video. You can also copy it from the Mac:

```sh
scp Q5/Q5.py pi@raspberrypi.local:~/
```

Then, in the Pi desktop over VNC: **Thonny → Load → `/home/pi/Q5.py` → Run**.

## How to test

1. On the Pi: `curl -s -o /dev/null -w "%{http_code}\n" https://api.thingspeak.com/`
   must print `200`. Don't test with `ping`: ThingSpeak never answers it.
2. Run `Q5.py`. The Shell prints `Number: …` once a minute.
3. In ThingSpeak, open the channel's **Private View**: a point appears per
   minute. Let it run **at least 5–7 minutes** before filming the graph; slide
   74's example chart spans 15:01–15:07.

## Limitations

- Not hardware-tested. Syntax-checked only; it was not run, to avoid posting to
  ThingSpeak with a placeholder key.
- **Failures are silent.** `response` is assigned and never checked, as in the
  listing. A wrong key or no internet gives no points on the chart and no
  error in Thonny. If the chart stays empty, check line 6 and connectivity
  first.
- Over the Ethernet cable the Pi's internet depends on macOS Internet Sharing
  being on (`../Exercise1/README.md` step 2). With Sharing off, the program
  dies on its first send with `Temporary failure in name resolution`.
- `requests` ships with Raspberry Pi OS. If you get
  `ModuleNotFoundError: requests`, run `sudo apt install python3-requests`.
