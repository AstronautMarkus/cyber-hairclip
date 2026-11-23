#pragma once
#include <stdint.h>

// ---------------- User settings ----------------
constexpr uint32_t FX_MS = 8000;         // how long each animation runs (ms)
constexpr uint32_t FRAME_MS = 33;        // frame period: ~30 fps
constexpr uint8_t ROTATION = 0;          // 2 = rotate 180° if the clip sits upside down (effects assume 128x64 landscape)
constexpr uint8_t CONTRAST = 0x50;       // OLED brightness 0-255 (Adafruit default 207): lower = longer battery, less burn-in
constexpr uint8_t OLED_ADDR = 0x3C;      // I2C address (some modules use 0x3D)
constexpr uint8_t BADAPPLE_CHANCE = 25;  // % chance Bad Apple cuts in after each animation (25 ≈ 1 turn in 5); 0 = regular
constexpr char BANNER[] = "AstronautMarkus.Dev";  // signature: boot log, banner, hidden in the rain, warp arrival (max 20)
