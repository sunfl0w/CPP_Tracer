#pragma once

#include <vector>

#include "RGB_Color.hpp"

namespace OpenCG {
    class Pixel {
    private:
        char character;
        RGB_Color characterColor;

    public:
        Pixel();
        Pixel(char character, RGB_Color characterColor);
        char GetCharacter();
        RGB_Color GetColor();
    };
}  // namespace OpenCG