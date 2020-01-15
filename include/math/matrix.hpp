#pragma once

#include <string>
#include <vector>

namespace OpenCG::Math {
    class Matrix {
    private:
        unsigned int width;
        unsigned int height;
    public:
        std::vector<float> data;

    public:
        Matrix();
        Matrix(int width, int height);
        Matrix(int width, int height, std::vector<float> data);

        Matrix MultiplyWith(const Matrix& otherMatrix);

        std::vector<float> GetData();

        std::string ToString();
    };
}  // namespace OpenCG::Math