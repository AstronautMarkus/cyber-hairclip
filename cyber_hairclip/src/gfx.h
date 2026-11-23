#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr int W = 128, H = 64;  // screen size in pixels

extern Adafruit_SSD1306 display;
extern int8_t SIN[256];  // integer sine, 256 steps per turn: fast even without an FPU (ESP8266)

void gfxBegin();
float frand(float a, float b);
void glitch(int n);  // "corrupted signal": shifts 8 px bands and inverts chunks of the frame buffer

// 白 ("shiro", white) hand-drawn at 5x7 like the font, since the Adafruit font is ASCII only.
// Write it as '\x01' inside strings. Draws at the cursor and advances it; scale works like setTextSize.
void printKanjiShiro(int scale, uint16_t fg, uint16_t bg);
