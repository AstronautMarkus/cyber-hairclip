#include "effects.h"

// BANNER as a marquee over a modulated wave, with glitch bursts.
void fxBanner(uint32_t t) {
  display.setCursor(4, 4);
  display.print("> SIGNAL: ONLINE");
  if ((t >> 8) & 1) display.print('_');
  display.setTextSize(2);
  display.setCursor(W - (int)(t / 14 % (W + strlen(BANNER) * 12)), 22);  // marquee
  display.print(BANNER);
  int py = 56;
  for (int x = 0; x < W; x++) {  // modulated wave along the bottom
    int y = 56 + SIN[(uint8_t)(x * 5 + (t >> 2))] * SIN[(uint8_t)(x * 2 - (t >> 3))] / 2200;
    if (x) display.drawLine(x - 1, py, x, y, WHITE);
    py = y;
  }
  if (random(10) < 3) glitch(random(1, 4));
  if (t % 1500 < 100) glitch(10);  // heavy burst
}
