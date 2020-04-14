#pragma once

#include <math.h>

namespace Tracer::Math {
    class Vec3 {
    private:
        float x;
        float y;
        float z;

    public:
        Vec3();
        Vec3(const Vec3& vec3);
        Vec3(float x, float y, float z);

        float GetX() const;
        float GetY() const;
        float GetZ() const;

        float Get(int index) const;
        void Set(int index, float value);

        float GetMagnitude() const;
        void Normalize();
        void Round();
        Vec3 Add(const Vec3& otherVec3) const;
        Vec3 Subtract(const Vec3& otherVec3) const;
        float Dot(const Vec3& otherVec3) const;
        Vec3 Multiply(float num) const;
        Vec3 Cross(const Vec3& otherVec3) const;
        float DistanceTo(const Vec3& otherVec3) const;
    };
}  // namespace OpenCG::Math