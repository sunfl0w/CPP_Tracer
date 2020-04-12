#include "material.hpp"

namespace Tracer::Components::Material {
    Material::Material(MaterialType type, Color::Color color) : color(color) {
        this->type = type;
    }

    MaterialType Material::GetType() {
        return type;
    }

    Color::Color& Material::GetColor() {
        return color;
    }

    void Material::SetType(MaterialType materialType) {
        type = materialType;
    }

    void Material::SetColor(Color::Color color) {
        this->color = color;
    }
}  // namespace Tracer::Components::MaterialComponents