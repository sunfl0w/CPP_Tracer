#pragma once

#include <cmath>

#include "matrix.hpp"

namespace OpenCG::Rendering {
    class Projector {
    private:
        Math::Matrix projection;
    public:
        Projector();
        Projector(int fov, int near, int far);
        Math::Matrix GetMatrix();
    };
}  // namespace OpenCG::Renderer