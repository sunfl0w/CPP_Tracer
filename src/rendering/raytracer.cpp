#include "raytracer.hpp"

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    std::vector<unsigned char> Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        std::vector<unsigned char> buffer = std::vector<unsigned char>(imageWidth * 3 * imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.0f);

        glm::vec4 camPosWorld = scene.GetCamera().GetTransform().GetTransformMatrix() * glm::vec4(0, 0, 0, 1);

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = -(1 - 2 * ((y + 0.5) * invHeight)) * angle;  //Y-Axis is flipped

                glm::vec4 projectionRayWorld = scene.GetCamera().GetTransform().GetTransformMatrix() * glm::vec4(xx, yy, 1, 1);
                glm::vec4 projectionRayDirWorld = projectionRayWorld - camPosWorld;
                glm::vec3 camPosWorldV3 = glm::vec3(camPosWorld.x, camPosWorld.y, camPosWorld.z);
                glm::vec3 projectionRayDirWorldV3 = glm::vec3(projectionRayDirWorld.x, projectionRayDirWorld.y, projectionRayDirWorld.z);
                glm::vec3 pixelColor = Raytrace(scene, camPosWorldV3, projectionRayDirWorldV3, 0);

                buffer[(x + y * imageWidth) * 3] = (unsigned char)(pixelColor.r * 255.0f);
                buffer[(x + y * imageWidth) * 3 + 1] = (unsigned char)(pixelColor.g * 255.0f);
                buffer[(x + y * imageWidth) * 3 + 2] = (unsigned char)(pixelColor.b * 255.0f);
            }
        }
        return buffer;
    }

    IntersectionData Raytracer::RayCastObjects(std::vector<std::unique_ptr<Objects::RenderableObject>>& renderableObjects, glm::vec3& origin, glm::vec3& dir) const {
        IntersectionData closestIntersect = Math::IntersectionData();
        float closesIntersectDst = 99999999.9f;
        for (std::unique_ptr<Objects::RenderableObject>& renderableObject : renderableObjects) {
            IntersectionData intersect = renderableObject.get()->Intersect(origin, dir);
            float dst = glm::distance(intersect.GetIntersectionPos(), origin);
            if (intersect.IsHit() && dst < closesIntersectDst) {
                closesIntersectDst = dst;
                closestIntersect = intersect;
                closestIntersect.SetMaterial(renderableObject.get()->GetMaterial());
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

        float epsilon = 0.00001f;

        //Culling stuff. Don't touch for now

        /*if (det < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }*/
        //Culling

        if (std::fabs(det) < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        float invDet = 1.0f / det;

        glm::vec3 tvec = origin - vertex0;

        float x = glm::dot(tvec, pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        glm::vec3 qvec = glm::cross(tvec, edge1);
        float y = glm::dot(dir, qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        float z = glm::dot(edge2, qvec) * invDet;

        glm::vec3 intersect = origin + dir * z;

        if (z < epsilon) {
            return IntersectionData(triangle, glm::vec3(0, 0, 0), false);
        }

        return IntersectionData(triangle, intersect, true);
    }

    glm::vec3 Raytracer::Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const {
        Math::IntersectionData intersect = RayCastObjects(scene.GetMeshObjects(), origin, dir);
        glm::vec3 surfaceColor = glm::vec3(0, 0, 0);
        if (intersect.IsHit()) {
            if (depth < 3 && (intersect.GetMaterial().GetReflectivity() > 0.0f || intersect.GetMaterial().GetTransparency() > 0.0f)) {
                //Reflective and refractive color computation
                glm::vec3 intersectPos = intersect.GetIntersectionPos();
                bool inObject = false;
                glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                //norm = glm::normalize(norm);
                /*if (glm::dot(dir, norm) > 0) {
                    norm = -norm;
                    inObject = true;
                }*/

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
                    float ior = 1.5f;  //Index of refraction
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

                surfaceColor = (reflectionColor * fresnel * 0.8f + refractionColor * (1 - fresnel) * intersect.GetMaterial().GetTransparency()) * intersect.GetMaterial().GetColor();
                int i = 0;
            } else {
                //Diffuse color computation
                for (Objects::PointLight* light : scene.GetLightObjects()) {
                    float dst = glm::distance(intersect.GetIntersectionPos(), light->GetTransform().GetPosition());
                    if (dst < 1.0f) {
                        dst = 1.0f;
                    }

                    glm::vec3 shadowRayDir = light->GetTransform().GetPosition() - intersect.GetIntersectionPos();
                    glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();

                    //norm = glm::normalize(norm);
                    shadowRayDir = glm::normalize(shadowRayDir);

                    /*bool inObject = false;
                    if (glm::dot(dir, norm) > 0) {
                        norm = -norm;
                        inObject = true;
                    }*/

                    glm::vec3 newRayOrigin = intersect.GetIntersectionPos() + norm * 0.001f;
                    Math::IntersectionData shadowIntersect = RayCastObjects(scene.GetMeshObjects(), newRayOrigin, shadowRayDir);

                    if (!shadowIntersect.IsHit()) {
                        //Diffuse color calculation. Light intensity uses the inverse square law
                        surfaceColor += intersect.GetMaterial().GetColor() * 1.0f * std::max(0.0f, glm::dot(norm, shadowRayDir)) * light->GetColor() * light->GetIntensity() * 1.0f / std::pow(dst, 0.01f);
                    }
                }
            }
            /*if (surfaceColor.r > 1.0f || surfaceColor.g > 1.0f || surfaceColor.b > 1.0f) {
                surfaceColor = glm::normalize(surfaceColor);
            }*/
        }
        return surfaceColor;
    }
}  // namespace Tracer::Rendering