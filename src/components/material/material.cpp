#include "material.hpp"

namespace Tracer::Components::Material {
    Material::Material(MaterialType type, Color::RGB_Color color) : color(color) {
        this->type = type;
    }

    MaterialType Material::GetType() {
        return type;
    }

    Color::RGB_Color& Material::GetColor() {
        return color;
    }

    void Material::SetType(MaterialType materialType) {
        type = materialType;
    }

    void Material::SetColor(Color::RGB_Color color) {
        this->color = color;
    }
}  // namespace Tracer::Components::MaterialComponents