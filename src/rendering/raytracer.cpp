#include "raytracer.hpp"

namespace Tracer::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderToBuffer(std::vector<Components::Mesh>& meshes, int imageWidth, int imageHeight, const Math::Vec3& camPos, const Math::Vec3& lightPos) {
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

                for (Components::Mesh mesh : meshes) {
                    for (Math::Tris triangle : mesh.GetData()) {
                        Math::Ray ray = Math::Ray(camPos, rayDir, 100);
                        if (mesh.RayIntersects(ray)) {
                            Math::IntersectionData intersectData = ray.Cast(triangle);

                            if (intersectData.IsHit()) {
                                float dst = intersectData.GetIntersectionPos().DistanceTo(camPos);
                                if (dst < minDst) {
                                    nearestIntersectData = intersectData;
                                    minDst = dst;
                                }
                            }
                        }
                    }
                    if (nearestIntersectData.IsHit()) {
                        Math::Ray shadowRay = Math::Ray(nearestIntersectData.GetIntersectionPos(), lightPos.Subtract(nearestIntersectData.GetIntersectionPos()), 100);
                        bool inShadow = false;

                        for (Math::Tris triangle : mesh.GetData()) {
                            if (mesh.RayIntersects(shadowRay)) {
                                Math::IntersectionData intersectData = shadowRay.Cast(triangle);
                                float dst = nearestIntersectData.GetIntersectionPos().DistanceTo(intersectData.GetIntersectionPos());
                                float dstToLight = intersectData.GetIntersectionPos().DistanceTo(lightPos);

                                if (dst > 0 && dst < dstToLight && intersectData.IsHit()) {
                                    inShadow = true;
                                    break;
                                }
                            }
                        }
                        if (inShadow) {
                            screenBuffer.SetPixelColor(x, y, RGB_Color(100, 50, 25));
                        } else {
                            screenBuffer.SetPixelColor(x, y, RGB_Color(200, 100, 50));
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