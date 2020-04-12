#include "scene.hpp"

namespace Tracer::Rendering {
    Scene::Scene() {
        objects = std::vector<std::unique_ptr<Objects::Object>>();
    }

    std::vector<std::unique_ptr<Objects::Object>> Scene::GetSceneObjects() const {
        return objects;
    }

    void Scene::AddObject(Objects::Object object) {
        bool isTagPresent = false;
        for(int i = 0; i < objects.size(); i++) {
            if(objects[i]->GetTag() == object.GetTag()) {
                return;
            }
        }
        objects.push_back(std::unique_ptr<Objects::Object>(new Objects::Object(object)));
    }

    void Scene::RemoveObject(std::string tag) {
        for(int i = 0; i < objects.size(); i++) {
            if(objects[i]->GetTag() == tag) {
                objects.erase(objects.begin() + i);
                break;
            }
        }
    }
}  // namespace Tracer::Rendering