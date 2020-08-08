#include "scene.hpp"

namespace Tracer::Rendering {
    Scene::Scene() {}

    void Scene::LoadSceneDataFromFile(std::string path) {
        pugi::xml_document xmlDoc;
        xmlDoc.load_file(path.c_str());
    }

    void Scene::AddMeshObject(Objects::MeshObject& meshObject) {
        meshObjects.push_back(std::make_unique<Objects::MeshObject>(meshObject));
        renderableObjects.push_back(std::make_unique<Objects::MeshObject>(meshObject));
    }

    void Scene::AddSphere(Objects::Sphere& sphere) {
        spheres.push_back(std::make_unique<Objects::Sphere>(sphere));
        renderableObjects.push_back(std::make_unique<Objects::Sphere>(sphere));
    }

    void Scene::AddPointLight(Objects::PointLight& pointLight) {
        pointLights.push_back(std::make_unique<Objects::PointLight>(pointLight));
    }

    void Scene::SetCamera(Objects::Camera& camera) {
        this->camera = camera;
    }

    std::vector<std::unique_ptr<Objects::RenderableObject>>& Scene::GetRenderableObjects() {
        return renderableObjects;
    }

    std::vector<std::unique_ptr<Objects::MeshObject>>& Scene::GetMeshObjects() {
        return meshObjects;
    }

    std::vector<std::unique_ptr<Objects::Sphere>>& Scene::GetSpheres() {
        return spheres;
    }

    std::vector<std::unique_ptr<Objects::PointLight>>& Scene::GetPointLights() {
        return pointLights;
    }

    Objects::Camera& Scene::GetCamera() {
        return camera;
    }
}  // namespace Tracer::Rendering