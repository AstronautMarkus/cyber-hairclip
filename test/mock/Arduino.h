#pragma once
// Minimal Arduino stand-ins so the firmware builds and runs on a PC (see test/run.sh).
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using std::max;  // the ESP cores use std::min/max too, which reject mixed argument types
using std::min;

#define constrain(a, l, h) ((a) < (l) ? (l) : ((a) > (h) ? (h) : (a)))
#define TWO_PI 6.283185307179586
#define PROGMEM

inline uint32_t fake_ms;  // simulated clock: delay() advances it
inline uint32_t millis() { return fake_ms; }
inline void delay(uint32_t ms) { fake_ms += ms; }
inline long random(long h) { return h ? rand() % h : 0; }
inline long random(long l, long h) { return h > l ? l + rand() % (h - l) : l; }
inline bool setCpuFrequencyMhz(uint32_t) { return true; }

struct Print {
  size_t print(const char *) { return 0; }
  size_t print(char) { return 0; }
  size_t print(int) { return 0; }
  size_t printf(const char *f, ...) __attribute__((format(printf, 2, 3))) {
    char b[64];
    va_list a;
    va_start(a, f);
    int n = vsnprintf(b, sizeof b, f, a);
    va_end(a);
    assert(n < 64);  // the ESP cores fall back to the heap above 64 chars
    return n;
  }
};
