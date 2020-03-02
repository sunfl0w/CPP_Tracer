#include "material.hpp"

namespace Tracer::Components::MaterialComponents {
    Material::Material(MaterialType type, Color color) : color(0, 0, 0) {
        this->type = type;
        this->color = color;
    }

    MaterialType Material::GetType() {
        return type;
    }

    Color& Material::GetColor() {
        return color;
    }

    void Material::SetType(MaterialType materialType) {
        type = materialType;
    }

    void Material::SetColor(Color color) {
        this->color = color;
    }
}  // namespace Tracer::Components::MaterialComponents