#include "raytracer.hpp"

namespace OpenCG::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderToBuffer(std::vector<Tris> triangles, int imageWidth, int imageHeight, Math::Vec3 camPos) {
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
                IntersectData nearestIntersectData = IntersectData();

                for (Tris triangle : triangles) {
                    Ray ray = Ray(camPos, rayDir, 100);
                    IntersectData intersectData = ray.Cast(triangle);

                    if (intersectData.hit) {
                        float dst = intersectData.intersectPos.DistanceTo(camPos);
                        if (dst < minDst) {
                            nearestIntersectData = intersectData;
                            minDst = dst;
                        }
                    }
                }
                if (nearestIntersectData.hit) {
                    //Ray shadowRay = Ray(nearestIntersectData.intersectPos, Math::Vec3(0, 0, -40).SubtractOther(nearestIntersectData.intersectPos), 100);
                    Math::Vec3 lightPos(40, 0, -40);
                    Math::Vec3 test = nearestIntersectData.intersectPos;
                    //test.SubtractOther(lightPos);
                    Ray shadowRay = Ray(test, lightPos.SubtractOther(nearestIntersectData.intersectPos), 100);
                    bool inShadow = false;

                    for (Tris triangle : triangles) {
                        IntersectData intersectData = shadowRay.Cast(triangle);
                        float dst = nearestIntersectData.intersectPos.DistanceTo(intersectData.intersectPos);
                        float dstToLight = intersectData.intersectPos.DistanceTo(lightPos);

                        if (dst > 0 && dst < dstToLight && intersectData.hit) {
                            inShadow = true;
                            break;
                        }
                    }
                    if (inShadow) {
                        screenBuffer.SetPixelColor(x, y, RGB_Color(100, 50, 25));
                        //screenBuffer.SetPixelColor(x, y, RGB_Color(200, 100, 50));
                    } else {
                        screenBuffer.SetPixelColor(x, y, RGB_Color(200, 100, 50));
                    }
                } else {
                    screenBuffer.SetPixelColor(x, y, RGB_Color(0, 0, 0));
                }
            }
        }
        return screenBuffer;
    }
}  // namespace OpenCG::Rendering