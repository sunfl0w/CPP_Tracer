#include "tris.hpp"

namespace OpenCG::Rendering {
    Tris::Tris() {}

    Tris::Tris(Vertex v1, Vertex v2, Vertex v3) : vertecies(std::array<Vertex, 3>{v1, v2, v3}) {
    }

    Vertex Tris::V1() {
        return vertecies[0];
    }

    Vertex Tris::V2() {
        return vertecies[1];
    }

    Vertex Tris::V3() {
        return vertecies[2];
    }

    void Tris::Set(int index, Vertex vertex) {
        vertecies[index] = vertex;
    }
}  // namespace OpenCG::Renderer