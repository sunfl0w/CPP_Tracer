#pragma once

#include <cmath>

#include "mat4.hpp"
#include "vec3.hpp"
#include "tris.hpp"

using namespace Tracer::Math;

namespace Tracer::Components::Position {
    class Transform {
    private:
        Mat4 transformMatrix;

    public:
        Transform(const Vec3& position);

        Vec3 GetPosition();

        void Translate(const Vec3& translation);

        void Rotate(float x, float y, float z);

        Vec3 TransformPosition(const Vec3& position);

        Tris TransformTris(const Tris& tris);
    };
}  // namespace Tracer::Components::Positioning