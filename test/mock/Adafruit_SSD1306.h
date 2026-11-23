#pragma once
#include <Adafruit_GFX.h>
#include <Wire.h>

#define WHITE 1
#define BLACK 0
#define SSD1306_SWITCHCAPVCC 2
#define SSD1306_SETCONTRAST 0x81

struct Adafruit_SSD1306 : Adafruit_GFX {
  uint8_t buf[128 * 64 / 8];
  Adafruit_SSD1306(int, int, TwoWire *, int) {}
  bool begin(int, int) { return true; }
  void ssd1306_command(uint8_t) {}
  void clearDisplay() { memset(buf, 0, sizeof buf); }
  void display() { fake_ms += 25; }  // roughly what the 1 KB I2C transfer takes at 400 kHz
  uint8_t *getBuffer() { return buf; }
};
