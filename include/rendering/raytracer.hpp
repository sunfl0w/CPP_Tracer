#pragma once

#include <vector>

#include "screenBuffer.hpp"
#include "tris.hpp"
#include "ray.hpp"
#include "intersectData.hpp"

namespace OpenCG::Rendering {
    class Raytracer {
    public:
        Raytracer();
        ScreenBuffer RenderToBuffer(std::vector<Tris> triangles, int imageWidth, int imageHeight);
    };
}