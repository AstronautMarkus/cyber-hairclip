#pragma once
#include <Arduino.h>

struct Adafruit_GFX : Print {
  virtual size_t write(uint8_t) { return 1; }  // hides Print::write overloads, like the real library
  void drawPixel(int16_t, int16_t, uint16_t) {}
  void drawLine(int16_t, int16_t, int16_t, int16_t, uint16_t) {}
  void drawFastHLine(int16_t, int16_t, int16_t, uint16_t) {}
  void drawFastVLine(int16_t, int16_t, int16_t, uint16_t) {}
  void drawRect(int16_t, int16_t, int16_t, int16_t, uint16_t) {}
  void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t) {}
  void drawCircle(int16_t, int16_t, int16_t, uint16_t) {}
  void fillCircle(int16_t, int16_t, int16_t, uint16_t) {}
  void fillTriangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, uint16_t) {}
  void drawChar(int16_t, int16_t, unsigned char, uint16_t, uint16_t, uint8_t) {}
  void drawBitmap(int16_t, int16_t, const uint8_t *b, int16_t w, int16_t h, uint16_t) {
    for (int i = 0; i < (w + 7) / 8 * h; i++) sink += b[i];  // touch every byte so ASan catches overreads
  }
  void setCursor(int16_t, int16_t) {}
  void setTextSize(uint8_t) {}
  void setTextColor(uint16_t) {}
  void setTextColor(uint16_t, uint16_t) {}
  void setTextWrap(bool) {}
  void setRotation(uint8_t) {}
  int16_t getCursorX() const { return 0; }
  int16_t getCursorY() const { return 0; }
  inline static volatile unsigned sink;
};
