#include "intersectionData.hpp"

namespace Tracer::Math {
    IntersectionData::IntersectionData() {
        hit = false;
    }

    IntersectionData::IntersectionData(const glm::vec3& intersectionPos, const Tris& intersectionTriangle, bool hit) {
        this->intersectionTriangle = intersectionTriangle;
        this->intersectionPos = intersectionPos;
        this->hit = hit;
    }

    Tris& IntersectionData::GetIntersectionTriangle() {
        return intersectionTriangle;
    }

    glm::vec3& IntersectionData::GetIntersectionPos() {
        return intersectionPos;
    }

    bool IntersectionData::IsHit() const {
        return hit;
    }
}  // namespace Tracer::Math