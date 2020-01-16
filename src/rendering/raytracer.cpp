#include "raytracer.hpp"

namespace OpenCG::Rendering {
    Raytracer::Raytracer() {}

    ScreenBuffer Raytracer::RenderToBuffer(std::vector<Tris> triangles, int imageWidth, int imageHeight) {
        ScreenBuffer screenBuffer(imageWidth, imageHeight);
        float invWidth = 1 / float(imageWidth), invHeight = 1 / float(imageHeight);
        float fov = 30;
        float aspectratio = imageWidth / float(imageHeight);
        float angle = tan(M_PI * 0.5 * fov / 180.);

        for (int x = 0; x < imageWidth; x++) {
            for (int y = 0; y < imageHeight; y++) {
                float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
                float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
                Math::Vec3 rayDir(xx, yy, 1);
                rayDir.Normalize();
                float minDst = 99999999;
                RGB_Color color;
                for (Tris triangle : triangles) {
                    Ray ray = Ray(Math::Vec3(0, 0, 5), rayDir, 100);
                    IntersectData intersectData = ray.Cast(triangle);

                    if (intersectData.intersectPos.X() != 0 && intersectData.intersectPos.Y() != 0 && intersectData.intersectPos.Z() != 0) {
                        float dst = intersectData.intersectPos.DistanceTo(Math::Vec3(0, 0, 0));
                        if (dst < minDst) {
                            color = intersectData.color;
                            minDst = dst;
                        }
                    }
                }
                if (minDst != 99999999) {
                    screenBuffer.SetPixelColor(x, y, color);
                } else {
                    screenBuffer.SetPixelColor(x, y, RGB_Color(0, 0, 0));
                }
            }
        }
        return screenBuffer;
    }
}  // namespace OpenCG::Rendering