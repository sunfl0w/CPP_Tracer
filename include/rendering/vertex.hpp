#pragma once

#include <vector>

#include "vec3.hpp"
#include "matrix.hpp"

namespace OpenCG::Rendering {
    class Vertex {
    private:
        OpenCG::Math::Vec3 point;

    public:
        Vertex();
        Vertex(float x, float y, float z);
        float X();
        float Y();
        float Z();
        void Set(int index, float value);
        OpenCG::Math::Matrix ToMatrix();
    };
}  // namespace OpenCG::Renderer
