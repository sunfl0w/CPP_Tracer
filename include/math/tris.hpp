#pragma once

#include <array>

#include "vec3.hpp"

namespace Tracer::Math {
    class Tris {
    private:
        std::array<Vec3, 3> vertecies;

    public:
        Tris();

        Tris(const Vec3& v0, const Vec3& v1, const Vec3& v2);

        const Vec3& GetV0() const;

        const Vec3& GetV1() const;

        const Vec3& GetV2() const;

        const std::array<Vec3, 3>& GetVertecies() const;

        void Set(int index, const Vec3& vertex);
    };
}  // namespace OpenCG::Renderer