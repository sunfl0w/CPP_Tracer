#pragma once

#include "vec3.hpp"
#include "RGB_Color.hpp"

namespace OpenCG::Rendering {
    struct IntersectData {
        Math::Vec3 intersectPos;
        RGB_Color color;

        IntersectData() {}

        IntersectData(Math::Vec3 intersectPos, RGB_Color color) {
            this->intersectPos = intersectPos;
            this->color = color;
        }
    };
}