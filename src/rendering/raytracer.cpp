#include "raytracer.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        ScreenBuffer screenBuffer(imageWidth, imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.);

        Math::Vec3 camPos = scene.GetCamera().GetTransform().GetPosition();

#pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            //#pragma omp prallel for schedule(dynamic)
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
                Math::Vec3 rayDir(xx, yy, 1);
                rayDir.Normalize();

                screenBuffer.SetPixelColor(x, y, Raytrace(scene, camPos, rayDir, 5));
            }
        }
        return screenBuffer;
    }

    IntersectionData Raytracer::RayCastObjects(std::vector<Objects::RenderableObject>& renderableObjects, Math::Vec3& origin, Math::Vec3& dir) const {
        IntersectionData closestIntersect = Math::IntersectionData();
        float closesIntersectDst = 999999.9f;
        for (Objects::RenderableObject renderableObject : renderableObjects) {
            for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                IntersectionData intersect = RayCastTris(triangle, origin, dir);
                if (intersect.IsHit() && intersect.GetIntersectionPos().DistanceTo(origin) < closesIntersectDst) {
                    closesIntersectDst = intersect.GetIntersectionPos().DistanceTo(origin);
                    closestIntersect = intersect;
                }
            }
        }
        return closestIntersect;
    }

    IntersectionData Raytracer::RayCastTris(Math::Tris& triangle, Math::Vec3& origin, Math::Vec3& dir) const {
        //Möller–Trumbore intersection algorithm
        Math::Vec3 vertex0 = Math::Vec3(triangle.GetV0());
        Math::Vec3 vertex1 = Math::Vec3(triangle.GetV1());
        Math::Vec3 vertex2 = Math::Vec3(triangle.GetV2());

        Math::Vec3 edge1 = vertex1.Subtract(vertex0);
        Math::Vec3 edge2 = vertex2.Subtract(vertex0);

        Math::Vec3 pvec = dir.Cross(edge2);
        //pvec.Normalize();
        float det = edge1.Dot(pvec);

        //float epsilon = std::numeric_limits<float>::epsilon();
        float epsilon = 0.0000001f;

        if (det < epsilon) {
            return IntersectionData(Math::Vec3(0, 0, 0), triangle, false);
        }

        float invDet = 1.0f / det;

        Math::Vec3 tvec = origin.Subtract(vertex0);

        float x = tvec.Dot(pvec) * invDet;
        if (x < 0.0f || x > 1.0f) {
            return IntersectionData(Math::Vec3(0, 0, 0), triangle, false);
        }

        Math::Vec3 qvec = tvec.Cross(edge1);
        //qvec.Normalize();
        float y = dir.Dot(qvec) * invDet;
        if (y < 0.0f || x + y > 1.0f) {
            return IntersectionData(Math::Vec3(0, 0, 0), triangle, false);
        }

        float z = edge2.Dot(qvec) * invDet;

        Math::Vec3 intersect = vertex0.Add(edge2.Multiply(x).Add(edge1.Multiply(y)));
        Math::Vec3 norm = edge1.Cross(edge2);
        norm.Normalize();
        norm = norm.Multiply(0.0001f);
        intersect = intersect.Add(norm);

        if (z < epsilon) {
            return IntersectionData(Math::Vec3(0, 0, 0), triangle, false);
        }

        return IntersectionData(intersect, triangle, true);
    }

    RGB_Color Raytracer::Raytrace(Scene& scene, Math::Vec3& origin, Math::Vec3& dir, int depth) const {
        Math::IntersectionData intersect = RayCastObjects(scene.GetRenderableObjects(), origin, dir);

        if (intersect.IsHit()) {
            RGB_Color diffuseColor(255, 150, 0);
            int lightHits = 0;
            for (Objects::PointLight* light : scene.GetLightObjects()) {
                float diffuseModifier = 1.0f;

                float dst = intersect.GetIntersectionPos().DistanceTo(light->GetTransform().GetPosition());
                Math::Vec3 shadowRayDir = light->GetTransform().GetPosition().Subtract(intersect.GetIntersectionPos());
                shadowRayDir.Normalize();
                Math::Vec3 norm = intersect.GetIntersectionTriangle().GetNormal();
                std::cout << std::acos(norm.Dot(shadowRayDir)) * 180.f / M_PI << std::endl;
                float angle = std::acos(norm.Dot(shadowRayDir)) * 180.f / M_PI;
                float angleModifier = std::clamp((float)(std::acos(norm.Dot(shadowRayDir)) * 180.0f / M_PI / 360.0f), 0.0f, 1.0f);
                //float test = dst / (50.0f * light->GetIntensity() * angleModifier);
                diffuseModifier /= 1 + std::pow(dst / (100.0f * light->GetIntensity() * angleModifier), 2.0f);
                if (angle < 20.0f) {
                    int i = 0;
                }

                Math::IntersectionData shadowIntersect = RayCastObjects(scene.GetRenderableObjects(), intersect.GetIntersectionPos(), shadowRayDir);
                if (!shadowIntersect.IsHit()) {
                    diffuseColor = RGB_Color(std::clamp(diffuseColor.r * diffuseModifier + light->GetColor().GetRGB().r * (1 - diffuseModifier), 0.0f, 255.0f),
                                             std::clamp(diffuseColor.g * diffuseModifier + light->GetColor().GetRGB().g * (1 - diffuseModifier), 0.0f, 255.0f),
                                             std::clamp(diffuseColor.b * diffuseModifier + light->GetColor().GetRGB().b * (1 - diffuseModifier), 0.0f, 255.0f));
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