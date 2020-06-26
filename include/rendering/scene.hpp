#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderableObject.hpp"
#include "pointLight.hpp"
#include "camera.hpp"

namespace Tracer::Rendering {
    class Scene {
    private:
        std::vector<std::unique_ptr<Objects::RenderableObject>> renderableObjects;
        std::vector<Objects::PointLight*> pointLights;
        Objects::Camera camera;

    public:
        Scene(std::vector<std::unique_ptr<Objects::RenderableObject>> renderableObjects, std::vector<Objects::PointLight*> pointLights, Objects::Camera& camera);

        std::vector<std::unique_ptr<Objects::RenderableObject>> GetRenderableObjects();

        std::vector<Objects::PointLight*> GetLightObjects();

        Objects::Camera& GetCamera();
    };
}  // namespace Tracer::Rendering