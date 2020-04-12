#pragma once

#include "vec3.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class PointLight {
    private:
        Components::Position::Transform transform;
        float intensity;

    public:
        PointLight(const Math::Vec3& position, float intensity);

        Components::Position::Transform& GetTransform();

        float GetIntensity();
    };
}