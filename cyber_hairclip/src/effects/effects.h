#pragma once
#include "../gfx.h"
#include "../../config.h"

// An effect draws one frame. t = ms since the effect started this turn (0..FX_MS).
// Effects keep their own state in statics; one that needs a fresh start can detect a new turn when t goes backwards.
typedef void (*EffectFn)(uint32_t t);

struct Effect {
  EffectFn draw;
  uint8_t chance;  // 0 = regular (shuffle bag); >0 = featured: % chance to cut in after any other effect
};

constexpr int MAX_EFFECTS = 32;
extern const Effect EFFECTS[];  // registry.cpp
extern const int NUM_EFFECTS;

void fxEye(uint32_t t);
void fxMatrix(uint32_t t);
void fxTesseract(uint32_t t);
void fxWarp(uint32_t t);
void fxRadar(uint32_t t);
void fxBanner(uint32_t t);
void fxSynthwave(uint32_t t);
void fxPulse(uint32_t t);
void fxSpectrum(uint32_t t);
void fxHelix(uint32_t t);
void fxTerminal(uint32_t t);
void fxCrack(uint32_t t);
void fxTor(uint32_t t);
void fxHtop(uint32_t t);
void fxLife(uint32_t t);
void fxPanic(uint32_t t);
void fxNeural(uint32_t t);
void fxBadApple(uint32_t t);
