#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Tracer::Components {
    class Material {
    private:
        glm::vec3 color;
        float reflectiveness;
        float transparency;

    public:
        Material();
        
        Material(const glm::vec3& color, float reflectivity, float transparency);

        glm::vec3& GetColor();

        float GetReflectivity();

        float GetTransparency();
    };
}  // namespace Tracer::Components::Material