#include "effects.h"

// dmesg scrolling at full speed... until a kernel panic.
void fxPanic(uint32_t t) {
  static const char *const MSG[] = {"eth0: up", "usb 1-1: new", "ext4: mount", "tor: ready", "audit: deny",
                                    "wlan0: down", "cpu0: hot", "sshd: listen", "oom: kill"};
  const uint32_t PANIC = 4800;
  if (t < PANIC) {
    int k = t / 90;  // a new line every 90 ms
    for (int i = max(0, k - 7), row = 0; i <= k; i++, row++) {
      const char *m = t > PANIC - 900 && i % 2 ? "sda: I/O err" : MSG[(i * 7 + i / 3) % 9];  // foreshadowing
      display.setCursor(0, row * 8);
      display.printf("[%3d.%02d] %s", i * 137 / 1000, i * 137 % 1000 / 10, m);
    }
    return;
  }
  static const char *const KP[] = {"Kernel panic - not", "syncing: VFS: Unable", "to mount root fs on",
                                   "unknown-block(0,0)", "", "---[ end Kernel panic"};
  for (int i = 0; i < 6; i++) {
    if (i == 0) display.setTextColor(BLACK, WHITE);
    display.setCursor(0, i * 8);
    display.print(KP[i]);
    display.setTextColor(WHITE);
  }
  if ((t >> 8) & 1) { display.setCursor(0, 56); display.printf("REBOOTING IN %ds...", (int)((FX_MS - t) / 1000 + 1)); }
  if (t < PANIC + 200) glitch(10);
  else if (random(12) == 0) glitch(2);
}
