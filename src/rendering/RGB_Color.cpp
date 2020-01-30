#include "RGB_Color.hpp"

namespace Tracer::Rendering {
    RGB_Color::RGB_Color() {}
    
    RGB_Color::RGB_Color(unsigned int r, unsigned int g, unsigned int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    int RGB_Color::Red() {
        return r;
    }

    int RGB_Color::Green() {
        return g;
    }

    int RGB_Color::Blue() {
        return b;
    }
}