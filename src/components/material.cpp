#include "material.hpp"

namespace Tracer::Components {
    Material::Material() {}
    
    Material::Material(const glm::vec3& color, float reflectivity, float transparency) {
        this->color = color;
        this->reflectiveness = reflectivity;
        this->transparency = transparency;
    }

        const glm::vec3& Material::GetColor() const {
            return color;
        }

        float Material::GetReflectivity() const {
            return reflectiveness;
        }

        float Material::GetTransparency() const {
            return transparency;
        }
}  // namespace Tracer::Components::MaterialComponents