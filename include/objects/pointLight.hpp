#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rgb_Color.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class PointLight {
    private:
        Components::Position::Transform transform;
        float intensity;
        Components::Color::RGB_Color color;

    public:
        PointLight(glm::vec3 position, float intensity, Components::Color::RGB_Color color);

        Components::Position::Transform& GetTransform();

        float GetIntensity();

        Components::Color::RGB_Color& GetColor();
    };
}