#pragma once

#include <array>

#include "vec4.hpp"

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

        Vec4 MultiplyWith(const Vec4& other);
    };
}  // namespace Tracer::Math