#pragma once

#include "hsv_Color.hpp"
#include "rgb_Color.hpp"

namespace Tracer::Components::Color {
    class Color {
    private:
        RGB_Color rgbColor;

    public:
        Color(int r, int g, int b);

        RGB_Color GetRGB();
    };
}  // namespace Tracer::Components::Color