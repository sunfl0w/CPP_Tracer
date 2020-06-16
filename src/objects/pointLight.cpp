#include "pointLight.hpp"

namespace Tracer::Objects {
    PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->color = color;
        this->intensity = intensity;
    }

    Components::Position::Transform& PointLight::GetTransform() {
        return transform;
    }

    glm::vec3& PointLight::GetColor() {
        return color;
    }

    float PointLight::GetIntensity() {
        return intensity;
    }
}