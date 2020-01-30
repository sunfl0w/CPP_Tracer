#pragma once

#include "rgb_Color.hpp"

namespace Tracer::Rendering {
    class HSV_Color {
    public:
        unsigned int h;
        unsigned int s;
        unsigned int v;

    public:
        HSV_Color();
        HSV_Color(unsigned int h, unsigned int s, unsigned int v);

        void FromRGB(unsigned int r, unsigned int g, unsigned int b);
    };
}