#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <algorithm>
#include <cstdint>

namespace ColorUtils {

  struct RgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    RgbColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    RgbColor(uint8_t w) : r(w), g(w), b(w) {}
    RgbColor() : r(0), g(0), b(0) {}
  };

  struct HslColor {
    float h;
    float s;
    float l;

    HslColor(float h, float s, float l) : h(h), s(s), l(l) {}
    HslColor(RgbColor rgb);

    static HslColor linear_blend(HslColor a, HslColor b, float progress) {
      float h = a.h + (b.h - a.h) * progress;
      float s = a.s + (b.s - a.s) * progress;
      float l = a.l + (b.l - a.l) * progress;
      return HslColor(h, s, l);
    }
  };

  HslColor rgb_to_hsl(const RgbColor& rgb);
  RgbColor hsl_to_rgb(const HslColor& hsl);

} // namespace ColorUtils

#endif // COLOR_UTILS_H