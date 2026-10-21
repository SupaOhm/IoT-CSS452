# Q5 — wiring

**No circuit.** Slide 73: "No circuit connection is required."

The only connection that matters is network: the Pi **must reach the internet**
(slide 74, in red). Over the Ethernet cable that means macOS Internet Sharing
is on; see `../Exercise1/README.md` step 2. Alternatively, put the Pi on Wi-Fi.

Check from the Pi before running:

```sh
curl -s -o /dev/null -w "%{http_code}\n" https://api.thingspeak.com/
```

`200` means the Pi reaches ThingSpeak. **Do not test with `ping`:**
ThingSpeak drops ping from everywhere (confirmed 2026-10-21 from a Mac with
working internet), so a failed ping proves nothing.
