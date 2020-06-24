#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transform.hpp"

namespace Tracer::Objects {
    class Camera {
    private:
        Components::Position::Transform transform;

    public:
        Camera();
        
        Camera(glm::vec3 position, glm::vec3 rotation);

        Components::Position::Transform& GetTransform();
    };
}  // namespace Tracer::Objects