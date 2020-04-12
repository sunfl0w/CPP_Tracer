#include "camera.hpp"

namespace Tracer::Objects {
    Camera::Camera(const Math::Vec3& position, const Math::Vec3& angles) : transform(position) {
        transform.Rotate(angles.GetX(), angles.GetY(), angles.GetZ());
    }

    Components::Position::Transform& Camera::GetTransform() {
        return transform;
    }
}