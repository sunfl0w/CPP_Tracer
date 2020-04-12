#include "color.hpp"

namespace Tracer::Components::Color {
    Color::Color(int r, int g, int b) {
        rgbColor = RGB_Color(r, g, b);
    }

    RGB_Color Color::GetRGB() {
        return rgbColor;
    }

    HSV_Color Color::GetHSV() {
        HSV_Color hsvColor;
        hsvColor.FromRGB(rgbColor.r, rgbColor.g, rgbColor.b);
        return hsvColor;
    }

    void Color::Set(RGB_Color color) {
        rgbColor = color;
    }

    void Color::Set(HSV_Color color) {
        rgbColor.FromHSV(color.h, color.s, color.v);
    }
}  // namespace Tracer::Components::Color