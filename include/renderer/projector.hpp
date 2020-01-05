#pragma once

#include "matrix.hpp"

namespace OpenCG::Renderer {
    class Projector {
    private:
        Math::Matrix projection;
    public:
        Projector(int width, int height, int near, int far);
        Math::Matrix GetMatrix();
    };
}  // namespace OpenCG::Renderer