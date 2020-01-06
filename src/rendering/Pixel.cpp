#include "Pixel.hpp"

namespace OpenCG::Rendering {
    Pixel::Pixel() {
        color = RGB_Color(255, 192, 203);
    }

    Pixel::Pixel(RGB_Color color) {
        this->color = color;
    }

    RGB_Color Pixel::GetColor() {
        return color;
    }
}