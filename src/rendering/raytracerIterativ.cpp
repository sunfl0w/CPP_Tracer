#include "raytracerIterative.hpp"

namespace Tracer::Rendering {
    RaytracerIterative::RaytracerIterative(SDL_Window* window) : Raytracer(window) {
        textureShader = Shader("resources/shaders/texture.vs", GL_VERTEX_SHADER, "resources/shaders/texture.fs", GL_FRAGMENT_SHADER);

        //Populate buffer objects for later rendering of the texture
        float vertices[] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 1.0f};

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3};

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //Init Texure
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::vector<unsigned char> buffer = std::vector<unsigned char>(screenWidth * 3 * screenHeight);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RaytracerIterative::RenderSceneToWindow(Scene& scene) const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        textureShader.Activate();
        textureShader.SetInt("tex", 0);

        std::vector<unsigned char> buffer = RenderSceneToBuffer(scene);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    std::vector<unsigned char> RaytracerIterative::RenderSceneToBuffer(Scene& scene) const {
        std::vector<unsigned char> buffer = std::vector<unsigned char>(screenWidth * 3 * screenHeight);
        float invWidth = 1 / float(screenWidth), invHeight = 1 / float(screenHeight);
        float fov = 30;
        float aspectratio = screenWidth / float(screenHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.0f);

        glm::vec4 camPosWorld = scene.GetCamera().GetTransform().GetTransformMatrix() * glm::vec4(0, 0, 0, 1);

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < screenWidth; x++) {
            for (int y = 0; y < screenHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = -(1 - 2 * ((y + 0.5) * invHeight)) * angle;  //Y-Axis is flipped

                //Calculating the camera ray with camera transformations in mind
                glm::vec4 projectionRayWorld = scene.GetCamera().GetTransform().GetTransformMatrix() * glm::vec4(xx, yy, 1, 1);
                glm::vec4 projectionRayDirWorld = projectionRayWorld - camPosWorld;
                glm::vec3 camPosWorldV3 = glm::vec3(camPosWorld.x, camPosWorld.y, camPosWorld.z);
                glm::vec3 projectionRayDirWorldV3 = glm::vec3(projectionRayDirWorld.x, projectionRayDirWorld.y, projectionRayDirWorld.z);
                projectionRayDirWorldV3 = glm::normalize(projectionRayDirWorldV3);

                //Actual raytracing
                glm::vec3 pixelColor = raytracePixel(scene, camPosWorldV3, projectionRayDirWorldV3);

                buffer[(x + y * screenWidth) * 3] = (unsigned char)(pixelColor.r * 255.0f);
                buffer[(x + y * screenWidth) * 3 + 1] = (unsigned char)(pixelColor.g * 255.0f);
                buffer[(x + y * screenWidth) * 3 + 2] = (unsigned char)(pixelColor.b * 255.0f);
            }
        }
        return buffer;
    }

    glm::vec3 RaytracerIterative::raytracePixel(Scene& scene, glm::vec3 origin, glm::vec3 dir) const {
        //Constants and definitions
        const int maxDepth = 5;
        const int maxNodes = 63;  //Basically pow(2, maxDepth + 1) - 1

        RTNode raytracingArray[maxNodes];

        //Build raytracing tree structure
        for (int i = 0; i < maxNodes; i++) {
            int parent = int(i - 1 / 2);
            int depth = std::floor(log2(i + 1));
            if (parent > 0) {
                if (i == 2 * parent + 1) {
                    raytracingArray[i] = raytraceRay(scene, raytracingArray[parent].reflectionRay, depth);
                } else if (i == 2 * parent + 2) {
                    raytracingArray[i] = raytraceRay(scene, raytracingArray[parent].refractionRay, depth);
                }
            } else {
                Ray ray;
                ray.origin = origin;
                ray.direction = dir;
                raytracingArray[i] = raytraceRay(scene, ray, depth);
                int x = 0;
            }
        }

        //Backtrack from last node to the first
        for (int i = maxNodes - 1; i > 0; i--) {
            int parentIndex = int(i - 1 / 2);
            RTNode parent = raytracingArray[parentIndex];
            RTNode current = raytracingArray[i];

            //Is leaf or inner node?
            if (i >= pow(2, maxDepth) - 1) {
                if (2 * parentIndex + 1 == i && parent.hasReflectionRay) {
                    parent.reflectionColor = current.combinedColor;
                } else if (2 * parentIndex + 2 == i && parent.hasRefractionRay) {
                    parent.refractionColor = current.combinedColor;
                }
            } else {
                current.combinedColor = (current.reflectionColor * current.fresnel * current.intersectionData.material.GetReflectivity() + current.refractionColor * (1 - current.fresnel) * current.intersectionData.material.GetTransparency()) * current.intersectionData.material.GetColor();

                if (2 * parentIndex + 1 == i && parent.hasReflectionRay) {
                    parent.reflectionColor = current.combinedColor;
                } else if (2 * parentIndex + 2 == i && parent.hasRefractionRay) {
                    parent.refractionColor = current.combinedColor;
                }
            }
        }
        /*if (raytracingArray[0].combinedColor != glm::vec3(0, 0, 0)) {
            int k = 0;
        }*/
        return raytracingArray[0].combinedColor;
    }

    RTNode RaytracerIterative::raytraceRay(Scene& scene, Ray ray, int depth) const {
        IntersectionData intersect = raycastObjects(scene, ray.origin, ray.direction);
        RTNode node;
        node.intersectionData = intersect;
        node.combinedColor = glm::vec3(0, 0, 0);
        node.fresnel = 0;
        node.hasReflectionRay = false;
        node.hasRefractionRay = false;

        if (intersect.hit) {
            if ((intersect.material.GetReflectivity() > 0.0f || intersect.material.GetTransparency() > 0.0f) && depth < 5) {
                //Reflective and refractive color computation
                bool inObject = false;
                glm::vec3 norm = intersect.normal;
                if (glm::dot(ray.direction, norm) > 0) {
                    norm = -norm;
                    inObject = true;
                }

                float facingRatio = -dot(ray.direction, norm);
                float fresnel = glm::mix((float)pow(1 - facingRatio, 3), 1.0f, 0.1f);
                node.fresnel = fresnel;

                glm::vec3 reflectionDir = ray.direction - norm * 2.0f * dot(ray.direction, norm);
                reflectionDir = glm::normalize(reflectionDir);

                glm::vec3 newRayOrigin = intersect.position + norm * 0.0001f;

                Ray reflectionRay;
                reflectionRay.origin = newRayOrigin;
                reflectionRay.direction = reflectionDir;

                node.reflectionRay = reflectionRay;
                node.hasReflectionRay = true;

                if (intersect.material.GetTransparency() > 0.0f) {
                    float ior = 1.1f;  //Index of refraction
                    float eta = ior;
                    if (!inObject) {
                        eta = 1.0f / ior;
                    }
                    float cosi = -dot(ray.direction, norm);
                    float k = 1 - eta * eta * (1 - cosi * cosi);
                    glm::vec3 refractionDir = ray.direction * eta + norm * (eta * cosi - sqrt(k));
                    refractionDir = glm::normalize(refractionDir);
                    newRayOrigin = intersect.position - norm * 0.0001f;

                    Ray refractionRay;
                    refractionRay.origin = newRayOrigin;
                    refractionRay.direction = refractionDir;
                    node.reflectionRay = refractionRay;
                    node.hasRefractionRay = true;
                }
            } else {
                //Diffuse color computation
                for (int i = 0; i < scene.GetPointLights().size(); i++) {
                    float dst = glm::distance(intersect.position, scene.GetPointLights()[i]->GetTransform().GetPosition());
                    if (dst < 1.0f) {
                        dst = 1.0f;
                    }

                    glm::vec3 shadowRayDir = scene.GetPointLights()[i]->GetTransform().GetPosition() - intersect.position;
                    glm::vec3 norm = intersect.normal;
                    shadowRayDir = normalize(shadowRayDir);

                    glm::vec3 newRayOrigin = intersect.position + norm * 0.001f;
                    IntersectionData shadowIntersect = raycastObjects(scene, newRayOrigin, shadowRayDir);

                    if (!shadowIntersect.hit) {
                        //Diffuse color calculation. Light intensity uses the inverse square law with a scaling modifier
                        node.combinedColor += intersect.material.GetColor() * 1.0f * std::max(0.0f, dot(norm, shadowRayDir)) * scene.GetPointLights()[i]->GetColor() * scene.GetPointLights()[i]->GetIntensity() * 1.0f / pow(dst, 0.01f);
                    }
                }
            }
        }
        return node;
    }

    IntersectionData RaytracerIterative::raycastObjects(Scene& scene, glm::vec3 origin, glm::vec3 dir) const {
        IntersectionData closestIntersect;
        closestIntersect.hit = false;
        closestIntersect.position = glm::vec3(0, 0, 0);
        float closesIntersectDst = 9999999.0f;

        for (std::unique_ptr<Objects::RenderableObject>& renderableObject : scene.GetRenderableObjects()) {
            Tracer::Math::IntersectionData intersect = renderableObject->Intersect(origin, dir);
            float dst = glm::distance(intersect.GetIntersectionPos(), origin);
            if (intersect.IsHit() && dst < closesIntersectDst) {
                closesIntersectDst = dst;

                closestIntersect.hit = intersect.IsHit();
                closestIntersect.material = intersect.GetMaterial();
                closestIntersect.normal = intersect.GetIntersectionNormal();
                closestIntersect.position = intersect.GetIntersectionPos();
            }
        }
        return closestIntersect;
    }
}  // namespace Tracer::Rendering