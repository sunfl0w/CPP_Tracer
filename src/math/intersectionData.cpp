#include "intersectionData.hpp"

namespace Tracer::Math {
    IntersectionData::IntersectionData() {
        hit = false;
    }

    IntersectionData::IntersectionData(const Vec3& intersectionPos, bool hit) {
        this->intersectionPos = intersectionPos;
        this->hit = hit;
    }

    const Vec3& IntersectionData::GetIntersectionPos() {
        return intersectionPos;
    }

    bool IntersectionData::IsHit() const {
        return hit;
    }
}  // namespace Tracer::Math