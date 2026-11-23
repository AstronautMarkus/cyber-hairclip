#include "effects.h"

// Digital rain. BANNER hides in row 4, shows wherever drops pass, and is fully revealed at the end.
static constexpr int COLS = W / 6, ROWS = H / 8;  // 6x8 px cells: 21 columns x 8 rows

void fxMatrix(uint32_t t) {
  static char g[ROWS][COLS];
  static float head[COLS], speed[COLS];
  static int len[COLS];

  for (int c = 0; c < COLS; c++) {
    if (speed[c] == 0 || head[c] - len[c] > ROWS) {  // first run, or the drop has left the screen
      head[c] = -random(0, 10);
      speed[c] = frand(0.1f, 0.4f);
      len[c] = random(3, 9);
      for (int r = 0; r < ROWS; r++) g[r][c] = random(33, 127);
    }
    if (c >= 1 && c - 1 < (int)strlen(BANNER)) g[4][c] = BANNER[c - 1];  // hidden message
    head[c] += speed[c];
    int hd = head[c];
    for (int r = hd - len[c]; r <= hd; r++) {
      if (r < 0 || r >= ROWS) continue;
      int x = c * 6, y = r * 8;
      if (r == hd) {
        display.drawChar(x, y, g[r][c], BLACK, WHITE, 1);  // inverted head
        continue;
      }
      display.drawChar(x, y, g[r][c], WHITE, BLACK, 1);
      if (r < hd - len[c] / 2)  // tail: clear every other pixel so it looks dimmer
        for (int j = 0; j < 8; j++)
          for (int i = j & 1; i < 6; i += 2) display.drawPixel(x + i, y + j, BLACK);
    }
  }
  g[random(ROWS)][random(COLS)] = random(33, 127);  // glyphs mutate
  if (t > FX_MS - 2000) {  // full reveal at the end
    display.fillRect(0, 31, W, 10, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(6, 32);
    display.print(BANNER);
    display.setTextColor(WHITE);
  }
}
