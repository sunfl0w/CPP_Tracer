#pragma once

#include "matrix.hpp"
#include "vec3.hpp"

namespace OpenCG::Renderer {
    class Viewport {
    private:
        unsigned int width;
        unsigned int height;
        unsigned int minZ;
        unsigned int maxZ;

    public:
        Viewport(unsigned int width, unsigned int height, unsigned int minZ, unsigned int maxZ);

        Math::Vec3 TransformPoint(const Math::Vec3& point);
    };
}  // namespace OpenCG::Renderer