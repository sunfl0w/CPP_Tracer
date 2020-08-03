#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "position/transform.hpp"

namespace Tracer::Objects {
    class PointLight {
    private:
        Tracer::Components::Position::Transform transform;
        glm::vec3 color;
        float intensity;

    public:
        PointLight(const glm::vec3& position, const glm::vec3& color, float intensity);

        Tracer::Components::Position::Transform& GetTransform();

        glm::vec3& GetColor();

        float GetIntensity();
    };
}