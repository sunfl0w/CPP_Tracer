#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "intersectionData.hpp"
#include "scene.hpp"
#include "mesh.hpp"
#include "ray.hpp"
#include "screenBuffer.hpp"
#include "tris.hpp"
#include "rgb_Color.hpp"
#include "hsv_Color.hpp"
#include "camera.hpp"
#include "pointLight.hpp"
#include "transform.hpp"

namespace Tracer::Rendering {
    class Raytracer {
    public:
        Raytracer();

        ScreenBuffer RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const;

        IntersectionData RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, Math::Vec3& origin, Math::Vec3& dir) const;

        IntersectionData RayCastTris(Math::Tris& triangle, Math::Vec3& origin, Math::Vec3& dir) const;

        RGB_Color Raytrace(Scene& scene, Math::Vec3& origin, Math::Vec3& dir, int depth) const;
    };
}  // namespace Tracer::Rendering