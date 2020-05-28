#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tris.hpp"

namespace Tracer::Math {
    class IntersectionData {
    private:
        Tris intersectionTriangle;
        glm::vec3 intersectionPos;
        bool hit;

    public:
        IntersectionData();

        IntersectionData(const glm::vec3& intersectionPos, const Tris& intersectionTriangle, bool hit);

        Tris& GetIntersectionTriangle();

        glm::vec3& GetIntersectionPos();

        bool IsHit() const;
    };
}  // namespace Tracer::Math