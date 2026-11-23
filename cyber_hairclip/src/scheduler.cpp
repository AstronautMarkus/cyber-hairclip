#include "scheduler.h"
#include <utility>
#include "gfx.h"
#include "../config.h"
#include "effects/effects.h"

static uint8_t bag[MAX_EFFECTS];
static int bagLen, bagPos, cur = -1;
static uint32_t fxStart;

// Random order, "shuffle bag" style: every regular effect plays once before any repeats, never twice in a row.
// Featured effects (chance > 0) stay out of the bag and may cut in after any other effect.
static int nextEffect() {
  for (int i = 0; i < NUM_EFFECTS; i++)
    if (EFFECTS[i].chance && i != cur && random(100) < EFFECTS[i].chance) return i;
  if (bagPos == bagLen) {
    bagLen = 0;
    for (int i = 0; i < NUM_EFFECTS; i++)
      if (!EFFECTS[i].chance) bag[bagLen++] = i;
    for (int i = bagLen - 1; i > 0; i--) std::swap(bag[i], bag[random(i + 1)]);  // Fisher-Yates
    if (bag[0] == cur) std::swap(bag[0], bag[bagLen - 1]);  // a new bag never starts with the effect just shown
    bagPos = 0;
  }
  return bag[bagPos++];
}

void schedulerBegin(uint32_t now) {
  cur = nextEffect();
  fxStart = now;
}

void schedulerDraw(uint32_t now) {
  if (now - fxStart >= FX_MS) {  // unsigned math: survives the millis() rollover at 49.7 days
    cur = nextEffect();
    fxStart = now;
  }
  uint32_t t = now - fxStart;
  EFFECTS[cur].draw(t);
  if (t < 250) glitch(6);  // transition between effects
}

int currentEffect() { return cur; }
