#include "color_utils.h"

namespace ColorUtils {

  HslColor::HslColor(RgbColor rgb) {
    *this = ColorUtils::rgb_to_hsl(rgb);
  }

  HslColor rgb_to_hsl(const RgbColor& rgb) {
    float r = rgb.r / 255.0F;
    float g = rgb.g / 255.0F;
    float b = rgb.b / 255.0F;

    float max = std::max(r, std::max(g, b));
    float min = std::min(r, std::min(g, b));
    float delta = max - min;

    float h, s, l = (max + min) / 2.0F;

    if (delta == 0) {
      h = 0;
      s = 0;
    } else {
      s = l < 0.5F ? delta / (max + min) : delta / (2 - max - min);

      if (max == r) {
        h = (g - b) / delta + (g < b ? 6 : 0);
      } else if (max == g) {
        h = (b - r) / delta + 2;
      } else {
        h = (r - g) / delta + 4;
      }

      h /= 6;
    }

    return HslColor(h, s, l);
  }

  RgbColor hsl_to_rgb(const HslColor& hsl) {
    float r, g, b;

    if (hsl.s == 0) {
      r = g = b = hsl.l; // achromatic
    } else {
      auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0 / 6) return p + (q - p) * 6 * t;
        if (t < 1.0 / 2) return q;
        if (t < 2.0 / 3) return p + (q - p) * (2.0 / 3 - t) * 6;
        return p;
        };

      float q = hsl.l < 0.5 ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
      float p = 2 * hsl.l - q;
      r = hue2rgb(p, q, hsl.h + 1.0 / 3);
      g = hue2rgb(p, q, hsl.h);
      b = hue2rgb(p, q, hsl.h - 1.0 / 3);
    }

    return RgbColor(static_cast<uint8_t>(r * 255), static_cast<uint8_t>(g * 255), static_cast<uint8_t>(b * 255));
  }

} // namespace ColorUtils