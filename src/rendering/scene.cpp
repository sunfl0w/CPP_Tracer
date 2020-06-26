#include "scene.hpp"

namespace Tracer::Rendering {
    Scene::Scene(std::vector<std::unique_ptr<Objects::RenderableObject>> renderableObjects, std::vector<Objects::PointLight*> pointLights, Objects::Camera& camera) {
        this->renderableObjects = renderableObjects;
        this->pointLights = pointLights;
        this->camera = camera;
    }

    std::vector<std::unique_ptr<Objects::RenderableObject>> Scene::GetRenderableObjects() {
        return renderableObjects;
    }

    std::vector<Objects::PointLight*> Scene::GetLightObjects() {
        return pointLights;
    }

    Objects::Camera& Scene::GetCamera() {
        return camera;
    }
}  // namespace Tracer::Rendering