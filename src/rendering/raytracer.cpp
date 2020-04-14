#include "raytracer.hpp"

using namespace Tracer::Components::Color;

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderSceneToBuffer(Scene& scene, int imageWidth, int imageHeight) const {
        return RenderMeshesToBuffer(scene.GetRenderableObjects(), imageWidth, imageHeight, scene.GetCamera(), scene.GetLightObjects());
    }

    ScreenBuffer Raytracer::RenderMeshesToBuffer(std::vector<Objects::RenderableObject>& renderableObjects, int imageWidth, int imageHeight, Objects::Camera& camera, std::vector<Objects::PointLight>& pointLights) const {
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
                        RGB_Color color(200, 100, 50);
                        Math::Ray shadowRay = Math::Ray(nearestIntersectData.GetIntersectionPos(), pointLights[0].GetTransform().GetPosition().Subtract(nearestIntersectData.GetIntersectionPos()), 100);
                        bool inShadow = false;
                        float dstToLight = nearestIntersectData.GetIntersectionPos().DistanceTo(pointLights[0].GetTransform().GetPosition());
                        Math::Vec3 shadowRayVector = pointLights[0].GetTransform().GetPosition().Subtract(nearestIntersectData.GetIntersectionPos());
                        shadowRayVector.Normalize();
                        Math::Vec3 triangleNormal = nearestIntersectData.GetIntersectionTriangle().GetNormal();
                        triangleNormal.Normalize();
                        float test = shadowRayVector.Dot(triangleNormal);
                        float angleToLight = std::acos(test) * 180.0f / M_PI;
                        //std::cout << shadowRayVector.Dot(rayDir) << std::endl;
                        //std::cout << angleToLight << std::endl;

                        for (Math::Tris triangle : renderableObject.GetMesh().GetData()) {
                            Tris trisPos = renderableObject.GetTransform().TransformTris(triangle);
                            //if (mesh.RayIntersects(shadowRay)) {
                                Math::IntersectionData intersectData = shadowRay.Cast(trisPos);

                                if (intersectData.IsHit()) {
                                    inShadow = true;
                                    break;
                                }
                            //}
                        }
                        if (inShadow) {
                            HSV_Color hsvColor;
                            hsvColor.FromRGB(color.r, color.g, color.b);
                            float modifier = ((1 / ((dstToLight + 300) * 0.001f)) - 3.0f);
                            if(modifier < 0.0f) {
                                modifier = 0.0f;
                            }
                            if(modifier > 0.5f) {
                                modifier = 0.5f;
                            }
                            hsvColor.v = hsvColor.v * modifier;
                            RGB_Color displayedColor = RGB_Color(hsvColor.h, hsvColor.s, hsvColor.v);
                            screenBuffer.SetPixelColor(x, y, displayedColor);
                        } else {
                            HSV_Color hsvColor;
                            hsvColor.FromRGB(color.r, color.g, color.b);
                            float modifier = ((1 / ((angleToLight + 300) * 0.001f)) - 2.33f);
                            //float modifier = ((1 / ((dstToLight + 300) * 0.001f)) - 2.33f);
                            if(modifier < 0.0f) {
                                modifier = 0.0f;
                            }
                            hsvColor.v = hsvColor.v * modifier;
                            RGB_Color displayedColor = RGB_Color(hsvColor.h, hsvColor.s, hsvColor.v);
                            screenBuffer.SetPixelColor(x, y, displayedColor);
                        }
                    } else {
                        screenBuffer.SetPixelColor(x, y, RGB_Color(0, 0, 0));
                    }
                }
            }
        }
        return screenBuffer;
    }
}  // namespace OpenCG::Rendering