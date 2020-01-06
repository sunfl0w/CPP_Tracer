#pragma once

#include "matrix.hpp"
#include "vec3.hpp"

namespace OpenCG::Rendering {
    class Camera {
    private:
        Math::Matrix viewMatrix;
    public:
        Camera(const Math::Vec3& camPos, const Math::Vec3& target, const Math::Vec3& up);
        Math::Matrix GetMatrix();
    };
}  // namespace OpenCG::Renderer