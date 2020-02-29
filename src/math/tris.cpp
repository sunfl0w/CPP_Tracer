#include "tris.hpp"

namespace Tracer::Math {
    Tris::Tris() {}

    Tris::Tris(const Vec3& v0, const Vec3& v1, const Vec3& v2) : vertecies(std::array<Vec3, 3>{Vec3(v0), Vec3(v1), Vec3(v2)}) {
    }

    const Vec3& Tris::GetV0() const {
        return vertecies[0];
    }

    const Vec3& Tris::GetV1() const {
        return vertecies[1];
    }

    const Vec3& Tris::GetV2() const {
        return vertecies[2];
    }

    const std::array<Vec3, 3>& Tris::GetVertecies() const {
        return vertecies;
    }

    void Tris::Set(int index, const Vec3& vertex) {
        vertecies[index] = vertex;
    }

    const Vec3 Tris::GetNormal() {
        return (vertecies[1].Subtract(vertecies[0])).Cross((vertecies[2].Subtract(vertecies[0])));
    }
}  // namespace OpenCG::Renderer