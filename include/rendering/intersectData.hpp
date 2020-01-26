#pragma once

#include "vec3.hpp"
#include "RGB_Color.hpp"

namespace OpenCG::Rendering {
    struct IntersectData {
        Math::Vec3 intersectPos;
        RGB_Color color;
        bool hit;

        IntersectData() {
            hit = false;
        }

        IntersectData(Math::Vec3 intersectPos, RGB_Color color, bool hit) {
            this->intersectPos = intersectPos;
            this->color = color;
            this->hit = hit;
        }
    };
}