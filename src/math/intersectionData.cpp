#include "intersectionData.hpp"

namespace Tracer::Math {
    IntersectionData::IntersectionData() {
        hit = false;
    }

    IntersectionData::IntersectionData(const Tris& intersectionTriangle, const glm::vec3& intersectionPos, bool hit) {
        this->intersectionTriangle = intersectionTriangle;
        this->intersectionPos = intersectionPos;
        this->hit = hit;
    }

    IntersectionData::IntersectionData(const Tris& intersectionTriangle, const glm::vec3& intersectionPos, const Tracer::Components::Material& material, bool hit) {
        this->intersectionTriangle = intersectionTriangle;
        this->intersectionPos = intersectionPos;
        this->material = material;
        this->hit = hit;
    }

    Tris& IntersectionData::GetIntersectionTriangle() {
        return intersectionTriangle;
    }

    glm::vec3& IntersectionData::GetIntersectionPos() {
        return intersectionPos;
    }

    Tracer::Components::Material& IntersectionData::GetMaterial() {
        return material;
    }

    void IntersectionData::SetMaterial(const Tracer::Components::Material& material) {
        this->material = material;
    }

    bool IntersectionData::IsHit() const {
        return hit;
    }
}  // namespace Tracer::Math