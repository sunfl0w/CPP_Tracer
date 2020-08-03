#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "intersectionData.hpp"
#include "material.hpp"
#include "position/transform.hpp"

namespace Tracer::Objects {
    class RenderableObject {
    protected:
        Components::Position::Transform transform;
        Components::Material material;

    public:
        RenderableObject(const glm::vec3& position, const Components::Material& material);

        virtual ~RenderableObject();

        Components::Position::Transform& GetTransform();

        Components::Material& GetMaterial();

        virtual Tracer::Math::IntersectionData Intersect(glm::vec3& origin, glm::vec3& dir) = 0;
    };
}  // namespace Tracer::Objects