#include "effects.h"

// Hyperspace jump: star streaks that keep accelerating, arriving at BANNER.
void fxWarp(uint32_t t) {
  const int N = 70;
  static float sx[N], sy[N], sz[N];
  float v = 0.006f + t * 0.000006f;
  for (int i = 0; i < N; i++) {
    float z0 = sz[i];
    sz[i] -= v;
    if (sz[i] <= 0.02f) { sx[i] = frand(-1, 1); sy[i] = frand(-1, 1); sz[i] = frand(0.5f, 1); continue; }
    display.drawLine(W / 2 + sx[i] / z0 * 40, H / 2 + sy[i] / z0 * 40,
                     W / 2 + sx[i] / sz[i] * 40, H / 2 + sy[i] / sz[i] * 40, WHITE);
  }
  if (t > FX_MS - 1500) {  // arrival
    display.setTextColor(WHITE, BLACK);
    display.setCursor((W - (int)strlen(BANNER) * 6) / 2, 28);
    display.print(BANNER);
    display.setTextColor(WHITE);
  }
}
