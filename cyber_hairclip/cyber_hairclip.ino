// CYBER HAIRCLIP: animations for a 128x64 SSD1306 OLED on ESP8266 / ESP32.
// Libraries (Library Manager): "Adafruit SSD1306" and "Adafruit GFX Library".
// Settings live in config.h. Animations live in src/effects/, one file each, listed in registry.cpp.

#include "config.h"
#include "src/gfx.h"
#include "src/power.h"
#include "src/boot.h"
#include "src/scheduler.h"

void setup() {
  powerSave();
  gfxBegin();
  bootSequence();
  schedulerBegin(millis());
}

void loop() {
  uint32_t now = millis();
  display.clearDisplay();
  display.setTextSize(1);  // effects may leave the text size changed (the banner uses 2)
  schedulerDraw(now);
  display.display();
  uint32_t spent = millis() - now;
  if (spent < FRAME_MS) delay(FRAME_MS - spent);  // steady frame rate on both chips
}
