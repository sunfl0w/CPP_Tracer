#include "raytracer.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    std::vector<unsigned char> Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        std::vector<unsigned char> buffer = std::vector<unsigned char>(imageWidth * 3 * imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.);

        glm::vec3 camPos = scene.GetCamera().GetTransform().GetPosition();

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            //#pragma omp prallel for schedule(dynamic)
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
                glm::vec3 rayDir(xx, yy, 1);
                glm::normalize(rayDir);

                glm::vec3 pixelColor = Raytrace(scene, camPos, rayDir, 5);

                buffer[(x + y * imageWidth) * 4] = (unsigned char)pixelColor.x;
                buffer[(x + y * imageWidth) * 4 + 1] = (unsigned char)pixelColor.y;
                buffer[(x + y * imageWidth) * 4 + 2] = (unsigned char)pixelColor.z;
                buffer[(x + y * imageWidth) * 4 + 3] = 255;
            }
        }
        return buffer;
    }

    IntersectionData Raytracer::RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, glm::vec3& origin, glm::vec3& dir) const {
        IntersectionData closestIntersect = Math::IntersectionData();
        float closesIntersectDst = 999999.9f;
        for (Objects::RenderableObject renderableObject : renderableObjects) {
            for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                IntersectionData intersect = RayCastTris(triangle, origin, dir);
                float dst = glm::distance(intersect.GetIntersectionPos(), origin);
                if (intersect.IsHit() && dst < closesIntersectDst) {
                    closesIntersectDst = dst;
                    closestIntersect = intersect;
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
        glm::normalize(norm);
        norm = norm * 0.0001f;
        intersect = intersect + norm;

        if (z < epsilon) {
            return IntersectionData(glm::vec3(0, 0, 0), triangle, false);
        }

        return IntersectionData(intersect, triangle, true);
    }

    RGB_Color Raytracer::Raytrace(Scene& scene, glm::vec3& origin, glm::vec3& dir, int depth) const {
        Math::IntersectionData intersect = RayCastObjects(scene.GetRenderableObjects(), origin, dir);

        if (intersect.IsHit()) {
            RGB_Color diffuseColor(0, 0, 0);
            RGB_Color albedo(255, 255, 0);
            int lightHits = 0;
            for (Objects::PointLight* light : scene.GetLightObjects()) {
                float diffuseModifier = 1.0f;

                float dst = intersect.GetIntersectionPos().DistanceTo(light->GetTransform().GetPosition());
                glm::vec3 shadowRayDir = light->GetTransform().GetPosition().Subtract(intersect.GetIntersectionPos());
                glm::normalize(shadowRayDir);
                glm::vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                glm::normalize(norm);
                float angleModifier = std::clamp((float)(std::acos(glm::dot(norm, shadowRayDir) * 180.0f / M_PI / 360.0f)), 0.0f, 1.0f);
                diffuseModifier /= 1 + std::pow(dst / (100.0f * light->GetIntensity() * angleModifier), 2.0f);

                Math::IntersectionData shadowIntersect = RayCastObjects(scene.GetRenderableObjects(), intersect.GetIntersectionPos(), shadowRayDir);
                if (!shadowIntersect.IsHit()) {
                    RGB_Color singleLightPixelColor = RGB_Color(std::clamp(albedo.r * (1 - diffuseModifier) + light->GetColor().GetRGB().r * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f),
                                                                std::clamp(albedo.g * (1 - diffuseModifier) + light->GetColor().GetRGB().g * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f),
                                                                std::clamp(albedo.b * (1 - diffuseModifier) + light->GetColor().GetRGB().b * (1 - diffuseModifier) * 0.3f, 0.0f, 255.0f));
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