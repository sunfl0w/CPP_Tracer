#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "meshObject.hpp"
#include "sphereObject.hpp"
#include "pointLight.hpp"
#include "camera.hpp"

namespace Tracer::Rendering {
    class Scene {
    private:
        std::vector<Objects::MeshObject> meshObjects;
        std::vector<Objects::SphereObject> sphereObjects;
        std::vector<Objects::PointLight*> pointLights;
        Objects::Camera camera;

    public:
        Scene(std::vector<Objects::MeshObject>& meshObjects, std::vector<Objects::SphereObject>& sphereObjects, std::vector<Objects::PointLight*> pointLights, Objects::Camera& camera);

        std::vector<Objects::MeshObject>& GetMeshObjects();

        std::vector<Objects::SphereObject>& GetSphereObjects();

        std::vector<Objects::PointLight*> GetLightObjects();

        Objects::Camera& GetCamera();
    };
}  // namespace Tracer::Rendering