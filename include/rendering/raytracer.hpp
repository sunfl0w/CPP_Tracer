#pragma once
#include <glad/glad.h>

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "intersectionData.hpp"
#include "mesh.hpp"
#include "pointLight.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "transform.hpp"
#include "tris.hpp"

namespace Tracer::Rendering {
    struct Material {
        glm::vec4 color;
        glm::vec4 modifiers; //First value is reflectivness, second one is transparency
    };

    struct Sphere {
        glm::mat4 transformMatrix;
        glm::vec4 radius;
    };

    struct MeshObject {
        glm::vec4 vertexData[1024];
        glm::mat4 transformMatrix;
        glm::vec4 numTris;
    };

    struct Light {
        glm::vec4 position;
        glm::vec4 color;
    };

    struct SceneData {
        MeshObject meshObjects[4];
        Sphere spheres[4];
        Light lights[4];
        glm::vec4 cameraPosition;
        int numLights;
        int numModels;
    };
    
    class Raytracer {
    public:
        Raytracer();

        virtual void RenderSceneToScreen(Scene& scene, int screenWidth, int screenHeight) const = 0;

        std::vector<unsigned char> RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const;

        IntersectionData RayCastObjects(std::vector<std::unique_ptr<Objects::RenderableObject>>& renderableObjects, glm::vec3& origin, glm::vec3& dir) const;

        IntersectionData RayCastTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const;

        glm::vec3 Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const;
    };
}  // namespace Tracer::Rendering