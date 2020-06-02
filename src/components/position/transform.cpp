#include "transform.hpp"

namespace Tracer::Components::Position {
    Transform::Transform() {}
    
    Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::vec3 Transform::TranformPosition(glm::vec3 pos) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        //Translate mid of sprite to origin for rotation
        model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z));
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, -0.5f * scale.z));

        model = glm::scale(model, scale);

        glm::vec3 transformedPos = model * glm::vec4(pos, 1.0f);
        return transformedPos;
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