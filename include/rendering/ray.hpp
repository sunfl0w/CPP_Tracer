#pragma once

#include <vector>

#include "tris.hpp"
#include "vec3.hpp"
#include "intersectData.hpp"

namespace OpenCG::Rendering {
    class Ray {
    public:
        Math::Vec3 origin;
        Math::Vec3 direction;
        int length;

        Ray(Math::Vec3 origin, Math::Vec3 direction, int length);

        IntersectData Cast(Tris triangle);
    };
}  // namespace OpenCG::Rendering