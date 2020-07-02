#pragma once

#include "raytracer.hpp"

namespace Tracer::Rendering {
    //Structs for arranging data that can be sent to the gpu
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

    class RaytracerGPU : public Raytracer {
        RaytracerGPU();

        virtual void RenderSceneToScreen(Scene& scene, int screenWidth, int screenHeight) const;
    };
}