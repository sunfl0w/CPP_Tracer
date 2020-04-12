#pragma once

#include "vec3.hpp"
#include "transform.hpp"

namespace Tracer::Objects {
    class Camera {
    private:
        Components::Position::Transform transform;

    public:
        Camera(const Math::Vec3& position, const Math::Vec3& angles);

        Components::Position::Transform& GetTransform();
    };
}  // namespace Tracer::Objects