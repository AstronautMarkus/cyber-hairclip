#include "effects.h"

// Heart monitor: a sweeping cursor redraws the ECG trace; the heart icon beats on the QRS.
static constexpr int BEAT = 50;  // samples per beat (15 ms each = 80 bpm)

static int ecg(int p) {  // height in px above the baseline: P wave, QRS complex, T wave
  static const int8_t QRS[] = {-3, 9, 22, 4, -7};
  if (p >= 4 && p < 10) return SIN[(p - 4) * 21] / 40;
  if (p >= 16 && p < 21) return QRS[p - 16];
  if (p >= 28 && p < 40) return SIN[(p - 28) * 10] / 25;
  return 0;
}

void fxPulse(uint32_t t) {
  const int BASE = 44;
  int n = t / 15, cur = n % W, py = -1;  // the cursor sweeps across and overwrites the old trace
  for (int y = 12; y < 56; y += 8)
    for (int x = 4; x < W; x += 8) display.drawPixel(x, y, WHITE);  // monitor grid
  for (int x = 0; x < W; x++) {
    int d = (cur - x + W) % W;  // samples since the cursor passed this column
    if (d > W - 8) { py = -1; continue; }  // gap ahead of the cursor
    int y = BASE - ecg(((n - d) % BEAT + BEAT) % BEAT);
    if (py >= 0) display.drawLine(x - 1, py, x, y, WHITE);
    py = y;
  }
  display.fillCircle(cur, BASE - ecg(n % BEAT), 1, WHITE);

  int r = n % BEAT >= 16 && n % BEAT < 26 ? 4 : 3, hx = 118, hy = 6;  // beating heart
  display.fillCircle(hx - r, hy, r, WHITE);
  display.fillCircle(hx + r, hy, r, WHITE);
  display.fillTriangle(hx - 2 * r, hy + 1, hx + 2 * r, hy + 1, hx, hy + 3 * r, WHITE);
  display.setCursor(0, 0);  display.print("HR 80 BPM");
  display.setCursor(0, 56); display.print("SpO2 98%  NEURO OK");
}
