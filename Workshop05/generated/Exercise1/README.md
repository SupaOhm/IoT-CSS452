# Exercise1 — Exercise 5 task 1: reach the Raspberry Pi desktop from your laptop

Status: READY FOR REVIEW

> **Video name:** not given. Exercise 5 says only "Submit the video to the
> Google Classroom". Homework 5 uses `Q1`–`Q5`, so nothing collides.

## Files in this folder

| File | What it is |
| --- | --- |
| `README.md` | this file: the macOS walkthrough |
| `wiring.md` | the cable, power and network connections |

**There is no code in this task.** It is a setup exercise: the deliverable is a
video of the Pi desktop and Thonny running on your laptop screen.

## Task

From `CSS452 - Exercise 5 - Intro to Raspberry Pi.pdf`:

> 1. Take a video to show that you can access Raspberry Pi via a notebook
>    computer successfully (Section 2 Raspberry Pi Setup):
>    - show Raspberry Pi desktop and Thonny Python program similar to the
>      figure below.
>
> Submit the video to the Google Classroom.

The figure is a screenshot of a `raspberrypi.local (raspberrypi) - VNC Viewer`
window. It shows the Pi desktop with **Menu → Programming → Thonny Python IDE**
open.

## Why this differs from the slides

Lecture Note 8 §2 (slides 14–27) is written for Windows: **PuTTY** for the
console and **RealVNC VNC Viewer** for the desktop. The sheet asks you to *show
access*, not to use those programs. On a Mac each one has a replacement:

| Slides use | On macOS | Licence | Pi needs changing? |
| --- | --- | --- | --- |
| PuTTY | `ssh` in Terminal (OpenSSH, ships with macOS) | open source (BSD) | no |
| VNC Viewer | **TigerVNC Viewer**, already in `/Applications` | open source (GPL) | **yes**: one-time change, step 6B |
| VNC Viewer | RealVNC Viewer, already in `/Applications` as *RealVNC Connect* | free, closed | no |
| VNC Viewer | macOS Screen Sharing (built in) | closed | yes, same change as TigerVNC |
| Windows ICS (slides 17–18) | macOS Internet Sharing (slide 19) | — | no |
| Bonjour for `raspberrypi.local` | built into macOS | — | no |

Name resolution is easier on a Mac than on Windows: `raspberrypi.local` works
with nothing extra installed.

### Why TigerVNC needs a server change

