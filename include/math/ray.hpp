#pragma once

#include <vector>
#include <iostream>

#include "tris.hpp"
#include "vec3.hpp"
#include "intersectionData.hpp"

namespace Tracer::Math {
    class Ray {
    private:
        Vec3 origin;
        Vec3 direction;
        int length;

    public:
        Ray(const Vec3& origin, const Math::Vec3& direction, int length);

        const Vec3& GetOrigin() const;

        const Vec3& GetDirection() const;

        int GetLength() const;

        IntersectionData Cast(const Tris& triangle);
    };
}  // namespace OpenCG::Rendering