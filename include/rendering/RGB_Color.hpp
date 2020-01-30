#pragma once

namespace Tracer::Rendering {
    class RGB_Color {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;

    public:
        RGB_Color();
        RGB_Color(unsigned int r, unsigned int g, unsigned int b);

        int Red();
        int Green();
        int Blue();
    };
}  // namespace Tracer::Rendering