The course SD card runs **Raspbian 11 (bullseye)**: confirmed with
`cat /etc/os-release` on 2026-10-21. That is newer than the Python 3.7.3 /
Buster shown on slide 32, so the slides' screenshots predate the card. Its VNC
server is still **RealVNC Server** (the `V2` icon in the panel), which out of the box accepts only its own proprietary
authentication and encryption. Any other viewer, TigerVNC or Screen Sharing,
fails until the server is switched to the standard **VNC password**
authentication. RealVNC documents this
([help article](https://help.realvnc.com/hc/en-us/articles/10406396398877-How-do-I-connect-from-a-non-RealVNC-VNC-Viewer-to-RealVNC-Server-on-a-Raspberry-Pi)).
Step 6B does it from the SSH session in four commands.

**If you only want the shortest path,** use RealVNC Viewer (6A). It needs no
server change and matches the instructor's figure exactly. TigerVNC is the open
source route and costs about two extra minutes.

## Walkthrough (macOS 13 or later)

### 1. Power and cable (slides 16)

Plug the Ethernet cable from the Pi into your Mac. Most Macs have no Ethernet
port, so use a USB-C/Thunderbolt Ethernet adapter or a dock. Then power the Pi
over USB-C. See `wiring.md`.

### 2. Share your Wi-Fi to the Pi (slide 19, renamed for current macOS)

Slide 19 says *System Preferences → Sharing*. On macOS 13 and later that became:

**System Settings → General → Sharing → Internet Sharing → ⓘ**

- *Share your connection from:* **Wi-Fi**
- *To computers using:* your Ethernet adapter (e.g. "USB 10/100/1000 LAN",
  "Ethernet Adapter", or the dock's name)
- **Done**, then switch Internet Sharing **on**.

Pick the adapter the Pi is actually on. The list can hold near-identical names,
such as "USB 10/100 LAN" and "USB 10/100/1000 LAN". To see which one is in use,
run `networksetup -listallhardwareports` in Mac Terminal and match the device
(`en7` etc.). After switching Sharing on, reboot the Pi or replug its cable so
it picks up a `192.168.2.x` address. Until it does, SSH and VNC appear to hang.
Confirmed 2026-10-21: the Pi got `192.168.2.2`, and name lookup through
`192.168.2.1` worked.

Exercise 5 does not need internet on the Pi, since the link is a direct cable.
**Homework Q4 and Q5 do need it**: Q4 to install `guizero` (slide 60) and Q5
to reach ThingSpeak (slide 74). Setting it up now saves a second round.

If Internet Sharing will not turn on, or your Wi-Fi blocks it, slide 28's
alternative is to put the Pi on Wi-Fi instead, for example a phone hotspot.

### 3. Check the Pi is reachable

```sh
ping raspberrypi.local
```

Replies mean you're ready. Give a fresh boot about a minute. If nothing
answers, unplug and replug the cable, and check the adapter appears under
System Settings → Network.

### 4. Console: `ssh` replaces PuTTY (slides 20–21)

```sh
ssh pi@raspberrypi.local
```

The first time, type `yes` to accept the host key. Password: `raspberry`
(slide 21). Nothing appears on screen while you type it.

A recent Mac also prints `WARNING: connection is not using a post-quantum key
exchange algorithm`. That is harmless here: Bullseye's OpenSSH predates the
algorithm the Mac prefers, and the link is a cable to your own Pi.

- `Connection refused`: SSH is off. The SD card needs an empty file named
  `ssh` in its boot partition (slide 20, and the supplementary note: "Our
  technician did this").
- `REMOTE HOST IDENTIFICATION HAS CHANGED`: you are reaching a different Pi
  under the same name, for example after a board swap in class. Clear the old
  entry with `ssh-keygen -R raspberrypi.local` and connect again.

### 5. Enable VNC and desktop autologin (slides 21–25)

```sh
sudo raspi-config
```

- **Interface Options → VNC → Yes**
- **System Options → Boot / Auto Login → Desktop Autologin**
- Tab to **Finish**. The Pi reboots and the SSH session drops (slide 25).

### 6A. Desktop with RealVNC Viewer: no server change (slides 26–27)

Open **RealVNC Connect** (already installed), connect to `raspberrypi.local`,
click Continue, and log in as `pi` / `raspberry`.

### 6B. Desktop with TigerVNC: open source

After the reboot, SSH back in (step 4) and switch RealVNC Server to standard
VNC-password authentication:

```sh
sudo mkdir -p /root/.vnc/config.d
sudo sh -c 'printf "Authentication=VncAuth\nEncryption=PreferOn\n" >> /root/.vnc/config.d/vncserver-x11'
sudo vncpasswd -service
sudo systemctl restart vncserver-x11-serviced
```

- `vncpasswd -service` asks for a **new VNC password**. It is separate from
  `pi`'s login password, and VNC passwords are cut to **8 characters**. Slide 11
  says record every password you set; this is one more.
- If `vncpasswd -service` is rejected, newer RealVNC builds want
  `sudo vncpasswd -legacy -service`. That is the form in RealVNC's own article.
- If the viewer still refuses after the restart, change `PreferOn` to
  `PreferOff` in that file and restart again. TigerVNC cannot use RealVNC's
  encryption, so the two only meet without it.

Then open **TigerVNC Viewer**, enter `raspberrypi.local`, and give the VNC
password.

On first connect TigerVNC shows **"Server key fingerprint"** with an 8-byte
fingerprint. It is the VNC version of SSH's "authenticity of host" prompt:
click **Yes**. Over a direct cable the only machine that can answer is your Pi.

**Confirmed on the course card (2026-10-21):** TigerVNC reached the Pi desktop.
The window title reads `raspberrypi - TigerVNC`, not the figure's `VNC Viewer`.

Without RealVNC's encryption the session runs unencrypted. On a direct cable
between your Mac and your Pi that hardly matters. On a shared Wi-Fi or hotspot,
tunnel it through SSH instead, which needs no server change beyond 6B:

```sh
ssh -L 5901:localhost:5900 pi@raspberrypi.local
```

Leave that open and point TigerVNC at `localhost::5901` (two colons: TigerVNC
reads that as a port number).

**macOS Screen Sharing** works after the same 6B change: Finder → ⌘K →
`vnc://raspberrypi.local`, then the VNC password.

### 7. "Cannot currently show the desktop" (supplementary note)

A Pi with no HDMI monitor attached sometimes has no screen to share. Over SSH:
`sudo raspi-config` → **Display Options → Resolution**, pick anything except
*Default*, Finish, and reconnect. If it persists, try another resolution.

### 8. Record the video

1. With the Pi desktop on screen, open **Menu → Programming → Thonny Python IDE**,
   as in the figure.
2. Record it. ⌘⇧5 → *Record Entire Screen* captures the laptop screen. The
   sheet does not say whether a screen recording is enough or whether it wants
   to see the laptop and Pi physically; see open question 2 in `../INDEX.md`.
   Filming with a phone so the cable and the Mac are both in shot proves the
   point either way.

## Source basis

| Fact | Source |
| --- | --- |
| Use Putty + VNC Viewer over Ethernet | LN8 slide 14 |
| Direct cable Pi ↔ computer, adapter if no port | LN8 slide 16 |
| macOS: Sharing → Internet Sharing, Wi-Fi → wired LAN | LN8 slide 19 |
| Host `raspberrypi.local`, SSH, missing `ssh` file remark | LN8 slide 20 |
| `pi` / `raspberry`; `sudo raspi-config` | LN8 slides 12, 21 |
| Interface Options → VNC → Yes | LN8 slides 22–23 |
| System Options → Boot/Auto Login → Desktop Autologin | LN8 slide 24 |
| Finish reboots and ends the SSH session | LN8 slide 25 |
| VNC Viewer to `raspberrypi.local`, Continue, credentials | LN8 slide 26 |
| Wi-Fi access point as an alternative | LN8 slide 28 |
| Python 3.7.3 (→ Buster) | LN8 slide 32 |
| SD card already has the OS and the `ssh` file | supplementary, handwritten notes |
| "Cannot currently show the desktop" → change resolution | supplementary, last section |
| Non-RealVNC viewers need VNC-password auth on RealVNC Server | RealVNC help article (external) |

The TigerVNC, `ssh` and Screen Sharing steps are **not from the course
materials**. They are macOS replacements for the slides' Windows tools.

## How to test

1. `ping raspberrypi.local` answers.
2. `ssh pi@raspberrypi.local` reaches a `pi@raspberrypi:~ $` prompt.
3. A VNC viewer shows the Pi desktop, and Thonny opens from the Programming menu.

## Limitations

- **Partly confirmed on hardware (2026-10-21, student's Mac + course Pi):**
  `ssh pi@raspberrypi.local` logged in, `/etc/os-release` reads
  `Raspbian GNU/Linux 11 (bullseye)`, and TigerVNC reached the Pi desktop after
  the fingerprint prompt. Thonny has not yet been shown, and the video is not
  recorded.
- Whether step 6B was actually needed on this card is not yet recorded.
- A card running Bookworm or later uses `wayvnc` instead of RealVNC Server, and
  step 6B would not apply there.
- `pi` / `raspberry` is a well-known default. Fine on a direct cable; on any
  shared network, change it with `passwd` and record the new one (slide 11).
