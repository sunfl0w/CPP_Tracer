#include "color.hpp"

namespace Tracer::Components::Color {
    Color::Color(int r, int g, int b) {
        rgbColor = RGB_Color(r, g, b);
    }

    RGB_Color Color::GetRGB() {
        return rgbColor;
    }
}  // namespace Tracer::Components::Color