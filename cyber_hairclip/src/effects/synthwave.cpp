#include "effects.h"

// Synthwave sunset: striped sun, twinkling stars and a perspective grid rolling towards you.
void fxSynthwave(uint32_t t) {
  const int HZ = 30, R = 22;  // horizon line, sun radius
  for (int k = 0; k < 14; k++)  // twinkling stars
    if ((k + (t >> 8)) % 5) display.drawPixel(k * 37 % W, k * 13 % 24, WHITE);
  for (int dy = 1; dy <= R; dy++) {  // sun: half disc with stripes sliding down into the horizon
    if (dy < 12 && (dy + (t >> 6)) % 4 < (dy < 6 ? 2 : 1)) continue;
    int hw = sqrtf(R * R - dy * dy);
    display.drawFastHLine(64 - hw, HZ - dy, hw * 2 + 1, WHITE);
  }
  display.drawFastHLine(0, HZ, W, WHITE);
  for (int k = -12; k <= 12; k++) display.drawLine(64 + k * 2, HZ, 64 + k * 32, H - 1, WHITE);
  float f = (t % 400) / 400.0f;  // horizontal lines approach with 1/z perspective
  for (int i = 0; i < 8; i++) {
    int y = HZ + 34 / (i + 1 - f);
    if (y < H) display.drawFastHLine(0, y, W, WHITE);
  }
}
