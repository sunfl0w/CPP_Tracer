#pragma once

#include <vector>

#include "tris.hpp"
#include "ray.hpp"

namespace Tracer::Components {
    class BoundingBox {
    private:
        float minX, maxX, minY, maxY, minZ, maxZ;

    public:
        BoundingBox();

        BoundingBox(const std::vector<Math::Tris>& meshData);

        bool RayIntersects(const Math::Ray& ray) const;
    };
}  // namespace Tracer::Components