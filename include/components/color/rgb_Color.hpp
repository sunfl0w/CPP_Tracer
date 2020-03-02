#pragma once

#include "hsv_Color.hpp"
#include "component.hpp"

namespace Tracer::Components::Color {
    class RGB_Color : public Component {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;

    public:
        RGB_Color();
        RGB_Color(unsigned int r, unsigned int g, unsigned int b);
        RGB_Color(const HSV_Color& hsvColor);
    };
}  // namespace Tracer::Rendering