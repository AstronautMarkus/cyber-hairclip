#include "boot.h"
#include "gfx.h"
#include "../config.h"

void bootSequence() {
  char signature[24];
  snprintf(signature, sizeof signature, "> %s", BANNER);
  const char *lines[] = {signature, "> N1 FW 0.9.1-beta", "> 64 THREADS..... OK", "> 1024 ELECTRODES OK",
                         "> UNIT 001/001 VIP"};
  display.clearDisplay();
  display.setTextSize(1);
  for (int l = 0; l < 5; l++) {
    display.setCursor(0, l * 10);
    for (const char *c = lines[l]; *c; c++) {
      display.print(*c);
      display.display();
      delay(18);
    }
    delay(150);
  }
  for (int x = 0; x <= W - 4; x += 4) {  // loading bar
    display.drawRect(0, 52, W, 10, WHITE);
    display.fillRect(2, 54, x, 6, WHITE);
    display.display();
    delay(12);
  }
  delay(300);
}
