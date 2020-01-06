#include "viewport.hpp"

namespace OpenCG::Rendering {
    Viewport::Viewport() {}

    Viewport::Viewport(unsigned int width, unsigned int height, unsigned int minZ, unsigned int maxZ) {
        this->width = width;
        this->height = height;
        this->minZ = minZ;
        this->maxZ = maxZ;
    }

    Math::Vec3 Viewport::TransformPoint(const Math::Vec3& point) {
        return Math::Vec3((1.0f + point.X()) * width / 2.0f, (1.0f - point.Y()) * height / 2.0f, minZ + point.Z() * (maxZ - minZ));
    }
}