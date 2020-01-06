#pragma once

#include <vector>
#include <math.h>

namespace OpenCG::Math {
    class Vec3 {
    private:
        std::vector<float> data;

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
        float MultiplyWith(const Vec3& otherVec3) const;
        Vec3 CrossWith(const Vec3& otherVec3) const;
    };
}  // namespace OpenCG::Math