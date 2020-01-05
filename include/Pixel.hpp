#pragma once

#include <vector>

#include "RGB_Color.hpp"

namespace OpenCG {
    class Pixel {
    private:
        RGB_Color color;

    public:
        Pixel();
        Pixel(RGB_Color color);
        RGB_Color GetColor();
    };
}  // namespace OpenCG