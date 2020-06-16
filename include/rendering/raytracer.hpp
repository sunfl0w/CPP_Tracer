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
    struct Model {
        glm::vec4 vertexData[1024];
        glm::mat4 modelMatrix;
        glm::vec4 numTris;
    };

    struct Light {
        glm::vec4 position;
        glm::vec4 color;
    };

    struct ShaderData {
        Model models[4];
        Light lights[4];
        glm::vec4 cameraPosition;
        int numLights;
        int numModels;
    };
    
    class Raytracer {
    public:
        Raytracer();

        void RenderSceneToImage(Scene& scene, int imageWidth, int imageHeight) const;

        std::vector<unsigned char> RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const;

        IntersectionData RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, glm::vec3& origin, glm::vec3& dir) const;

        IntersectionData RayCastTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const;

        glm::vec3 Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const;
    };
}  // namespace Tracer::Rendering