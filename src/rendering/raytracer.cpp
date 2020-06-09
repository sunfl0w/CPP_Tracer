#include "raytracer.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    void Raytracer::RenderSceneToImage(Scene& scene, int imageWidth, int imageHeight) const {
        ShaderData shaderData;

        int modelIndex = 0;
        for (Objects::RenderableObject renderableObject : scene.GetRenderableObjects()) {
            Model model;
            int vertexIndex = 0;
            int triangleCount = 0;
            for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                model.vertexData[vertexIndex] = glm::vec4(triangle.vert0, 1.0f);
                model.vertexData[vertexIndex + 1] = glm::vec4(triangle.vert1, 1.0f);
                model.vertexData[vertexIndex + 2] = glm::vec4(triangle.vert2, 1.0f);
                vertexIndex+=3;
                triangleCount++;
            }
            model.modelMatrix = renderableObject.GetTransform().GetTransformMatrix();
            model.numTris = triangleCount;
            shaderData.models[modelIndex] = model;
            modelIndex++;
        }
        shaderData.numModels = modelIndex;
        
        int lightIndex = 0;
        for(Objects::PointLight* light : scene.GetLightObjects()) {
            shaderData.lightPositionData[lightIndex] = glm::vec4(light->GetTransform().GetPosition(), 0);
            shaderData.lightColorData[lightIndex] = glm::vec4(light->GetColor().r, light->GetColor().g, light->GetColor().b, 0);
            shaderData.lightIntensity[lightIndex] = light->GetIntensity();
            lightIndex++;
        }
        shaderData.numLights = lightIndex;
        shaderData.cameraPosition = glm::vec4(scene.GetCamera().GetTransform().GetPosition(), 0);

        unsigned int ssbo;
        glGenBuffers(1, &ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(shaderData), &shaderData, GL_DYNAMIC_COPY);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    std::vector<unsigned char> Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        std::vector<unsigned char> buffer = std::vector<unsigned char>(imageWidth * 3 * imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.0f);

        glm::vec3 camPos = scene.GetCamera().GetTransform().GetPosition();

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = -(1 - 2 * ((y + 0.5) * invHeight)) * angle;//Y-Axis is flipped
                glm::vec3 rayDir(xx, yy, 1);
                rayDir = glm::normalize(rayDir);

                RGB_Color pixelColor = Raytrace(scene, camPos, rayDir, 2);

                buffer[(x + y * imageWidth) * 3] = (unsigned char)pixelColor.r;
                buffer[(x + y * imageWidth) * 3 + 1] = (unsigned char)pixelColor.g;
                buffer[(x + y * imageWidth) * 3 + 2] = (unsigned char)pixelColor.b;
            }
        }
        return buffer;
    }

    IntersectionData Raytracer::RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, glm::vec3& origin, glm::vec3& dir, RGB_Color& albedo) const {
        IntersectionData closestIntersect = Math::IntersectionData();
        float closesIntersectDst = 999999.9f;
        for (Objects::RenderableObject renderableObject : renderableObjects) {
            for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                Math::Tris transformedTriangle;
                transformedTriangle.vert0 = renderableObject.GetTransform().GetTransformMatrix() * glm::vec4(triangle.vert0, 1.0f);
                transformedTriangle.vert1 = renderableObject.GetTransform().GetTransformMatrix() * glm::vec4(triangle.vert1, 1.0f);
                transformedTriangle.vert2 = renderableObject.GetTransform().GetTransformMatrix() * glm::vec4(triangle.vert2, 1.0f);
                IntersectionData intersect = RayCastTris(transformedTriangle, origin, dir);
                float dst = glm::distance(intersect.GetIntersectionPos(), origin);
                if (intersect.IsHit() && dst < closesIntersectDst) {
                    closesIntersectDst = dst;
                    closestIntersect = intersect;
                    albedo = renderableObject.GetMaterial().GetColor();
                }
            }
        }
        return closestIntersect;
    }

    IntersectionData Raytracer::RayCastTris(Math::Tris& triangle, glm::vec3& origin, glm::vec3& dir) const {
        //Möller–Trumbore intersection algorithm
        glm::vec3 vertex0 = triangle.vert0;
        glm::vec3 vertex1 = triangle.vert1;
        glm::vec3 vertex2 = triangle.vert2;

        glm::vec3 edge1 = vertex1 - vertex0;
        glm::vec3 edge2 = vertex2 - vertex0;

        glm::vec3 pvec = glm::cross(dir, edge2);
        //pvec.Normalize();
        float det = glm::dot(edge1, pvec);

        //float epsilon = std::numeric_limits<float>::epsilon();
        float epsilon = 0.0000001f;

        if (det < epsilon) {
            return IntersectionData(glm::vec3(0, 0, 0), triangle, false);
        }

        float invDet = 1.0f / det;

        glm::vec3 tvec = origin - vertex0;

        float x = glm::dot(tvec, pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return IntersectionData(glm::vec3(0, 0, 0), triangle, false);
        }

        glm::vec3 qvec = glm::cross(tvec, edge1);
        //qvec.Normalize();
        float y = glm::dot(dir, qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return IntersectionData(glm::vec3(0, 0, 0), triangle, false);
        }

        float z = glm::dot(edge2, qvec) * invDet;

        glm::vec3 intersect = vertex0 + edge2 * x + edge1 * y;
        glm::vec3 norm = glm::cross(edge1, edge2);
        norm = glm::normalize(norm);
        norm = norm * 0.0001f;
        intersect = intersect + norm;

        if (z < epsilon) {
            return IntersectionData(glm::vec3(0, 0, 0), triangle, false);
        }

        return IntersectionData(intersect, triangle, true);
    }

    RGB_Color Raytracer::Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const {
        RGB_Color albedo(0, 0, 0);
        Math::IntersectionData intersect = RayCastObjects(scene.GetRenderableObjects(), origin, dir, albedo);

        if (intersect.IsHit()) {
            RGB_Color diffuseColor(0, 0, 0);

            int lightHits = 0;
            for (Objects::PointLight* light : scene.GetLightObjects()) {
                float diffuseModifier = 1.0f;

                float dst = glm::distance(intersect.GetIntersectionPos(), light->GetTransform().GetPosition());
                glm::vec3 shadowRayDir = light->GetTransform().GetPosition() - intersect.GetIntersectionPos();
                shadowRayDir = glm::normalize(shadowRayDir);
                glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                norm = glm::normalize(norm);
                float angleModifier = std::clamp((float)(std::acos(glm::dot(norm, shadowRayDir)) * 180.0f / M_PI / 360.0f), 0.0f, 1.0f);
                diffuseModifier /= 1 + std::pow(dst / (100.0f * light->GetIntensity() * angleModifier), 2.0f);

                RGB_Color shadowAlbedo;
                Math::IntersectionData shadowIntersect = RayCastObjects(scene.GetRenderableObjects(), intersect.GetIntersectionPos(), shadowRayDir, shadowAlbedo);
                if (!shadowIntersect.IsHit()) {
                    RGB_Color singleLightPixelColor = RGB_Color(std::clamp(albedo.r * (1 - diffuseModifier) + light->GetColor().r * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f),
                                                                std::clamp(albedo.g * (1 - diffuseModifier) + light->GetColor().g * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f),
                                                                std::clamp(albedo.b * (1 - diffuseModifier) + light->GetColor().b * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f));
                    diffuseColor = RGB_Color(std::clamp(diffuseColor.r + singleLightPixelColor.r * (1.0f / scene.GetLightObjects().size()), 0.0f, 255.0f),
                                             std::clamp(diffuseColor.g + singleLightPixelColor.g * (1.0f / scene.GetLightObjects().size()), 0.0f, 255.0f),
                                             std::clamp(diffuseColor.b + singleLightPixelColor.b * (1.0f / scene.GetLightObjects().size()), 0.0f, 255.0f));
                    lightHits++;
                }
            }
            if (lightHits > 0) {
                return diffuseColor;
            } else {
                return RGB_Color(0, 0, 0);
            }
        } else {
            return RGB_Color(0, 0, 0);
        }
    }
}  // namespace Tracer::Rendering