# M5Dial_NTP

For Japanese documentation, see `README_JP.md`.

## Overview

`M5Dial_NTP` is a collection of Arduino sketches for M5Dial.
It includes examples such as watch, timer, and simple piano apps.

## Included Sketches

- `M5Dial/M5Dial_watch_mod/M5Dial_watch_mod.ino`
  - Analog watch that syncs RTC from NTP over Wi-Fi
- `M5Dial/watchESPI/watchESPI.ino`
  - Analog watch using RTC time (no NTP sync)
- `M5Dial/timer/timer.ino`
  - Touch + rotary timer app
- `M5Dial/pianoDial/pianoDial.ino`
  - Touch piano app with tones

## Requirements

- Arduino IDE 2.x (recommended)
- ESP32 board package (by Espressif Systems)
- M5Dial library/environment providing `M5Dial.h`
- `TFT_eSPI` (used by `watchESPI` and `M5Dial_watch_mod`)
- `Tone32` (used by `pianoDial`)
  - Included in this repo at `M5Dial/pianoDial/Tone32-master`

## How to Use

1. Open the target `.ino` sketch in Arduino IDE
2. Select an M5Dial / ESP32S3 board profile
3. Install required libraries
4. Connect M5Dial and upload

## NTP Settings (`M5Dial_watch_mod`)

- `ssid`
- `password`
- `ntpServer`

## Notes

- Font headers (`Noto.h`, etc.) are required by watch sketches.
