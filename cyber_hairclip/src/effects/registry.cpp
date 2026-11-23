#include "effects.h"

// To add an effect: write src/effects/<name>.cpp with `void fx<Name>(uint32_t t)`,
// declare it in effects.h and add one line here. Order does not matter: playback is shuffled.
const Effect EFFECTS[] = {
    {fxEye},      {fxMatrix},   {fxTesseract}, {fxWarp},  {fxRadar}, {fxBanner},
    {fxSynthwave}, {fxPulse},   {fxSpectrum},  {fxHelix}, {fxTerminal}, {fxCrack},
    {fxTor},      {fxHtop},     {fxLife},      {fxPanic}, {fxNeural},
};
const int NUM_EFFECTS = sizeof(EFFECTS) / sizeof(EFFECTS[0]);
static_assert(sizeof(EFFECTS) / sizeof(EFFECTS[0]) <= MAX_EFFECTS, "raise MAX_EFFECTS in effects.h");
