#include "effects.h"

// Brute-forcing a hash. It is the real SHA-256 of "Shiro (白)" in UTF-8.
void fxCrack(uint32_t t) {
  const char *PASS = "Shiro (\x01)";  // \x01 = 白
  const int LEN = 9, X0 = (W - LEN * 12) / 2;
  const uint32_t STEP = 650, DONE = LEN * STEP;  // one character found every 0.65 s
  int locked = min(LEN, (int)(t / STEP));
  display.setCursor(0, 0);  display.print("$ hashcat -m1400 -a3");
  display.setCursor(0, 10); display.print("5fffcb6d8866ba6bbbf96");
  display.setCursor(0, 18); display.print("94d3e3f209bcdfea8a...");
  display.setTextSize(2);
  display.setCursor(X0, 28);
  for (int i = 0; i < LEN; i++)
    if (i >= locked) display.print((char)random(33, 127));
    else if (PASS[i] == '\x01') printKanjiShiro(2, WHITE, BLACK);
    else display.print(PASS[i]);
  display.setTextSize(1);
  for (int i = 0; i < locked; i++)  // underline what has been found
    if (PASS[i] != ' ') display.drawFastHLine(X0 + i * 12, 45, 10, WHITE);
  display.drawRect(0, 48, W, 5, WHITE);
  display.fillRect(1, 49, (W - 2) * min(t, DONE) / DONE, 3, WHITE);
  display.setCursor(0, 56);
  if (locked < LEN) {
    display.printf("%4d.%d MH/s  %3d%%", (int)random(1300, 1370), (int)random(10), (int)(t * 100 / DONE));
  } else {
    uint16_t fg = (t >> 7) & 1 ? BLACK : WHITE, bg = fg == WHITE ? BLACK : WHITE;  // blink inverted
    display.setTextColor(fg, bg);
    display.print(" CRACKED: Shiro (");
    printKanjiShiro(1, fg, bg);
    display.print(") ");
    display.setTextColor(WHITE);
    if (t < DONE + 150) glitch(4);
  }
}
