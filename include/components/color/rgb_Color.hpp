#pragma once

#include "hsv_Color.hpp"

namespace Tracer::Components::Color {
    class RGB_Color {
    public:
        float r;
        float g;
        float b;

    public:
        RGB_Color();
        RGB_Color(float r, float g, float b);
    };
}  // namespace Tracer::Rendering