#pragma once

#include <vector>
#include <memory>

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
        ScreenBuffer RenderSceneToBuffer(const Scene& scene) const;
        ScreenBuffer RenderMeshesToBuffer(std::vector<Components::Mesh>& meshes, int imageWidth, int imageHeight, Objects::Camera* camera, Objects::PointLight* pointLight) const;
    };
}  // namespace Tracer::Rendering