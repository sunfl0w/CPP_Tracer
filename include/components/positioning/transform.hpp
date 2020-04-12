#pragma once

#include <cmath>

#include "component.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

using namespace Tracer::Math;

namespace Tracer::Components::Positioning {
    class Transform : public Component {
    private:
        Mat4 transformMatrix;

    public:
        Transform(const Vec3& position);

        Vec3 GetPosition();

        void Translate(const Vec3& translation);

        void Rotate(float x, float y, float z);
    };
}  // namespace Tracer::Components::Positioning