#include "raytracerGPU.hpp"

namespace Tracer::Rendering {
    RaytracerGPU::RaytracerGPU() {}

    void RaytracerGPU::RenderSceneToScreen(Scene& scene, int screenWidth, int screenHeight) const {
        ShaderData shaderData;

        int modelIndex = 0;
        for (Objects::MeshObject meshObjects : scene.GetMeshObjects()) {
            Model model;
            int vertexIndex = 0;
            int triangleCount = 0;
            for (Math::Tris triangle : meshObjects.GetMesh().GetData()) {
                model.vertexData[vertexIndex] = glm::vec4(triangle.vert0, 1.0f);
                model.vertexData[vertexIndex + 1] = glm::vec4(triangle.vert1, 1.0f);
                model.vertexData[vertexIndex + 2] = glm::vec4(triangle.vert2, 1.0f);
                vertexIndex += 3;
                triangleCount++;
            }
            model.modelMatrix = glm::mat4(meshObjects.GetTransform().GetTransformMatrix());
            model.numTris = glm::vec4(triangleCount, 0, 0, 0);
            shaderData.models[modelIndex] = model;
            modelIndex++;
        }
        shaderData.numModels = modelIndex;

        int lightIndex = 0;
        for (Objects::PointLight* pointLight : scene.GetLightObjects()) {
            Light light;
            light.position = glm::vec4(pointLight->GetTransform().GetPosition(), 0);
            light.color = glm::vec4(pointLight->GetColor().r, pointLight->GetColor().g, pointLight->GetColor().b, pointLight->GetIntensity());
            shaderData.lights[lightIndex] = light;
            lightIndex++;
        }
        shaderData.numLights = lightIndex;
        shaderData.cameraPosition = glm::vec4(scene.GetCamera().GetTransform().GetPosition(), 0);

        unsigned int shaderDataBuffer;
        glGenBuffers(1, &shaderDataBuffer);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderDataBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(shaderData), &shaderData, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderDataBuffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}