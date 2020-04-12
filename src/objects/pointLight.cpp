#include "pointLight.hpp"

namespace Tracer::Objects {
    PointLight::PointLight() : Object("PointLight") {}

    PointLight::PointLight(Math::Vec3 position, float intensity) : Object("PointLight") {
        Components::Positioning::Transform transform(position);
        AddComponent(transform);
        this->intensity = intensity;
    }
}