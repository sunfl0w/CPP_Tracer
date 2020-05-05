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

        ScreenBuffer RenderMeshesToBuffer(std::vector<Objects::RenderableObject>& renderableObjects, int imageWidth, int imageHeight, Objects::Camera& camera, std::vector<Objects::PointLight*> pointLights) const;
    };
}  // namespace Tracer::Rendering