#include "intersectionData.hpp"

namespace Tracer::Math {
    IntersectionData::IntersectionData() {
        hit = false;
    }

    IntersectionData::IntersectionData(const glm::vec3& intersectionNorm, const glm::vec3& intersectionPos, const Tracer::Components::Material& material, bool hit) {
        this->intersectionNorm = intersectionNorm;
        this->intersectionPos = intersectionPos;
        this->material = material;
        this->hit = hit;
    }

    const glm::vec3& IntersectionData::GetIntersectionNormal() const {
        return intersectionNorm;
    }

    const glm::vec3& IntersectionData::GetIntersectionPos() const {
        return intersectionPos;
    }

    const Tracer::Components::Material& IntersectionData::GetMaterial() const {
        return material;
    }

    bool IntersectionData::IsHit() const {
        return hit;
    }
}  // namespace Tracer::Math