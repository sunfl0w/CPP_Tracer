#include "pointLight.hpp"

namespace Tracer::Objects {
    PointLight::PointLight(glm::vec3 position, float intensity, Components::Color::RGB_Color color) {
        this->transform = Components::Position::Transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        this->intensity = intensity;
        this->color = color;
    }

    Components::Position::Transform& PointLight::GetTransform() {
        return transform;
    }

    float PointLight::GetIntensity() {
        return intensity;
    }

    Components::Color::RGB_Color& PointLight::GetColor() {
        return color;
    }   
}