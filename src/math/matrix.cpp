#include "matrix.hpp"

namespace OpenCG::Math {
    Matrix::Matrix() {}

    Matrix::Matrix(int width, int height) {
        this->width = width;
        this->height = height;
        this->data = std::vector<float>(width * height);
    }

    Matrix::Matrix(int width, int height, std::vector<float> data) {
        this->width = width;
        this->height = height;
        this->data = data;
    }

    Matrix Matrix::MultiplyWith(const Matrix& otherMatrix) {
        if (width != otherMatrix.height) {
            throw "Can't multiply matrices that are not compatible.";
        }
        Matrix result = Matrix(otherMatrix.width, height);
        for (int y = 0; y < result.height; y++) {
            for (int x = 0; x < result.width; x++) {
                float sum = 0.0f;
                for (int z = 0; z < width; z++) {
                    sum += data[y * width + z] * otherMatrix.data[x + z * otherMatrix.width];
                }
                result.data[x + y * result.width] = sum;
            }
        }
        return result;
    }

    std::vector<float> Matrix::GetData() {
        return data;
    }

    std::string Matrix::ToString() {
        std::string matrixString;
        for (int y = 0; y < width; y++) {
            for (int x = 0; x < height; x++) {
                matrixString += " | " + std::to_string(data[x + y * width]) + " | ";
            }
            matrixString += "\n";
        }
        return matrixString;
    }
}  // namespace OpenCG::Math