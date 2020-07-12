#pragma once

#include "raytracer.hpp"

namespace Tracer::Rendering {
    //Structs for arranging data that can be sent to the gpu
    struct Material {
        glm::vec4 color;
        glm::vec4 modifiers;  //First value is reflectivness, second one is transparency
    };

    struct Sphere {
        glm::vec4 position;
        glm::vec4 radius;
        Material material;
    };

    struct MeshObject {
        glm::vec4 vertexData[1024];
        glm::mat4 modelMatrix;
        glm::vec4 numTris;
        Material material;
    };

    struct PointLight {
        glm::vec4 position;
        glm::vec4 color;
    };

    struct Camera {
        glm::mat4 modelMatrix;
    };

    struct SceneData {
        MeshObject meshObjects[4];
        Sphere spheres[4];
        PointLight pointLights[4];
        Camera camera;
        int numMeshModels;
        int numSpheres;
        int numPointLights;
    };

    class RaytracerGPU : public Raytracer {
        Shader computeShader;
    public:
        RaytracerGPU();

        virtual void RenderSceneToScreen(Scene& scene, int screenWidth, int screenHeight) const;

    private:
        SceneData ConvertSceneToStruct(Scene& scene) const;
    };
}  // namespace Tracer::Rendering