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
        HSV_Color GetHSV();

        void Set(RGB_Color color);
        void Set(HSV_Color color);
    };
}  // namespace Tracer::Components::Color