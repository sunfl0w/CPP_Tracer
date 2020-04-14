#include "vec3.hpp"

namespace Tracer::Math {
    Vec3::Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec3::Vec3(const Vec3& vec3) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    Vec3::Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Vec3::GetX() const {
        return x;
    }

    float Vec3::GetY() const {
        return y;
    }
    float Vec3::GetZ() const {
        return z;
    }

    float Vec3::Get(int index) const {
        if(index == 0) {
            return x;
        } else if(index == 1) {
            return y;
        } else {
           return z;
        }
    }

    void Vec3::Set(int index, float value) {
        if(index == 0) {
            x = value;
        } else if(index == 1) {
            y = value;
        } else {
            z = value;
        }
    }

    float Vec3::GetMagnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void Vec3::Normalize() {
        float magnitude = GetMagnitude();
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }

    void Vec3::Round() {
        x = std::round(x);
        y = std::round(y);
        z = std::round(z);
    }

    Vec3 Vec3::Add(const Vec3& otherVec3) const {
        return Vec3(x + otherVec3.x, y + otherVec3.y, z + otherVec3.z);
    }

    Vec3 Vec3::Subtract(const Vec3& otherVec3) const {
        return Vec3(x - otherVec3.x, y - otherVec3.y, z - otherVec3.z);
    }

    float Vec3::Dot(const Vec3& otherVec3) const {
        return x * otherVec3.x + y * otherVec3.y + z * otherVec3.z;
    }

    Vec3 Vec3::Multiply(float num) const {
        return Vec3(x * num, y * num, z * num);
    }

    Vec3 Vec3::Cross(const Vec3& otherVec3) const {
        return Vec3(y * otherVec3.z - z * otherVec3.y,
                    z * otherVec3.x - x * otherVec3.z,
                    x * otherVec3.y - y * otherVec3.x);
    }

    float Vec3::DistanceTo(const Vec3& otherVec3) const {
        return std::sqrt(std::pow(x - otherVec3.x, 2) + std::pow(y - otherVec3.y, 2) + std::pow(z - otherVec3.z, 2));
    }
}  // namespace OpenCG::Math