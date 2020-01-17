#include "vec3.hpp"

namespace OpenCG::Math {
    Vec3::Vec3() {
        data = std::vector<float>(3);
    }
    Vec3::Vec3(float x, float y, float z) {
        data = std::vector<float>{x, y, z};
    }

    float Vec3::X() const {
        return data[0];
    }

    float Vec3::Y() const {
        return data[1];
    }
    float Vec3::Z() const {
        return data[2];
    }

    void Vec3::Set(int index, float value) {
        data[index] = value;
    }

    float Vec3::GetMagnitude() const {
        return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
    }

    void Vec3::Normalize() {
        float magnitude = GetMagnitude();
        data[0] /= magnitude;
        data[1] /= magnitude;
        data[2] /= magnitude;
    }

    void Vec3::Round() {
        data[0] = std::round(data[0]);
        data[1] = std::round(data[1]);
        data[2] = std::round(data[2]);
    }

    Vec3 Vec3::AddOther(const Vec3& otherVec3) const {
        return Vec3(X() + otherVec3.X(), Y() + otherVec3.Y(), Z() + otherVec3.Z());
    }

    Vec3 Vec3::SubtractOther(const Vec3& otherVec3) const {
        return Vec3(X() - otherVec3.X(), Y() - otherVec3.Y(), Z() - otherVec3.Z());
    }

    float Vec3::DotWith(const Vec3& otherVec3) const {
        return X() * otherVec3.X() + Y() * otherVec3.Y() + Z() * otherVec3.Z();
    }

    Vec3 Vec3::MultiplyWith(float num) const {
        return Vec3(X() * num, Y() * num, Z() * num);
    }

    Vec3 Vec3::CrossWith(const Vec3& otherVec3) const {
        return Vec3(data[1] * otherVec3.data[2] - data[2] * otherVec3.data[1],
                    data[2] * otherVec3.data[0] - data[0] * otherVec3.data[2],
                    data[0] * otherVec3.data[1] - data[1] * otherVec3.data[0]);
    }

    float Vec3::DistanceTo(const Vec3& otherVec3) const {
        return std::sqrt(std::pow(X() - otherVec3.X(), 2) + std::pow(Y() - otherVec3.Y(), 2) + std::pow(Z() - otherVec3.Z(), 2));
    }
}  // namespace OpenCG::Math