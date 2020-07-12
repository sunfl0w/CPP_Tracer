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