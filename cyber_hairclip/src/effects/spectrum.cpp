#include "effects.h"

// Spectrum analyzer: 16 LED-segment bars, a kick drum on the bass and falling peak caps.
void fxSpectrum(uint32_t t) {
  const int NB = 16, BW = W / NB;
  static float lvl[NB], peak[NB];
  bool kick = t % 469 < 70;  // kick drum at ~128 bpm
  for (int i = 0; i < NB; i++) {
    int v = 14 + SIN[(uint8_t)(i * 23 + (t >> 3))] / 9 + SIN[(uint8_t)(i * 61 - (t >> 2))] / 12 + random(12);
    if (kick) v += (NB - i) * 2;  // the kick hits the low bands harder
    v = constrain(v, 1, H - 4);
    lvl[i] = v > lvl[i] ? v : lvl[i] - 1.5f;  // jumps up, falls slowly
    peak[i] = lvl[i] > peak[i] ? lvl[i] : peak[i] - 0.4f;
    int x = i * BW;
    for (int y = H - 2; y > H - lvl[i]; y -= 3) display.fillRect(x, y, BW - 1, 2, WHITE);  // LED segments
    display.drawFastHLine(x, H - 3 - (int)peak[i], BW - 1, WHITE);
  }
}
