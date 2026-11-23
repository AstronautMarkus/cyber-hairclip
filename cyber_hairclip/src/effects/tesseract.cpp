#include "effects.h"

// 4D hypercube (tesseract) rotating, projected 4D -> 3D -> 2D.
static void rot(float &p, float &q, float a) {
  float c = cosf(a), s = sinf(a), p2 = p * c - q * s;
  q = p * s + q * c;
  p = p2;
}

void fxTesseract(uint32_t t) {
  int16_t px[16], py[16];
  for (int i = 0; i < 16; i++) {
    float x = i & 1 ? 1 : -1, y = i & 2 ? 1 : -1, z = i & 4 ? 1 : -1, w = i & 8 ? 1 : -1;
    rot(x, w, t * 0.0009f);  // XW plane: the rotation that only exists in 4D
    rot(y, z, t * 0.0006f);
    rot(x, y, t * 0.0004f);
    float k = 1 / (2.6f - w);        // 4D -> 3D
    float s = 78 * k / (3 - z * k);  // 3D -> 2D
    px[i] = W / 2 + x * s;
    py[i] = H / 2 + y * s;
  }
  for (int i = 0; i < 16; i++) {
    display.fillCircle(px[i], py[i], 1, WHITE);
    for (int b = 1; b < 16; b <<= 1)  // an edge joins two vertices that differ in one bit
      if (!(i & b)) display.drawLine(px[i], py[i], px[i | b], py[i | b], WHITE);
  }
}
