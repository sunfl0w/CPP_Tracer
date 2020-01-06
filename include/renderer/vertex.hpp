#pragma once

#include "vec3.hpp"

namespace OpenCG::Renderer {
    class Vertex {
    public:
        OpenCG::Math::Vec3 point;

        Vertex(float x, float y, float z);
    };
}  // namespace OpenCG::Renderer
