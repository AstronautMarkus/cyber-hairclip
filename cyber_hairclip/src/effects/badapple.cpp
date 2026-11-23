#include "effects.h"

// Bad Apple!!: a few key frames at a few fps, choppy on purpose. Each turn resumes where the
// previous one stopped, so the song plays in chapters. The frames are not in the repo:
// generate badapple_frames.h with tools/badapple.py; without it this effect is left out.
#if __has_include("badapple_frames.h")
#include "badapple_frames.h"

void fxBadApple(uint32_t t) {
  static uint32_t base, last;
  if (t < last) base += last * BA_FPS / 1000 + 1;  // new turn: continue right after the last frame shown
  last = t;
  uint32_t f = (base + t * BA_FPS / 1000) % BA_N;
  display.drawBitmap((W - BA_W) / 2, 0, BA_FRAMES + f * (BA_W * BA_H / 8), BA_W, BA_H, WHITE);
}
#endif
