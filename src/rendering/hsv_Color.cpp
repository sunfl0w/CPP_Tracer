#include "hsv_Color.hpp"

namespace Tracer::Rendering {
    HSV_Color::HSV_Color() {}

    HSV_Color::HSV_Color(unsigned int h, unsigned int s, unsigned int v) {
        this->h = h;
        this->s = s;
        this->v = v;
    }

    void HSV_Color::FromRGB(unsigned int r, unsigned int g, unsigned int b) {
        unsigned char rgbMin, rgbMax;

        rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
        rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

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

        if (rgbMax == r)
            h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
        else if (rgbMax == g)
            h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
        else
            h = 171 + 43 * (r - g) / (rgbMax - rgbMin);

        return;
    }
}  // namespace Tracer::Rendering