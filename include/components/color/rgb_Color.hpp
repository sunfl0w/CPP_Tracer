#pragma once

#include "hsv_Color.hpp"

namespace Tracer::Components::Color {
    class RGB_Color {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;

    public:
        RGB_Color();
        RGB_Color(unsigned int r, unsigned int g, unsigned int b);

        void FromHSV(unsigned int h, unsigned int s, unsigned int v);
    };
}  // namespace Tracer::Rendering