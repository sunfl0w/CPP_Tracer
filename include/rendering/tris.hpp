#pragma once

#include <array>

#include "vertex.hpp"

namespace OpenCG::Rendering {
    class Tris {
    private:
        std::array<Vertex, 3> vertecies;

    public:
        Tris();
        Tris(Vertex v1, Vertex v2, Vertex v3);
        Vertex V1();
        Vertex V2();
        Vertex V3();
        void Set(int index, Vertex vertex);
    };
}  // namespace OpenCG::Renderer