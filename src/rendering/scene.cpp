#include "scene.hpp"

namespace Tracer::Rendering {
    Scene::Scene(std::vector<Objects::MeshObject>& meshObjects, std::vector<Objects::SphereObject>& sphereObjects, std::vector<Objects::PointLight*> pointLights, Objects::Camera& camera) {
        this->meshObjects = meshObjects;
        this->sphereObjects = sphereObjects;
        this->pointLights = pointLights;
        this->camera = camera;
    }

    std::vector<Objects::MeshObject>& Scene::GetMeshObjects() {
        return meshObjects;
    }

    std::vector<Objects::SphereObject>& Scene::GetSphereObjects() {
        return sphereObjects;
    }

    std::vector<Objects::PointLight*> Scene::GetLightObjects() {
        return pointLights;
    }

    Objects::Camera& Scene::GetCamera() {
        return camera;
    }
}  // namespace Tracer::Rendering