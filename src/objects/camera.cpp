#include "camera.hpp"

namespace Tracer::Objects {
    Camera::Camera(glm::vec3 position, glm::vec3 rotation) {
        transform = Components::Position::Transform(position, rotation, glm::vec3(1.0f, 1.0f, 1.0f));
    }

    Components::Position::Transform& Camera::GetTransform() {
        return transform;
    }
}