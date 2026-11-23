#include "effects.h"

// Rotating DNA double helix with a base-sequence ticker.
void fxHelix(uint32_t t) {
  int p1 = 0, p2 = 0;
  for (int x = 0; x < W; x += 2) {
    uint8_t a = x * 3 + (t >> 3);
    int s = SIN[a] * 22 / 127, front1 = SIN[(uint8_t)(a + 64)] > 0;  // strand 1 is in front when cos > 0
    int y1 = 30 + s, y2 = 30 - s;
    if (x % 8 == 0)  // dotted base-pair rungs
      for (int y = min(y1, y2) + 2; y < max(y1, y2) - 1; y += 2) display.drawPixel(x, y, WHITE);
    if (x) {
      display.drawLine(x - 2, p1, x, y1, WHITE);
      display.drawLine(x - 2, p2, x, y2, WHITE);
      if (front1) display.drawLine(x - 2, p1 + 1, x, y1 + 1, WHITE);  // the front strand is thicker
      else display.drawLine(x - 2, p2 + 1, x, y2 + 1, WHITE);
    }
    p1 = y1;
    p2 = y2;
  }
  for (uint32_t k = 0, o = t / 120; k < W / 6; k++)  // sequence read-out along the bottom
    display.drawChar(k * 6, 56, "ACGT"[((k + o) * 2654435761u) >> 30], WHITE, BLACK, 1);
}
