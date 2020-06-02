#pragma once

#include "materialType.hpp"
#include "rgb_Color.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Components::Material {
    class Material {
    private:
        MaterialType type;
        Color::RGB_Color color;

    public:
        Material(MaterialType type, Color::RGB_Color color);

        MaterialType GetType();

        Color::RGB_Color& GetColor();

        void SetType(MaterialType materialType);

        void SetColor(Color::RGB_Color color);
    };
}  // namespace Tracer::Components::Material