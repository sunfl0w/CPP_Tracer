#include "vec4.hpp"

namespace Tracer::Math {
     Vec4::Vec4() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vec4::Vec4(const Vec4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }

    Vec4::Vec4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    float Vec4::GetX() const {
        return x;
    }

    float Vec4::GetY() const {
        return y;
    }

    float Vec4::GetZ() const {
        return z;
    }

    float Vec4::GetW() const {
        return w;
    }

    float Vec4::Get(int index) const {
        if(index == 0) {
            return x;
        } else if(index == 1) {
            return y;
        } else if(index == 2) {
           return z;
        } else {
            return w;
        }
    }

    void Vec4::Set(int index, float value) {
        if(index == 0) {
            x = value;
        } else if(index == 1) {
            y = value;
        } else if(index == 2) {
            z = value;
        } else {
            w = value;
        }
    }

    float Vec4::GetMagnitude() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    void Vec4::Normalize() {
        float magnitude = GetMagnitude();
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        w /= magnitude;
    }

    void Vec4::Round() {
        x = std::round(x);
        y = std::round(y);
        z = std::round(z);
        w = std::round(w);
    }

    Vec4 Vec4::Add(const Vec4& otherVec4) const {
        return Vec4(x + otherVec4.x, y + otherVec4.y, z + otherVec4.z, w + otherVec4.w);
    }

    Vec4 Vec4::Subtract(const Vec4& otherVec4) const {
        return Vec4(x - otherVec4.x, y - otherVec4.y, z - otherVec4.z, w - otherVec4.w);
    }

    float Vec4::Dot(const Vec4& otherVec4) const {
        return x * otherVec4.x + y * otherVec4.y + z * otherVec4.z + w * otherVec4.w;
    }

    Vec4 Vec4::Multiply(float num) const {
        return Vec4(x * num, y * num, z * num, w * num);
    }
}