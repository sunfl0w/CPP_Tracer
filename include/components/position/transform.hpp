#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tris.hpp"

using namespace Tracer::Math;

namespace Tracer::Components::Position {
    class Transform {
    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 modelMatrix;

    public:
        Transform();

        Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale);

        glm::mat4& GetTransformMatrix();

        const glm::vec3& GetPosition();

        void SetPosition(const glm::vec3& position);

        void Translate(const glm::vec3& translation);

        const glm::vec3& GetRotation();

        void SetRotation(const glm::vec3& rotation);

        void Rotate(const glm::vec3& rotation);

        void SetScale(const glm::vec3& scale);

        void RotateAroundOrigin(const glm::vec3& axis, float angle);

    private:
        void UpdateModelMatrix();
    };
}  // namespace Tracer::Components::Positioning