#include "mat4.hpp"

namespace Tracer::Math {
    Mat4::Mat4() {
        data = std::array<float, 16>();
    }

    Mat4::Mat4(const std::array<float, 16>& data) {
        this->data = data;
    }

    float& Mat4::operator[](std::size_t index) {
        if (index > 15 || index < 0) {
            throw "Index out of bounds";
        }
        return data[index];
    }

    void Mat4::ToIdentity() {
        data = std::array<float, 16>();
        data[0] = 1;
        data[5] = 1;
        data[10] = 1;
        data[15] = 1;
    }

    Mat4 Mat4::MultiplyWith(const Mat4& other) {
        Mat4 result = Mat4();
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                float sum = 0.0f;
                for (int z = 0; z < 4; z++) {
                    sum += data[y * 4 + z] * other.data[x + z * 4];
                }
                result.data[x + y * 4] = sum;
            }
        }
        return result;
    }

    Vec4 Mat4::MultiplyWith(const Vec4& other) {
        Vec4 result = Vec4();
        for (int y = 0; y < 4; y++) {
            float sum = 0.0f;
            for (int z = 0; z < 4; z++) {
                sum += data[y * 4 + z] * other.Get(z);
            }
            result.Set(y, sum);
        }
        return result;
    }
}  // namespace Tracer::Math