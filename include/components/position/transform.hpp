#pragma once

#include <cmath>

#include "vec3.hpp"

using namespace Tracer::Math;

namespace Tracer::Components::Position {
    class Transform {
    private:
        Vec3 position;
        Vec3 rotation;

    public:
        Transform(const Vec3& position);

        Vec3 GetPosition();

        void Translate(const Vec3& translation);

        void Rotate(float x, float y, float z);
    };
}  // namespace Tracer::Components::Positioning