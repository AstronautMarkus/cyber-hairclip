# Cyber Hairclip

[![CI](https://github.com/AstronautMarkus/cyber-hairclip/actions/workflows/ci.yml/badge.svg)](https://github.com/AstronautMarkus/cyber-hairclip/actions/workflows/ci.yml)

A tiny OLED you wear in your hair. An ESP8266 or ESP32 drives a 128x64 SSD1306 screen through 17 cyberpunk, hacker and Linux animations in random order, plus an optional Bad Apple!! player, until the battery runs out (or 24/7 on USB).

## Animations

| Effect | What you see |
|---|---|
| `eye` | Cybernetic eye that looks around, blinks, with a spinning iris ring |
| `matrix` | Digital rain with your `BANNER` hidden in it, revealed at the end |
| `tesseract` | A 4D hypercube rotating through the XW plane |
| `warp` | Hyperspace jump that accelerates and arrives at your `BANNER` |
| `radar` | Radar sweep with fading trail, blips and target lock |
| `banner` | Glitchy marquee over a modulated wave |
| `synthwave` | Striped sun and a perspective grid rolling towards you |
| `pulse` | Heart monitor: sweeping ECG trace and a beating heart |
| `spectrum` | LED spectrum analyzer with kick drum and falling peaks |
| `helix` | Rotating DNA double helix with a base-sequence ticker |
| `terminal` | `nmap` → `hydra` → root shell → `history -c` → HACK THE PLANET |
| `crack` | `hashcat` cracking a real SHA-256, one character at a time |
| `tor` | Onion routing: the packet sheds one layer at every hop |
| `htop` | `htop` with `john` pinning a core at 100% |
| `life` | Conway's Game of Life with gliders dropped in |
| `panic` | `dmesg` at full speed... until the kernel panics |
| `neural` | Fake neural implant: live spike raster and "decoded" thoughts |
| `badapple` | Bad Apple!! key frames, choppy on purpose ([optional](#bad-apple-optional)) |

It boots with a typed, fake brain-implant log. Every effect plays once before any repeats and never twice in a row.

## Hardware

- ESP8266 (e.g. Wemos D1 mini) or ESP32
- 0.96" SSD1306 128x64 I2C OLED
- A small LiPo **with a protection circuit**, plus a charger board

| OLED | ESP8266 (D1 mini) | ESP32 |
|---|---|---|
| VCC | 3V3 | 3V3 |
| GND | GND | GND |
| SDA | D2 (GPIO4) | GPIO21 |
| SCL | D1 (GPIO5) | GPIO22 |

## Build and flash

1. Add the board package to the Arduino IDE (*Settings → Additional boards manager URLs*):
   - ESP8266: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - ESP32: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
2. In the Library Manager install **Adafruit SSD1306** (it pulls in Adafruit GFX).
3. Open `cyber_hairclip/cyber_hairclip.ino`, pick your board and upload.

With `arduino-cli`:

```sh
arduino-cli compile --fqbn esp32:esp32:esp32 --upload -p /dev/ttyUSB0 cyber_hairclip
```

## Settings

Everything lives in [`cyber_hairclip/config.h`](cyber_hairclip/config.h):

| Setting | Default | Meaning |
|---|---|---|
| `FX_MS` | `8000` | How long each animation runs (ms) |
| `ROTATION` | `0` | `2` flips the screen 180° |
| `CONTRAST` | `0x50` | OLED brightness 0–255. Lower saves battery and burn-in |
| `OLED_ADDR` | `0x3C` | I2C address (some modules use `0x3D`) |
| `BADAPPLE_CHANCE` | `25` | % chance Bad Apple cuts in after each animation |
| `BANNER` | `AstronautMarkus.Dev` | Your signature, up to 20 characters |

## Bad Apple!! (optional)

The frames are **not** in this repo: the video belongs to its creators. If you have its frames as numbered PNGs:

```sh
pip install pillow
python3 tools/badapple.py path/to/frames --preview sheet.png
```

This keeps the 240 frames that change the most (`--keys`), to be played at 3 fps (`--fps`), and writes `cyber_hairclip/src/effects/badapple_frames.h` (gitignored, ~165 KB of flash). The next build picks it up automatically; without the file the effect is simply left out. Each turn resumes where the last one stopped, so the song plays in chapters. It fits an ESP32 or an ESP8266 with 4 MB of flash.

## Adding an animation

1. Create `cyber_hairclip/src/effects/myfx.cpp`:

   ```cpp
   #include "effects.h"

   void fxMyFx(uint32_t t) {  // t = ms since this turn started (0..FX_MS)
     display.drawCircle(W / 2, H / 2, 16 + SIN[(uint8_t)(t >> 3)] / 16, WHITE);
   }
   ```

2. Declare `void fxMyFx(uint32_t t);` in [`effects.h`](cyber_hairclip/src/effects/effects.h).
3. Add `{fxMyFx}` to [`registry.cpp`](cyber_hairclip/src/effects/registry.cpp), or `{fxMyFx, 30}` to make it featured like Bad Apple.

Shared helpers from [`gfx.h`](cyber_hairclip/src/gfx.h): `display`, `W`/`H`, the integer sine table `SIN`, `frand`, `glitch` and `printKanjiShiro`. Keep state in `static` variables, avoid the heap, and stay under ~8 ms per frame: sending the frame over I2C already takes ~25 of the 33 ms.

## Battery and 24/7

- The radio is fully off, the ESP32 runs at 80 MHz and the OLED contrast is lowered. Rough estimate: 25–40 mA in total, so a battery lasts about its mAh ÷ 30 hours (not measured).
- No heap allocations and the `millis()` rollover is handled, so it can run indefinitely.
- OLEDs burn in. The random order spreads the wear, and a lower `CONTRAST` helps.
- The firmware runs until the cell is empty: use a LiPo with a protection circuit.

## Development

```sh
./test/run.sh
```

Builds the real firmware for the host against the stubs in [`test/mock`](test/mock), for both chips, and runs ~2 hours of simulated time across the `millis()` rollover under AddressSanitizer and UBSan. CI also compiles the firmware for ESP8266 and ESP32 with `arduino-cli`.

## Layout

```
cyber_hairclip/            Arduino sketch (open the .ino)
├── cyber_hairclip.ino     setup() and loop()
├── config.h               user settings
└── src/
    ├── gfx.*              display, sine table, glitch, 白 glyph
    ├── scheduler.*        shuffled playlist and featured effects
    ├── boot.*             boot log
    ├── power.*            radio off, CPU clock
    └── effects/           one file per animation + registry.cpp
tools/badapple.py          key-frame extractor for Bad Apple!!
test/                      host simulation and Arduino stubs
```
