#include "pointLight.hpp"

namespace Tracer::Objects {
    PointLight::PointLight(const Math::Vec3& position, float intensity, const Components::Color::Color& color) : transform(position), color(0, 0, 0) {
        this->intensity = intensity;
        this->color = color;
    }

    Components::Position::Transform& PointLight::GetTransform() {
        return transform;
    }

    float PointLight::GetIntensity() {
        return intensity;
    }

    Components::Color::Color& PointLight::GetColor() {
        return color;
    }   
}