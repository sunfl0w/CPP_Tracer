#include "pointLight.hpp"

namespace Tracer::Objects {
    PointLight::PointLight(const Math::Vec3& position, float intensity) : transform(position) {
        this->intensity = intensity;
    }

    Components::Position::Transform& PointLight::GetTransform() {
        return transform;
    }

    float PointLight::GetIntensity() {
        return intensity;
    }
}