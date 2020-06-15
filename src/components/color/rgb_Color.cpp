#include "rgb_Color.hpp"

namespace Tracer::Components::Color {
    RGB_Color::RGB_Color() {}

    RGB_Color::RGB_Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
}  // namespace Tracer::Components::Color