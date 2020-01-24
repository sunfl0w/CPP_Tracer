#pragma once

#include <math.h>

namespace OpenCG::Math {
    class Vec3 {
    public:
        float x;
        float y;
        float z;

    public:
        Vec3();
        Vec3(float x, float y, float z);

        float X() const;
        float Y() const;
        float Z() const;

        float GetMagnitude() const;
        void Normalize();
        void Round();
        Vec3 AddOther(const Vec3& otherVec3) const;
        Vec3 SubtractOther(const Vec3& otherVec3) const;
        float DotWith(const Vec3& otherVec3) const;
        Vec3 MultiplyWith(float num) const;
        Vec3 CrossWith(const Vec3& otherVec3) const;
        float DistanceTo(const Vec3& otherVec3) const;
    };
}  // namespace OpenCG::Math