#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "intersectionData.hpp"
#include "raytracer.hpp"
#include "shader.hpp"
#include "material.hpp"

namespace Tracer::Rendering {
    struct IntersectionData {
        Tracer::Components::Material material;
        glm::vec3 position;
        glm::vec3 normal;
        bool hit;
    };

    struct Ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    struct RTNode {
        IntersectionData intersectionData;
        Ray reflectionRay;
        glm::vec3 reflectionColor;
        bool hasReflectionRay;
        Ray refractionRay;
        glm::vec3 refractionColor;
        bool hasRefractionRay;
        float fresnel;
        glm::vec3 combinedColor;
    };

    class RaytracerIterative : public Raytracer {
        Shader textureShader;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        unsigned int texture;

    public:
        RaytracerIterative(SDL_Window* window);

        virtual void RenderSceneToWindow(Scene& scene) const;

    private:
        std::vector<unsigned char> RenderSceneToBuffer(Scene& scene) const;

        glm::vec3 raytracePixel(Scene& scene, glm::vec3 origin, glm::vec3 dir) const;

        RTNode raytraceRay(Scene& scene, Ray ray, int depth) const;

        IntersectionData raycastObjects(Scene& scene, glm::vec3 origin, glm::vec3 dir) const;
    };
}  // namespace Tracer::Rendering