#pragma once

#include <string>
#include <vector>

namespace OpenCG::Math {
    class Matrix {
    private:
        unsigned int width;
        unsigned int height;

        std::vector<float> data;

    public:
        Matrix();
        Matrix(unsigned int width, unsigned int height);
        Matrix(unsigned int width, unsigned int height, std::vector<float> data);

        Matrix MultiplyWith(const Matrix& otherMatrix);

        std::string ToString();
    };
}  // namespace OpenCG::Math