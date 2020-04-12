#pragma once

namespace Tracer::Math {
    class Vec4 {
    private:
        float x;
        float y;
        float z;
        float w;

    public:
        Vec4();
        Vec4(const Vec4& vec4);
        Vec4(float x, float y, float z, float w);

        float GetX() const;
        float GetY() const;
        float GetZ() const;
        float GetW() const;

        void Set(int index, float value);

        float GetMagnitude() const;
        void Normalize();
        void Round();
        Vec4 Add(const Vec4& otherVec3) const;
        Vec4 Subtract(const Vec4& otherVec3) const;
        float Dot(const Vec4& otherVec3) const;
        Vec4 Multiply(float num) const;
    };
}