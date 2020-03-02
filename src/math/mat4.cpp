#include "mat4.hpp"

namespace Tracer::Math {
    Mat4::Mat4() {
        data = std::array<float, 16>();
    }

    Mat4::Mat4(const std::array<float, 16>& data) {
        this->data = data;
    }

    void Mat4::ToIdentity() {
        data = std::array<float, 16>();
        data[0] = 1;
        data[5] = 1;
        data[10] = 1;
        data[15] = 1;
    }

    Mat4 Mat4::MultiplyWith(const Mat4& other) {
        
    }
}  // namespace Tracer::Math