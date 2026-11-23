#include "gfx.h"
#include "../config.h"

Adafruit_SSD1306 display(W, H, &Wire, -1);
int8_t SIN[256];

void gfxBegin() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(CONTRAST);
  display.setRotation(ROTATION);
  display.setTextColor(WHITE);
  display.setTextWrap(false);  // marquee text runs off the edge instead of wrapping
  for (int i = 0; i < 256; i++) SIN[i] = 127 * sin(i * TWO_PI / 256);
}

float frand(float a, float b) { return a + (b - a) * random(10000) / 10000.0f; }

void glitch(int n) {
  uint8_t *buf = display.getBuffer();
  while (n--) {
    uint8_t *row = buf + random(H / 8) * W;
    int s = random(-12, 13);
    if (s > 0) { memmove(row + s, row, W - s); memset(row, 0, s); }
    if (s < 0) { memmove(row, row - s, W + s); memset(row + W + s, 0, -s); }
    if (random(3) == 0)
      for (int x = random(W), e = x + random(8, 40); x < e && x < W; x++) row[x] ^= 0xFF;
  }
}

void printKanjiShiro(int s, uint16_t fg, uint16_t bg) {
  static const uint8_t K[7] = {0b00100, 0b01000, 0b11111, 0b10001, 0b11111, 0b10001, 0b11111};
  int x = display.getCursorX(), y = display.getCursorY();
  display.fillRect(x, y, 6 * s, 8 * s, bg);
  for (int r = 0; r < 7; r++)
    for (int c = 0; c < 5; c++)
      if (K[r] >> (4 - c) & 1) display.fillRect(x + c * s, y + r * s, s, s, fg);
  display.setCursor(x + 6 * s, y);
}
