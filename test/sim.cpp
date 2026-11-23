// Runs the real firmware against the stubs in test/mock for ~2 hours of simulated time,
// across the millis() rollover, and checks the playlist rules. Build and run with test/run.sh.
#include <Arduino.h>
#include <vector>
#include "../cyber_hairclip/src/effects/effects.h"
#include "../cyber_hairclip/src/scheduler.h"

void setup();
void loop();

int main() {
  fake_ms = 0xFFFFFFFFu - 200000;  // millis() wraps ~200 s into the run
  setup();
  std::vector<int> seq{currentEffect()};
  std::vector<uint32_t> start{fake_ms};
  for (int frame = 0; frame < 200000; frame++) {
    int before = currentEffect();
    uint32_t now = fake_ms;
    loop();
    if (currentEffect() != before) {
      seq.push_back(currentEffect());
      start.push_back(now);
    }
  }

  int regular = 0, featured = 0;
  for (int i = 0; i < NUM_EFFECTS; i++) EFFECTS[i].chance ? featured++ : regular++;
  for (size_t i = 1; i < seq.size(); i++) {
    assert(seq[i] != seq[i - 1]);                 // never the same effect twice in a row
    uint32_t d = start[i] - start[i - 1];
    assert(d >= FX_MS && d < FX_MS + FRAME_MS * 2);  // every turn lasts FX_MS, also across the rollover
  }
  std::vector<int> bagged;
  for (int s : seq)
    if (!EFFECTS[s].chance) bagged.push_back(s);
  for (size_t b = 0; b + regular <= bagged.size(); b += regular) {  // regular effects come in full bags
    std::vector<bool> seen(NUM_EFFECTS);
    for (int i = 0; i < regular; i++) {
      assert(!seen[bagged[b + i]]);
      seen[bagged[b + i]] = true;
    }
  }
  printf("OK: %d effects (%d featured), %zu turns, %zu featured turns\n", NUM_EFFECTS, featured, seq.size(),
         seq.size() - bagged.size());
}
