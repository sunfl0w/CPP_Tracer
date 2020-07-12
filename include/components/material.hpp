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

        const glm::vec3& GetColor() const;

        float GetReflectivity() const;

        float GetTransparency() const;
    };
}  // namespace Tracer::Components::Material