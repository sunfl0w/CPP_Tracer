#include "color.hpp"

namespace Tracer::Components::Color {
    Color::Color(int r, int g, int b) {
        rgbColor = RGB_Color(r, g, b);
    }

    RGB_Color Color::GetRGB() {
        return rgbColor;
    }

    HSV_Color Color::GetHSV() {
        return HSV_Color(rgbColor);
    }

    void Color::Set(RGB_Color color) {
        rgbColor = color;
    }

    void Color::Set(HSV_Color color) {
        rgbColor = RGB_Color(color);
    }
}  // namespace Tracer::Components::Color