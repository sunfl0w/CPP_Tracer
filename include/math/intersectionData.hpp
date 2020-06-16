#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tris.hpp"
#include "material.hpp"

namespace Tracer::Math {
    class IntersectionData {
    private:
        Tris intersectionTriangle;
        glm::vec3 intersectionPos;
        Tracer::Components::Material material;
        bool hit;

    public:
        IntersectionData();

        IntersectionData(const Tris& intersectionTriangle, const glm::vec3& intersectionPos, bool hit);

        IntersectionData(const Tris& intersectionTriangle, const glm::vec3& intersectionPos, const Tracer::Components::Material& material, bool hit);

        Tris& GetIntersectionTriangle();

        glm::vec3& GetIntersectionPos();

        Tracer::Components::Material& GetMaterial();

        void SetMaterial(const Tracer::Components::Material& material);

        bool IsHit() const;
    };
}  // namespace Tracer::Math