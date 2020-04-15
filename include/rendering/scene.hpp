#pragma once

#include <memory>
#include <vector>

#include "renderableObject.hpp"
#include "pointLight.hpp"
#include "camera.hpp"

namespace Tracer::Rendering {
    class Scene {
    private:
        std::vector<Objects::RenderableObject> renderableObjects;
        std::vector<Objects::PointLight*> pointLights;
        Objects::Camera camera;

    public:
        Scene(const std::vector<Objects::RenderableObject>& renderableObjects, const std::vector<Objects::PointLight*> pointLights, const Objects::Camera& camera);

        std::vector<Objects::RenderableObject>& GetRenderableObjects();

        std::vector<Objects::PointLight*> GetLightObjects();

        Objects::Camera& GetCamera();
    };
}  // namespace Tracer::Rendering