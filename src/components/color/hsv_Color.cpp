#include "hsv_Color.hpp"

namespace Tracer::Components::Color {
    HSV_Color::HSV_Color() {}

    HSV_Color::HSV_Color(unsigned int h, unsigned int s, unsigned int v) {
        this->h = h;
        this->s = s;
        this->v = v;
    }

    HSV_Color::HSV_Color(const RGB_Color& rgbColor) {
        unsigned char rgbMin, rgbMax;

        rgbMin = rgbColor.r < rgbColor.g ? (rgbColor.r < rgbColor.b ? rgbColor.r : rgbColor.b) : (rgbColor.g < rgbColor.b ? rgbColor.g : rgbColor.b);
        rgbMax = rgbColor.r > rgbColor.g ? (rgbColor.r > rgbColor.b ? rgbColor.r : rgbColor.b) : (rgbColor.g > rgbColor.b ? rgbColor.g : rgbColor.b);

        v = rgbMax;
        if (v == 0) {
            h = 0;
            s = 0;
            return;
        }

        s = 255 * long(rgbMax - rgbMin) / v;
        if (s == 0) {
            h = 0;
            return;
        }

        if (rgbMax == rgbColor.r) {
            h = 0 + 43 * (rgbColor.g - rgbColor.b) / (rgbMax - rgbMin);
        } else if (rgbMax == rgbColor.g) {
            h = 85 + 43 * (rgbColor.b - rgbColor.r) / (rgbMax - rgbMin);
        } else {
            h = 171 + 43 * (rgbColor.r - rgbColor.g) / (rgbMax - rgbMin);
        }
    }
}  // namespace Tracer::Components::Color