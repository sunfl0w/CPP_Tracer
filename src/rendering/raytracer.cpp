#include "raytracer.hpp"

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
                vertexIndex += 3;
                triangleCount++;
            }
            model.modelMatrix = glm::mat4(renderableObject.GetTransform().GetTransformMatrix());
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

    std::vector<unsigned char> Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        std::vector<unsigned char> buffer = std::vector<unsigned char>(imageWidth * 3 * imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.0f);

        glm::vec3 camPos = scene.GetCamera().GetTransform().GetPosition();
        glm::mat4 rayMatrix = glm::mat4(1.0f);
        rayMatrix = glm::rotate(rayMatrix, -glm::radians(scene.GetCamera().GetTransform().GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
        rayMatrix = glm::rotate(rayMatrix, glm::radians(scene.GetCamera().GetTransform().GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = -(1 - 2 * ((y + 0.5) * invHeight)) * angle;  //Y-Axis is flipped
                glm::vec3 rayDirBase = glm::vec3(xx, yy, 1);
                glm::vec4 rayDirBaseV4 = rayMatrix * glm::vec4(rayDirBase.x, rayDirBase.y, rayDirBase.z, 1);

                glm::vec3 rayDir = glm::vec3(rayDirBaseV4.x, rayDirBaseV4.y, rayDirBaseV4.z);

                glm::vec3 pixelColor = Raytrace(scene, camPos, rayDir, 0);

                buffer[(x + y * imageWidth) * 3] = (unsigned char)(pixelColor.r * 255.0f);
                buffer[(x + y * imageWidth) * 3 + 1] = (unsigned char)(pixelColor.g * 255.0f);
                buffer[(x + y * imageWidth) * 3 + 2] = (unsigned char)(pixelColor.b * 255.0f);
            }
        }
        return buffer;
    }

    IntersectionData Raytracer::RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, glm::vec3& origin, glm::vec3& dir) const {
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
                    closestIntersect.SetMaterial(renderableObject.GetMaterial());
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
        float epsilon = 0.000001f;

        if (det < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        float invDet = 1.0f / det;

        glm::vec3 tvec = origin - vertex0;

        float x = glm::dot(tvec, pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        glm::vec3 qvec = glm::cross(tvec, edge1);
        //qvec.Normalize();
        float y = glm::dot(dir, qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        float z = glm::dot(edge2, qvec) * invDet;

        glm::vec3 intersect = vertex0 + edge2 * x + edge1 * y;
        glm::vec3 norm = glm::cross(edge1, edge2);
        norm = glm::normalize(norm);
        norm = norm * 0.00001f;
        intersect = intersect + norm;

        if (z < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        return IntersectionData(triangle, intersect, true);
    }

    glm::vec3 Raytracer::Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const {
        Math::IntersectionData intersect = RayCastObjects(scene.GetRenderableObjects(), origin, dir);
        glm::vec3 surfaceColor = glm::vec3(0, 0, 0);
        if (intersect.IsHit()) {
            if (depth < 3 && (intersect.GetMaterial().GetReflectivity() > 0.0f || intersect.GetMaterial().GetTransparency() > 0.0f)) {
                //Reflective and refractive color computation
                glm::vec3 intersectPos = intersect.GetIntersectionPos();
                bool inObject = false;
                glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                norm = glm::normalize(norm);
                if (glm::dot(dir, norm) > 0) {
                    norm = -norm;
                    inObject = true;
                }

                float facingRatio = -glm::dot(dir, norm);
                float fresnel = glm::mix((float)std::pow(1 - facingRatio, 3), 1.0f, 0.1f);

                glm::vec3 reflectionDir = dir - norm * 2.0f * glm::dot(dir, norm);
                reflectionDir = glm::normalize(reflectionDir);

                glm::vec3 newRayOrigin = intersectPos + norm * 0.0001f;
                glm::vec3 reflectionColor = Raytrace(scene, newRayOrigin, reflectionDir, depth + 1);
                if (depth == 0) {
                    int i = 0;
                }
                glm::vec3 refractionColor = glm::vec3(0, 0, 0);

                if (intersect.GetMaterial().GetTransparency() > 0.0f) {
                    float ior = 1.1f;
                    float eta = ior;
                    if (!inObject) {
                        eta = 1.0f / ior;
                    }
                    float cosi = -glm::dot(dir, norm);
                    float k = 1 - eta * eta * (1 - cosi * cosi);
                    glm::vec3 refractionDir = dir * eta + norm * (eta * cosi - std::sqrt(k));
                    refractionDir = glm::normalize(refractionDir);
                    newRayOrigin = intersectPos - norm * 0.0001f;
                    refractionColor = Raytrace(scene, newRayOrigin, refractionDir, depth + 1);
                }

                surfaceColor = (reflectionColor * fresnel + refractionColor * (1 - fresnel) * intersect.GetMaterial().GetTransparency()) * intersect.GetMaterial().GetColor();
                int i = 0;
            } else {
                //Diffuse color computation
                for (Objects::PointLight* light : scene.GetLightObjects()) {
                    float dst = glm::distance(intersect.GetIntersectionPos(), light->GetTransform().GetPosition());
                    if (dst < 1.0f) {
                        dst = 1.0f;
                    }

                    glm::vec3 shadowRayDir = light->GetTransform().GetPosition() - intersect.GetIntersectionPos();
                    shadowRayDir = glm::normalize(shadowRayDir);
                    glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                    norm = glm::normalize(norm);

                    glm::vec3 newRayOrigin = intersect.GetIntersectionPos() + norm * 0.1f;
                    Math::IntersectionData shadowIntersect = RayCastObjects(scene.GetRenderableObjects(), newRayOrigin, shadowRayDir);
                    if (!shadowIntersect.IsHit()) {
                        //Diffuse color calculation. Light intensity uses the inverse square law
                        surfaceColor += intersect.GetMaterial().GetColor() * 1.0f * std::max(0.0f, glm::dot(norm, shadowRayDir)) * light->GetColor() * light->GetIntensity() * 1.0f / std::pow(dst, 0.01f);
                    }
                }
            }
            if (surfaceColor.r > 1.0f || surfaceColor.g > 1.0f || surfaceColor.b > 1.0f) {
                surfaceColor = glm::normalize(surfaceColor);
            }
        }
        return surfaceColor;
    }
}  // namespace Tracer::Rendering