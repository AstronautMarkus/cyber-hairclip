#pragma once
#include <stdint.h>

void schedulerBegin(uint32_t now);  // pick the first effect
void schedulerDraw(uint32_t now);   // draw the current effect; switches to the next one every FX_MS
int currentEffect();                // index into EFFECTS (tests, debugging)
