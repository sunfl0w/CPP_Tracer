#include "matrix.hpp"

namespace OpenCG::Math {
    Matrix::Matrix(unsigned int width, unsigned int height) {
        this->width = width;
        this->height = height;
        data = std::vector<float>(width * height);
    }

    Matrix::Matrix(unsigned int width, unsigned int height, std::vector<float> data) {
        if (width * height != data.size()) {
            throw "Can't create matrix, data does not have the right size.";
        }
        this->width = width;
        this->height = height;
        this->data = data;
    }

    Matrix Matrix::MultiplyWith(const Matrix& otherMatrix) {
        if (width != otherMatrix.height || height != otherMatrix.width) {
            throw "Can't multiply matrices that are not compatible.";
        }
        Matrix result = Matrix(otherMatrix.width, height);
        for (int x = 0; x < result.width; x++) {
            for (int y = 0; y < result.height; y++) {
                float sum = 0.0f;
                for (int z = 0; z < width; z++) {
                    sum += data[y * width + z] * otherMatrix.data[x + z * height];
                }
                result.data[x + y * result.width] = sum;
            }
        }
        return result;
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