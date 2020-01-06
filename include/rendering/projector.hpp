#pragma once

#include "matrix.hpp"

namespace OpenCG::Rendering {
    class Projector {
    private:
        Math::Matrix projection;
    public:
        Projector();
        Projector(int width, int height, int near, int far);
        Math::Matrix GetMatrix();
    };
}  // namespace OpenCG::Renderer