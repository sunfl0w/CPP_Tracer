#pragma once

namespace OpenCG {
    class RGB_Color {
    private:
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
}  // namespace OpenCG