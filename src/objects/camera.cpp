#include "camera.hpp"

namespace Tracer::Objects {
    Camera::Camera() : Object("Camera") {}
    
    Camera::Camera(Math::Vec3 position, Math::Vec3 direction) : Object("Camera") {
        Components::Positioning::Transform transform(position);
        transform.Rotate(direction.GetX(), direction.GetY(), direction.GetZ());
        AddComponent(transform);
    }
}