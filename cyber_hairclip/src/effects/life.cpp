#include "effects.h"

// Conway's Game of Life on a 64x32 torus, with gliders dropped in so it never dies out.
void fxLife(uint32_t t) {
  const int GW = W / 2, GH = H / 2;  // 2x2 px cells
  static const uint8_t GL[5][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};  // glider (row, col)
  static uint8_t g[GH][GW], nx[GH][GW];
  static uint32_t last = ~0u, gen;
  if (t < last) {  // new turn: reseed
    for (int y = 0; y < GH; y++)
      for (int x = 0; x < GW; x++) g[y][x] = random(4) == 0;
    gen = 0;
  }
  last = t;
  if (t / 80 != gen) {  // ~12 generations per second
    gen = t / 80;
    for (int y = 0; y < GH; y++)
      for (int x = 0; x < GW; x++) {
        int n = -g[y][x];
        for (int dy = -1; dy <= 1; dy++)
          for (int dx = -1; dx <= 1; dx++) n += g[(y + dy + GH) % GH][(x + dx + GW) % GW];
        nx[y][x] = n == 3 || (n == 2 && g[y][x]);
      }
    memcpy(g, nx, sizeof g);
    if (gen % 15 == 0) {  // drop a glider so it never dies out
      int ox = random(GW), oy = random(GH);
      for (auto &c : GL) g[(oy + c[0]) % GH][(ox + c[1]) % GW] = 1;
    }
  }
  for (int y = 0; y < GH; y++)
    for (int x = 0; x < GW; x++)
      if (g[y][x]) display.fillRect(x * 2, y * 2, 2, 2, WHITE);
}
