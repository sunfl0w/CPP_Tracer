#include "vec3.hpp"

namespace OpenCG::Math {
    Vec3::Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3::Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Vec3::X() const {
        return x;
    }

    float Vec3::Y() const {
        return y;
    }
    float Vec3::Z() const {
        return z;
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

    Vec3 Vec3::AddOther(const Vec3& otherVec3) const {
        return Vec3(x + otherVec3.x, y + otherVec3.y, z + otherVec3.z);
    }

    Vec3 Vec3::SubtractOther(const Vec3& otherVec3) const {
        return Vec3(x - otherVec3.x, y - otherVec3.y, z - otherVec3.z);
    }

    float Vec3::DotWith(const Vec3& otherVec3) const {
        return x * otherVec3.x + y * otherVec3.y + z * otherVec3.z;
    }

    Vec3 Vec3::MultiplyWith(float num) const {
        return Vec3(x * num, y * num, z * num);
    }

    Vec3 Vec3::CrossWith(const Vec3& otherVec3) const {
        return Vec3(y * otherVec3.z - z * otherVec3.y,
                    z * otherVec3.x - x * otherVec3.z,
                    x * otherVec3.y - y * otherVec3.x);
    }

    float Vec3::DistanceTo(const Vec3& otherVec3) const {
        return std::sqrt(std::pow(x - otherVec3.x, 2) + std::pow(y - otherVec3.y, 2) + std::pow(z - otherVec3.z, 2));
    }
}  // namespace OpenCG::Math