#pragma once

#include "vec3.hpp"
#include "tris.hpp"

namespace Tracer::Math {
    class IntersectionData {
    private:
        Tris intersectionTriangle;
        Vec3 intersectionPos;
        bool hit;

    public:
        IntersectionData();

        IntersectionData(const Vec3& intersectionPos, const Tris& intersectionTriangle, bool hit);

        Tris& GetIntersectionTriangle();

        Vec3& GetIntersectionPos();

        bool IsHit() const;
    };
}  // namespace Tracer::Math