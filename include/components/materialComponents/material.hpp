#pragma once

#include "component.hpp"
#include "materialType.hpp"
#include "color.hpp"

using namespace Tracer::Components::ColorComponents;

namespace Tracer::Components::MaterialComponents {
    class Material : public Component {
    private:
        MaterialType type;
        Color color;

    public:
        Material(MaterialType type, Color color);

        MaterialType GetType();

        Color& GetColor();

        void SetType(MaterialType materialType);

        void SetColor(Color color);
    };
}  // namespace Tracer::Components::Material