#pragma once

#include "materialType.hpp"
#include "color.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Components::Material {
    class Material {
    private:
        MaterialType type;
        Color::Color color;

    public:
        Material(MaterialType type, Color::Color color);

        MaterialType GetType();

        Color::Color& GetColor();

        void SetType(MaterialType materialType);

        void SetColor(Color::Color color);
    };
}  // namespace Tracer::Components::Material