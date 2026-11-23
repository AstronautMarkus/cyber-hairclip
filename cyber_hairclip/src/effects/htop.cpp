#include "effects.h"

// htop with one core pinned at 100% by john (password cracking).
static void bar(const char *lb, int pct) {  // htop-style meter: 1[|||||  ]
  display.print(lb);
  display.print('[');
  for (int j = 0; j < 7; j++) display.print(j < pct * 7 / 100 ? '|' : ' ');
  display.print(']');
}

void fxHtop(uint32_t t) {
  static const int PID[] = {1337, 666, 9050, 22};
  static const char *const USR[] = {"root", "root", "tor", "root"}, *const CMD[] = {"john", "nmap", "tor", "sshd"};
  static int cpu[4], pc[4], load;
  static uint32_t tick = ~0u;
  if (t / 600 != tick) {  // htop refreshes about twice a second, not at 30 fps
    tick = t / 600;
    cpu[0] = random(92, 101);  // john eats a whole core
    for (int k = 1; k < 4; k++) cpu[k] = random(3, 60);
    pc[0] = random(950, 1000); pc[1] = random(150, 450); pc[2] = random(30, 120); pc[3] = random(0, 8);
    load = random(400, 440);
  }
  display.setCursor(0, 0);  bar("1", cpu[0]); display.print(' '); bar("2", cpu[1]);
  display.setCursor(0, 8);  bar("3", cpu[2]); display.print(' '); bar("4", cpu[3]);
  display.setCursor(0, 16); display.printf("Load: %d.%02d 1.33 0.77", load / 100, load % 100);
  display.fillRect(0, 24, W, 8, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(0, 24); display.print("  PID USER  CPU% CMD");
  display.setTextColor(WHITE);
  for (int k = 0; k < 4; k++) {
    display.setCursor(0, 32 + k * 8);
    display.printf("%5d %-5s%3d.%d %s", PID[k], USR[k], pc[k] / 10, pc[k] % 10, CMD[k]);
  }
}
