#include "effects.h"

// Cybernetic eye: darts around, blinks, the pupil breathes and a segmented iris ring spins.
void fxEye(uint32_t) {
  static float gx, gy;
  static int tx, ty;
  static uint32_t nextLook, blinkAt;
  uint32_t now = millis();  // absolute time: gaze and blinks carry on across turns

  // signed differences keep working when millis() wraps after 49.7 days
  if ((int32_t)(now - nextLook) > 0) { tx = random(-16, 17); ty = random(-7, 8); nextLook = now + random(300, 2500); }
  gx += (tx - gx) * 0.35f;  // fast, saccade-like movement
  gy += (ty - gy) * 0.35f;
  if ((int32_t)(now - blinkAt) > 200) blinkAt = now + random(1200, 5000);
  int32_t b = now - blinkAt;  // ms since the blink started (negative = not yet)
  float open = b >= 0 ? fabsf(1 - b / 100.0f) : 1;  // 1 -> 0 -> 1 over 200 ms

  const int cx = 64, cy = 32, EW = 56, EH = 27;
  int ix = cx + gx, iy = cy + gy;
  int pr = 7 + SIN[(uint8_t)(now >> 4)] / 50;  // pupil radius 5..9 px

  display.fillCircle(ix, iy, 21, WHITE);
  display.fillCircle(ix, iy, 19, BLACK);
  display.drawCircle(ix, iy, 16, WHITE);
  for (int i = 0; i < 16; i++) {  // spinning segmented ring
    uint8_t a = (uint8_t)(i * 16 + (now >> 4));
    int c = SIN[(uint8_t)(a + 64)], s = SIN[a];
    display.drawLine(ix + c * (pr + 2) / 127, iy + s * (pr + 2) / 127,
                     ix + c * 14 / 127, iy + s * 14 / 127, WHITE);
  }
  display.drawCircle(ix, iy, pr, WHITE);
  display.fillCircle(ix - 6, iy - 7, 2, WHITE);  // highlight

  // Eyelids: clear everything outside the almond shape and draw its outline
  for (int x = 0; x < W; x++) {
    float d = (x - cx) / (float)EW;
    if (d * d >= 1) { display.drawFastVLine(x, 0, H, BLACK); continue; }
    int h = EH * (1 - d * d) * open;
    display.drawFastVLine(x, 0, cy - h, BLACK);
    display.drawFastVLine(x, cy + h + 1, H - cy - h - 1, BLACK);
    display.drawPixel(x, cy - h, WHITE);
    display.drawPixel(x, cy - h - 1, WHITE);  // thicker upper lid
    display.drawPixel(x, cy + h, WHITE);
  }
  for (int i = 0; i < 4; i++) {  // HUD corner brackets
    int x = i & 1 ? W - 1 : 0, y = i & 2 ? H - 1 : 0, sx = i & 1 ? -1 : 1, sy = i & 2 ? -1 : 1;
    display.drawLine(x, y, x + 7 * sx, y, WHITE);
    display.drawLine(x, y, x, y + 7 * sy, WHITE);
  }
}
