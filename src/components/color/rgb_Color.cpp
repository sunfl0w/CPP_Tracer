#include "rgb_Color.hpp"

namespace Tracer::Components::ColorComponents {
    RGB_Color::RGB_Color() : Component("RGB_ColorComponent") {}

    RGB_Color::RGB_Color(unsigned int r, unsigned int g, unsigned int b) : Component("RGB_ColorComponent") {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    RGB_Color::RGB_Color(const HSV_Color& hsvColor) : Component("RGB_ColorComponent") {
        unsigned char region, remainder, p, q, t;

        if (hsvColor.s == 0) {
            r = hsvColor.v;
            g = hsvColor.v;
            b = hsvColor.v;
            return;
        }

        region = hsvColor.h / 43;
        remainder = (hsvColor.h - (region * 43)) * 6;

        p = (hsvColor.v * (255 - hsvColor.s)) >> 8;
        q = (hsvColor.v * (255 - ((hsvColor.s * remainder) >> 8))) >> 8;
        t = (hsvColor.v * (255 - ((hsvColor.s * (255 - remainder)) >> 8))) >> 8;

        switch (region) {
            case 0:
                r = hsvColor.v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = hsvColor.v;
                b = p;
                break;
            case 2:
                r = p;
                g = hsvColor.v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = hsvColor.v;
                break;
            case 4:
                r = t;
                g = p;
                b = hsvColor.v;
                break;
            default:
                r = hsvColor.v;
                g = p;
                b = q;
                break;
        }
    }
}  // namespace Tracer::Components::Color