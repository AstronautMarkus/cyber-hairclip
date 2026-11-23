#include "effects.h"

// N1 "implant": live neural spike raster and a decoded thought.
void fxNeural(uint32_t t) {
  const int CH = 12, Y0 = 11;  // visible channels, top row of the raster
  static const char *const THINK[] = {"GO TO MARS", "sudo make coffee", "I USE ARCH BTW", "42",
                                      "TABS > SPACES", "DOGE TO THE MOON", "MORE RAM PLZ", "HACK THE PLANET"};
  static uint16_t col[W];  // one bit per channel, one column per frame; col[W-1] is the newest
  static uint32_t per = ~0u;
  static int idx;
  bool burst = t % 2000 < 700;  // activity burst = the brain "thinks"; then it gets decoded
  if (t / 2000 != per) { per = t / 2000; idx = (idx + 1 + random(7)) % 8; }  // never the same thought twice

  uint16_t c = 0;
  for (int ch = 0; ch < CH; ch++)
    if (random(100) < (burst ? 22 : 4)) c |= 1 << ch;
  memmove(col, col + 1, sizeof col - sizeof col[0]);  // the raster scrolls left
  col[W - 1] = c;

  int n = 0;
  for (int x = 0; x < W; x++) {
    if (x >= W - 30) n += __builtin_popcount(col[x]);  // spikes in the last second
    for (int ch = 0; ch < CH; ch++)
      if (col[x] >> ch & 1) display.drawFastVLine(x, Y0 + ch * 3, 2, WHITE);
  }
  display.setCursor(0, 0);
  display.printf("N1 1024CH %5d SPK/S", n * 1024 / CH);
  display.setCursor(0, 56);
  if (burst) {
    display.print("DECODING");
    for (int i = 0; i < (int)(t % 2000 / 175); i++) display.print('.');
  } else {
    display.setTextColor(BLACK, WHITE);
    display.printf(" %s ", THINK[idx]);
    display.setTextColor(WHITE);
  }
}
