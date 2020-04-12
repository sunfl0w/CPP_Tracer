#include "rgb_Color.hpp"

namespace Tracer::Components::Color {
    RGB_Color::RGB_Color() {}

    RGB_Color::RGB_Color(unsigned int r, unsigned int g, unsigned int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void RGB_Color::FromHSV(unsigned int h, unsigned int s, unsigned int v) {
        unsigned char region, remainder, p, q, t;

        if (s == 0) {
            r = v;
            g = v;
            b = v;
            return;
        }

        region = h / 43;
        remainder = (h - (region * 43)) * 6;

        p = (v * (255 - s)) >> 8;
        q = (v * (255 - ((s * remainder) >> 8))) >> 8;
        t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

        switch (region) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            default:
                r = v;
                g = p;
                b = q;
                break;
        }
    }
}  // namespace Tracer::Components::Color