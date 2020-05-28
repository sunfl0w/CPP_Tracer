#include "transform.hpp"

namespace Tracer::Components::Position {
    Transform::Transform() {}
    
    Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::vec3& Transform::GetPosition() {
        return position;
    }

    void Transform::SetPosition(const glm::vec3& position) {
        this->position = position;
    }

    void Transform::Translate(const glm::vec3& translation) {
        position = position + translation;
    }

    glm::vec3& Transform::GetRotation() {
        return rotation;
    }

    void Transform::SetRotation(const glm::vec3& rotation) {
        this->rotation = rotation;
    }

    void Transform::Rotate(const glm::vec3& rotation) {
        this->rotation = this->rotation + rotation;
    }

    void Transform::SetScale(const glm::vec3& scale) {
        this->scale = scale;
    }
}  // namespace Tracer::Components::Positioning