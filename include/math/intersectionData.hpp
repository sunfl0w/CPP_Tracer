#pragma once

#include "vec3.hpp"

namespace Tracer::Math {
    class IntersectionData {
    private:
        Vec3 intersectionPos;
        bool hit;

    public:
        IntersectionData();

        IntersectionData(const Vec3& intersectionPos, bool hit);

        const Vec3& GetIntersectionPos();

        bool IsHit() const;
    };
}  // namespace Tracer::Math