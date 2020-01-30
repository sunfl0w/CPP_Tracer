#pragma once

#include <vector>

#include "intersectionData.hpp"
#include "mesh.hpp"
#include "ray.hpp"
#include "screenBuffer.hpp"
#include "tris.hpp"

namespace Tracer::Rendering {
    class Raytracer {
    public:
        Raytracer();
        ScreenBuffer RenderToBuffer(std::vector<Components::Mesh>& meshes, int imageWidth, int imageHeight, const Math::Vec3& camPos, const Math::Vec3& lightPos);
    };
}  // namespace Tracer::Rendering