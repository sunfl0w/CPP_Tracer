#pragma once

#include <vector>

#include "vec3.hpp"

namespace OpenCG::Rendering {
    class Vertex {
    public:
        OpenCG::Math::Vec3 data;

    public:
        Vertex();
        Vertex(float x, float y, float z);
        float X();
        float Y();
        float Z();
        void Set(int index, float value);
    };
}  // namespace OpenCG::Renderer
