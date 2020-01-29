#pragma once

#include <vector>

#include "screenBuffer.hpp"
#include "tris.hpp"
#include "ray.hpp"
#include "intersectData.hpp"
#include "mesh.hpp"

namespace OpenCG::Rendering {
    class Raytracer {
    public:
        Raytracer();
        ScreenBuffer RenderToBuffer(std::vector<Components::Mesh> meshes, int imageWidth, int imageHeight, Math::Vec3 camPos);
    };
}