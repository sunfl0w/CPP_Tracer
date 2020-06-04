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
    struct ShaderData {
        glm::vec4 vertexData[512];
        glm::vec4 lightPositionData[4];
        glm::vec4 lightColorData[4];
        float lightIntensity[4];
        glm::vec4 cameraPosition;
        int numTris;
        int numLights;
    };
    
    class Raytracer {
    public:
        Raytracer();

        void RenderSceneToImage(Scene& scene, int imageWidth, int imageHeight) const;

        std::vector<unsigned char> RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const;

        IntersectionData RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, glm::vec3& origin, glm::vec3& dir, RGB_Color& albedo) const;

        IntersectionData RayCastTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const;

        RGB_Color Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const;
    };
}  // namespace Tracer::Rendering