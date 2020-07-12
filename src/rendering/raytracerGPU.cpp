#include "raytracerGPU.hpp"

namespace Tracer::Rendering {
    RaytracerGPU::RaytracerGPU() {
        computeShader = Shader("resources/shaders/raytracing.comp", GL_COMPUTE_SHADER);
    }

    void RaytracerGPU::RenderSceneToScreen(Scene& scene, int screenWidth, int screenHeight) const {
        SceneData sceneData = ConvertSceneToStruct(scene);

        computeShader.Activate();

        unsigned int shaderDataBuffer;
        glGenBuffers(1, &shaderDataBuffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderDataBuffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(sceneData), &sceneData, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderDataBuffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        glDispatchCompute(600, 400, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    SceneData RaytracerGPU::ConvertSceneToStruct(Scene& scene) const {
        SceneData sceneData;

        //MeshObjects
        int meshObjectIndex = 0;
        for (std::unique_ptr<Objects::MeshObject>& meshObject : scene.GetMeshObjects()) {
            MeshObject meshObjectData;
            int vertexIndex = 0;
            int triangleCount = 0;
            for (Math::Tris triangle : meshObject->GetMesh().GetData()) {
                meshObjectData.vertexData[vertexIndex] = glm::vec4(triangle.vert0, 1.0f);
                meshObjectData.vertexData[vertexIndex + 1] = glm::vec4(triangle.vert1, 1.0f);
                meshObjectData.vertexData[vertexIndex + 2] = glm::vec4(triangle.vert2, 1.0f);
                vertexIndex += 3;
                triangleCount++;
            }
            meshObjectData.modelMatrix = meshObject->GetTransform().GetTransformMatrix();
            meshObjectData.numTris = glm::vec4(triangleCount, 0, 0, 0);
            sceneData.meshObjects[meshObjectIndex] = meshObjectData;
            meshObjectIndex++;
        }
        sceneData.numMeshModels = meshObjectIndex;

        //Spheres
        int sphereIndex = 0;
        for (std::unique_ptr<Objects::Sphere>& sphere : scene.GetSpheres()) {
            Sphere sphereData;
            sphereData.radius[0] = sphere->GetRadius();
            sphereData.position = glm::vec4(sphere->GetTransform().GetPosition(), 0);
            sceneData.spheres[sphereIndex] = sphereData;
            sphereIndex++;
        }
        sceneData.numSpheres = sphereIndex;

        //Lights
        int lightIndex = 0;
        for (std::unique_ptr<Objects::PointLight>& pointLight : scene.GetPointLights()) {
            PointLight lightData;
            lightData.position = glm::vec4(pointLight->GetTransform().GetPosition(), 0);
            lightData.color = glm::vec4(pointLight->GetColor().r, pointLight->GetColor().g, pointLight->GetColor().b, pointLight->GetIntensity());
            sceneData.pointLights[lightIndex] = lightData;
            lightIndex++;
        }
        sceneData.numPointLights = lightIndex;

        //Camera
        Camera cameraData;
        cameraData.modelMatrix = scene.GetCamera().GetTransform().GetTransformMatrix();

        return sceneData;
    }
}