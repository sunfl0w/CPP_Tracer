#pragma once

#include "component.hpp"
#include "vec3.hpp"
#include "mat4.hpp"

using namespace Tracer::Math;

namespace Tracer::Components::Positioning {
    class Transform : public Component {
    private:
        Mat4 transform;

    public:
        Transform(const Vec3& position);

        void Translate(const Vec3& translation);
    };
}  // namespace Tracer::Components::Positioning