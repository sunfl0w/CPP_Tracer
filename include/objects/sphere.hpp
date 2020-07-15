#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

#include "renderableObject.hpp"

namespace Tracer::Objects {
    class Sphere : public RenderableObject {
        float radius;

    public:
        Sphere(const glm::vec3& position, const Components::Material& material, float radius);

        float GetRadius();

        virtual Tracer::Math::IntersectionData Intersect(glm::vec3& origin, glm::vec3& dir);
    };
}