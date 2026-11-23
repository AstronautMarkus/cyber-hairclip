#include "effects.h"

// Radar sweep with blips, a fading trail and target lock.
void fxRadar(uint32_t t) {
  const int cx = 31, cy = 32, R = 30, NB = 5;
  static uint8_t ba[NB], br[NB];
  static uint32_t turn = 0xFFFFFFFF;
  uint8_t a = t >> 3;  // one revolution every ~2 s

  if (turn == 0xFFFFFFFF) for (int k = 0; k < NB; k++) { ba[k] = random(256); br[k] = random(6, R - 2); }
  if (t / 2048 != turn) { turn = t / 2048; int k = random(NB); ba[k] = random(256); br[k] = random(6, R - 2); }

  display.drawCircle(cx, cy, R, WHITE);
  display.drawCircle(cx, cy, R * 2 / 3, WHITE);
  display.drawCircle(cx, cy, R / 3, WHITE);
  for (int i = -R; i <= R; i += 3) { display.drawPixel(cx + i, cy, WHITE); display.drawPixel(cx, cy + i, WHITE); }

  display.drawLine(cx, cy, cx + SIN[(uint8_t)(a + 64)] * R / 127, cy + SIN[a] * R / 127, WHITE);
  for (int k = 1; k < 14; k++) {  // trail: sparser further back, so it fades out
    uint8_t aa = a - k * 2;
    for (int r = 4 + k % 3; r < R; r += 2 + k / 3)
      display.drawPixel(cx + SIN[(uint8_t)(aa + 64)] * r / 127, cy + SIN[aa] * r / 127, WHITE);
  }

  int seen = 0, lock = -1;
  for (int k = 0; k < NB; k++) {
    uint8_t age = a - ba[k];  // how long since the sweep passed this blip
    if (age > 170) continue;
    seen++;
    int x = cx + SIN[(uint8_t)(ba[k] + 64)] * br[k] / 127, y = cy + SIN[ba[k]] * br[k] / 127;
    display.fillCircle(x, y, age < 50 ? 2 : 1, WHITE);
    if (age < 50) {
      lock = k;
      if ((t >> 7) & 1) display.drawRect(x - 5, y - 5, 11, 11, WHITE);
    }
  }

  display.setCursor(68, 2);  display.print("RADAR");
  display.setCursor(68, 16); display.printf("BRG %03d", a * 360 / 256);
  display.setCursor(68, 28); display.printf("OBJ %d", seen);
  display.setCursor(68, 40);
  if (lock >= 0) display.printf("RNG %03dm", br[lock] * 7);
  else display.print("RNG ---");
  if (lock >= 0 && (t >> 7) & 1) {
    display.setTextColor(BLACK, WHITE);
    display.setCursor(68, 54); display.print(" LOCK ");
    display.setTextColor(WHITE);
  }
}
