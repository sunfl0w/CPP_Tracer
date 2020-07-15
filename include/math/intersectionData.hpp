#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material.hpp"

namespace Tracer::Math {
    class IntersectionData {
    private:
        glm::vec3 intersectionNorm;
        glm::vec3 intersectionPos;
        Tracer::Components::Material material;
        bool hit;

    public:
        IntersectionData();

        IntersectionData(const glm::vec3& intersectionNorm, const glm::vec3& intersectionPos, const Tracer::Components::Material& material, bool hit);

        const glm::vec3& GetIntersectionNormal() const;

        const glm::vec3& GetIntersectionPos() const;

        const Tracer::Components::Material& GetMaterial() const;

        bool IsHit() const;
    };
}  // namespace Tracer::Math