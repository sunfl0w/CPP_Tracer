#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class SphereObject {
        Components::Position::Transform transform;
        Components::Material material;
        float radius;

    public:
        SphereObject(const glm::vec3& position, const Components::Material& material, float radius);

        Components::Position::Transform& GetTransform();

        Components::Material& GetMaterial();

        const glm::vec3& GetCenter();

        float GetRadius();
    };
}