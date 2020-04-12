#include "scene.hpp"

namespace Tracer::Rendering {
    Scene::Scene(const std::vector<Objects::RenderableObject>& renderableObjects, const std::vector<Objects::PointLight>& pointLights, const Objects::Camera& camera) : camera(Math::Vec3(0, 0, 0), Math::Vec3(0, 0, 0)) {
        this->renderableObjects = renderableObjects;
        this->pointLights = pointLights;
        this->camera = camera;
    }

    std::vector<Objects::RenderableObject>& Scene::GetRenderableObjects() {
        return renderableObjects;
    }

    std::vector<Objects::PointLight>& Scene::GetLightObjects() {
        return pointLights;
    }

    Objects::Camera& Scene::GetCamera() {
        return camera;
    }
}  // namespace Tracer::Rendering