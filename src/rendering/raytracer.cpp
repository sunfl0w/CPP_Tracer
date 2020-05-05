#include "raytracer.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        return RenderMeshesToBuffer(scene.GetRenderableObjects(), imageWidth, imageHeight, scene.GetCamera(), scene.GetLightObjects());
    }

    ScreenBuffer Raytracer::RenderMeshesToBuffer(std::vector<Objects::RenderableObject>& renderableObjects, int imageWidth, int imageHeight, Objects::Camera& camera, std::vector<Objects::PointLight*> pointLights) const {
        ScreenBuffer screenBuffer(imageWidth, imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.);

        #pragma omp parallel for schedule(runtime)
        for (int x = 0; x < imageWidth; x++) {
            #pragma omp prallel for schedule(dynamic)
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
                Math::Vec3 rayDir(xx, yy, 1);
                rayDir.Normalize();
                float minDst = 99999999;
                Math::IntersectionData nearestIntersectData = Math::IntersectionData();

                for (Objects::RenderableObject renderableObject : renderableObjects) {
                    for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                        Tris trisPos = renderableObject.GetTransform().TransformTris(triangle);
                        Math::Ray ray = Math::Ray(camera.GetTransform().GetPosition(), rayDir, 100);
                        //if (mesh.RayIntersects(ray)) {
                            Math::IntersectionData intersectData = ray.Cast(trisPos);

                            if (intersectData.IsHit()) {
                                float dst = intersectData.GetIntersectionPos().DistanceTo(camera.GetTransform().GetPosition());
                                if (dst < minDst) {
                                    nearestIntersectData = intersectData;
                                    minDst = dst;
                                }
                            }
                        //}
                    }
                    if (nearestIntersectData.IsHit()) {
                        RGB_Color diffuseColor(255, 150, 0);
                        
                        for(Objects::PointLight* light: pointLights) {
                            Math::Ray shadowRay = Math::Ray(nearestIntersectData.GetIntersectionPos(), light->GetTransform().GetPosition().Subtract(nearestIntersectData.GetIntersectionPos()), 100);
                            float diffuseModifier = 1.0f;
                            for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                                Math::IntersectionData shadowRayData = shadowRay.Cast(triangle);
                                if(!shadowRayData.IsHit()) {
                                    float dst = nearestIntersectData.GetIntersectionPos().DistanceTo(light->GetTransform().GetPosition());
                                    Math::Vec3 shadowRayVector = light->GetTransform().GetPosition().Subtract(nearestIntersectData.GetIntersectionPos());
                                    diffuseModifier = shadowRayData.GetIntersectionTriangle().GetNormal().Dot(shadowRayVector);
                                    diffuseModifier /= 1 + std::pow(dst / 50.0f, 2.0f);
                                    diffuseColor = RGB_Color(std::clamp((diffuseColor.r + 50 * diffuseModifier) / 2.0f, 0.0f, 255.0f), std::clamp((diffuseColor.r + 150 * diffuseModifier) / 2.0f, 0.0f, 255.0f), std::clamp((diffuseColor.r + 50 * diffuseModifier) / 2.0f, 0.0f, 255.0f));
                                }
                            }
                        }
                        screenBuffer.SetPixelColor(x, y, RGB_Color(diffuseColor.r, diffuseColor.g, diffuseColor.b));
                    } else {
                        screenBuffer.SetPixelColor(x, y, RGB_Color(0, 0, 0));
                    }
                }
            }
        }
        return screenBuffer;
    }
}  // namespace OpenCG::Rendering