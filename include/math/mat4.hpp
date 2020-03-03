#pragma once

#include <array>

namespace Tracer::Math {
    class Mat4 {
    private:
        std::array<float, 16> data;

    public:
        Mat4();

        Mat4(const std::array<float, 16>& data);

        float& operator[](std::size_t index);

        void ToIdentity();

        Mat4 MultiplyWith(const Mat4& other);
    };
}  // namespace Tracer::Math