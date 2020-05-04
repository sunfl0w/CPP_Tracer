#pragma once

#include "vec3.hpp"
#include "transform.hpp"
#include "color.hpp"

namespace Tracer::Objects {
    class PointLight {
    private:
        Components::Position::Transform transform;
        float intensity;
        Components::Color::Color color;

    public:
        PointLight(const Math::Vec3& position, float intensity, const Components::Color::Color& color);

        Components::Position::Transform& GetTransform();

        float GetIntensity();

        Components::Color::Color& GetColor();
    };
}