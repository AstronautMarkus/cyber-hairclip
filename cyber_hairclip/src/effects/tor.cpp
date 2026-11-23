#include "effects.h"

// Tor circuit: the packet sheds one encryption layer at each hop; a new circuit on every trip.
void fxTor(uint32_t t) {
  static const char *const CC[] = {"DE", "NL", "IS", "CH", "SE", "RO", "FI", "US"};
  static const char *const ST[] = {"IP.......[REDACTED]", "MAC.........SPOOFED", "DNS........NO LEAKS",
                                   "JS.........DISABLED", "OPSEC.......NOMINAL"};
  const int Y = 28, GAP = 27, LEG = 600;  // circuit row, px between nodes, ms per hop
  uint32_t id = t / (LEG * 4), p = t % (LEG * 4);  // new circuit on every trip
  display.setCursor(0, 0);
  display.printf("TOR CIRCUIT #%04X", (unsigned)(id * 2654435761u >> 16));
  for (int i = 0; i < 5; i++) {
    int x = 10 + i * GAP;
    const char *lb = i == 0 ? "YOU" : i == 4 ? "SRV" : CC[(id * 3 + i * 5) % 8];
    display.drawRect(x - 3, Y - 3, 7, 7, WHITE);
    display.setCursor(x - (int)strlen(lb) * 3, Y + 9);
    display.print(lb);
    if (i < 4)  // link with marching ants
      for (int d = 5 + (t >> 6) % 3; d < GAP - 4; d += 3) display.drawPixel(x + d, Y, WHITE);
  }
  int s = p / LEG, x = 10 + s * GAP + (p % LEG) * GAP / LEG;
  display.fillCircle(x, Y, 2, WHITE);
  for (int k = 0; k < 3 - s; k++) display.drawCircle(x, Y, 5 + k * 2, WHITE);  // layers left
  if (s > 0 && p % LEG < 150) display.drawCircle(10 + s * GAP, Y, 6 + (p % LEG) / 10, WHITE);  // layer being shed
  display.setCursor(0, 56);
  display.print(ST[t / 1600 % 5]);
}
