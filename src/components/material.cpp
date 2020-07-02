#include "material.hpp"

namespace Tracer::Components {
    Material::Material() {}
    
    Material::Material(const glm::vec3& color, float reflectivity, float transparency) {
        this->color = color;
        this->reflectiveness = reflectivity;
        this->transparency = transparency;
    }

        glm::vec3& Material::GetColor() {
            return color;
        }

        float Material::GetReflectivity() {
            return reflectiveness;
        }

        float Material::GetTransparency() {
            return transparency;
        }
}  // namespace Tracer::Components::MaterialComponents