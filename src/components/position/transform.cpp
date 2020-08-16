#include "position/transform.hpp"

namespace Tracer::Components::Position {
    Transform::Transform() {}
    
    Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        UpdateModelMatrix();
    }

    glm::mat4& Transform::GetTransformMatrix() {
        return modelMatrix;
    }

    const glm::vec3& Transform::GetPosition() const {
        return position;
    }

    void Transform::SetPosition(const glm::vec3& position) {
        this->position = position;
        UpdateModelMatrix();
    }

    void Transform::Translate(const glm::vec3& translation) {
        position = position + translation;
        UpdateModelMatrix();
    }

    const glm::vec3& Transform::GetRotation() {
        return rotation;
    }

    void Transform::SetRotation(const glm::vec3& rotation) {
        this->rotation = rotation;
        UpdateModelMatrix();
    }

    void Transform::Rotate(const glm::vec3& rotation) {
        this->rotation = this->rotation + rotation;
        UpdateModelMatrix();
    }

    void Transform::SetScale(const glm::vec3& scale) {
        this->scale = scale;
        UpdateModelMatrix();
    }

    void Transform::UpdateModelMatrix() {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, -0.5f * scale.z));
    }

    void Transform::RotateAroundOrigin(const glm::vec3& axis, float angle) {
        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), axis);
        modelMatrix = rotationMatrix * modelMatrix;
    }
}  // namespace Tracer::Components::Positioning